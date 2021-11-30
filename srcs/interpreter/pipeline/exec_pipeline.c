/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:32:22 by twagner           #+#    #+#             */
/*   Updated: 2021/11/30 12:56:43 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

/*
** REDIRECTION HANDLER
** This function handles all the redirection commands for a command
*/

static void	ms_handle_redir(t_node	*node, char **envp)
{

}

/*
** COMMAND EXECUTION
** This function will check if the command contain redirections (to be done 
** with "dup" before the command execution), and then will create an arg array
** to be given to execve for execution.
*/

static int	ms_exec_left(t_node	*node, char **envp, int exit_code)
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
** Browse the tree to find every command. Each new command will create a 
** pipe to communicate with the previous one, and a fork to execute it.
** The execution of the command is then handled by a specitic exec function
*/

static void	ms_visit(t_node *node, char **envp, int exit_code)
{
	pid_t	pid;
	int		pipefd[2];

	if (!node)
		return ;
	ms_visit(node->left, envp, exit_code);
	ms_visit(node->right, envp, exit_code);
	// If I am on a PIPE SEQUENCE NODE
	if (node->reduc == R_PIPE_SEQUENCE)
	{
		// create a pipe
		if (pipe(pipefd) == -1)
			return :
		pid = fork();// fork
		if (pid == ERROR)
			return (ERROR);
		if (pid == 0)
		{
			// the child process will close write fd, enable signal management and "exec left" of the current node then close the read fd
			close(pipefd[0]);
			signal(SIGINT, ms_sig_handler);
			signal(SIGQUIT, ms_sig_handler);
			// changer les stdin et out de la commande sur le pipe
			ms_exec_left(t_node	*node, envp, exit_code);
			close(pipefd[1]);
		}
		else
		{
			// the current process will close read fd and continue browse the tree (no waitpid)
			close(pipefd[0]);
		}
	}
	return (cmd);
}

/*
** PIPELINE EXECUTION
** Creates a subshell to execute all the commands of the pipeline
*/

int	ms_exec_pipeline(t_node *ast, char **envp, int exit_code)
{
	pid_t				pid;
	pid_t				wpid;
	int					status;

	pid = fork();// 1 : fork to create a subshell
	if (pid == ERROR)
		return (ERROR);
	// Signal are ignored by Minishell and the subshell but the child processes of subshell should have them handled
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
		exit(ms_visit(ast, envp, exit_code));// 2 : Browse the tree into the subshell (and create pipes and fork for every command)
	else
	{
		wpid = waitpid(pid, &status, 0);// 2 : waitpid into the main shell (minishell)
		if (wpid == ERROR)
			return (ERROR);
	}
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
