/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:32:22 by twagner           #+#    #+#             */
/*   Updated: 2021/12/03 12:26:53 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

/*
** COMMAND EXECUTION
** This function will check if the command contain redirections (to be done 
** with "dup" before the command execution), and then will create an arg array
** to be given to execve for execution.
*/

static int	ms_exec(t_node	*node, char **envp, int exit_code)
{
	// if redir command :
	if (ms_search_ast(node->left, A_RED_TO, 0) \
		|| ms_search_ast(node->left, A_RED_FROM, 0) \
		|| ms_search_ast(node->left, A_DLESS, 0) \
		|| ms_search_ast(node->left, A_DGREAT, 0))
	{
		// changer les stdin et out de la commande sur les redirections
		// execute redir (dup) > Probably with a specific function
		// visit to build arg array
		// execute the command with execve
	}
	else // if simple command :
		return (ms_exec_simple_command(node->left, envp, exit_code));
	return (0);
}

/*
** VISIT
** Browse the tree to find every command. Each new command will use a 
** pipe to communicate with the previous and next one, and a fork to execute.
** The execution of the command is then handled by a specitic exec function
*/

static int	ms_visit(t_node *node, char **envp, int exit_code, t_pipe *pipe)
{
	pid_t	pid;
	int		ret;

	if (!node)
		return ;
	ms_visit(node->left, envp, exit_code, pipe);
	ms_visit(node->right, envp, exit_code, pipe);
	if (node->type == ROOT) // execute last process without fork (in the subshell then return its exit status)
	{
		ms_close_unused_fds(pipe);
		ms_connect_read_fd(pipe);
		ret = exec(node, envp, exit_code);
		ms_free_pipe_list(pipe);
		return (ret);
	}
	else if (node->reduc == R_PIPE_SEQUENCE) // fork
	{
		pid = fork(); // fork
		if (pid == ERROR)
			return (ERROR);
		if (pid == 0)
		{
			ms_activate_signal_handler();
			ms_close_unused_fds(pipe);
			ms_connect_read_fd(pipe);
			ms_connect_write_fd(pipe);
			ret = ms_exec(node, envp, exit_code);
			ms_free_pipe_list(pipe);
			exit(ret);
		}
		ms_update_curr_fds(pipe);
		// cut the branch si it is not executed again after
	}
	return (0);
}

/*
** PIPELINE EXECUTION
** Creates a subshell to execute all the commands of the pipeline
*/

int	ms_exec_pipeline(t_node *ast, char **envp, int exit_code, int nb)
{
	pid_t				pid;
	pid_t				wpid;
	int					status;
	t_pipe				pipe;

	if (ast)
		ast->type = -2;
	// 0 : Signal are ignored by Minishell and the subshell but the child processes of subshell should have them handled
	ms_ignore_signals();
	// 1 : fork to create a subshell
	pid = fork();
	if (pid == ERROR)
		return (ERROR);
	// 2 : Browse the tree into the subshell (and create pipes and fork for every command + exit the pipeline with the return code of the last command)
	if (pid == 0)
	{
		pipe = ms_init_pipes(nb);
		if (!pipe)
			return (ERROR);
		exit(ms_visit(ast, envp, exit_code, pipe));
	}
	else
	{// 2 bis : waitpid into the main shell (minishell)
		wpid = waitpid(pid, &status, 0);
		if (wpid == ERROR)
			return (ERROR);
	}
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
