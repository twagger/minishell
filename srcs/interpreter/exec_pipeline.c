/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:32:22 by twagner           #+#    #+#             */
/*   Updated: 2021/12/27 11:35:51 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

/*
** COMMAND EXECUTION
** This function will check if the command contain redirections (to be done 
** with "dup" before the command execution), and then will create an arg array
** to be given to execve for execution.
*/

static int	ms_exec_pipe_sequence(\
	t_node *node, char **envp, int exit_code, t_pipe *pipe)
{
	int	ret;

	ms_activate_signal_handler();
	ms_connect_pipe(pipe);
	ms_do_redirections(node);
	ret = ms_exec_piped_command(node, envp, exit_code);
	ms_free_pipe_list(pipe);
	return (ret);
}

/*
** VISIT AST FOR PIPELINE
** Browse the tree to find every command. Each new command will use a 
** pipe to communicate with the previous and next one, and a fork to execute,
** except for the last command (ROOT) which is executed in the subshell 
** process. The execution of the command is then handled by a specitic exec 
** function.
*/

static int	ms_visit(t_node *node, char **envp, int exit_code, t_pipe *pipe)
{
	pid_t	pid;

	if (!node)
		return (0);
	ms_visit(node->left, envp, exit_code, pipe);
	ms_visit(node->right, envp, exit_code, pipe);
	if (node->type == ROOT)
		return (ms_exec_pipe_sequence(node, envp, exit_code, pipe));
	else if (node->type == A_PIPE)
	{
		pid = fork();
		if (pid == ERROR)
			return (ERROR);
		if (pid == 0)
			exit(ms_exec_pipe_sequence(node->left, envp, exit_code, pipe));
		ms_update_curr_fds(pipe);
	}
	return (0);
}

/*
** PIPELINE EXECUTION
** Initialize pipes then creates a subshell to execute all 
** the commands of the pipeline. Gets the return status of the last
** command of the pipeline and returns it to Minishell.
*/

int	ms_exec_pipeline(t_node *ast, char **envp, int exit_code, int nb)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	t_pipe	*pipe;

	if (ast)
		ast->type = -2;
	ms_ignore_signals();
	pid = fork();
	if (pid == ERROR)
		return (ERROR);
	if (pid == 0) // subshell
	{
		pipe = ms_init_pipes(nb);
		if (!pipe)
			return (ERROR);
		exit(ms_visit(ast, envp, exit_code, pipe));
	}
	else // minishell
	{
		wpid = waitpid(pid, &status, 0); // get the return of the subshell process
		if (wpid == ERROR)
			return (ERROR);
	}
	return (ms_get_exit_status(status));
}
