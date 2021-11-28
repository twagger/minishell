/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:32:22 by twagner           #+#    #+#             */
/*   Updated: 2021/11/28 11:44:45 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

static void	ms_exec_left(t_node	*node, char **envp, int exit_code)
{
	// visit the left branch of a node
	// The left node is a simple command or a redir command
	// if simple command :
		// visit to build arg array
		// execute the command with execve
	// if redir command :
		// execute redir (dup)
		// visit to build arg array
		// execute the command with execve

}

static void	ms_visit(t_node *node, char **envp, int exit_code)
{
	if (!node)
		return ;
	ms_visit(node->left, envp, exit_code);
	ms_visit(node->right, envp, exit_code);
	// If I am on a PIPE SEQUENCE NODE :
	// create a pipe
	// fork
		// the child process will close useless fd and "exec left" of the current node
		// the current process will close useless fd and continue browse the tree (no wait)
	return (cmd);
}

/*
** MAIN FUNCTION
** Call the cmd list builder then execute the pipeline
*/

int	ms_exec_pipeline(t_node *ast, char **envp, int exit_code)
{
	pid_t				pid;
	pid_t				wpid;
	int					status;

	pid = fork();// 1 : fork to create a subshell
	if (pid == ERROR)
		return (ERROR);
	if (pid == 0)
	{
		signal(SIGINT, ms_sig_handler);
		signal(SIGQUIT, ms_sig_handler);
		exit(ms_visit(ast, envp, exit_code));// 2 : Browse the tree into the subshell (and create pipes and fork for every command)
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wpid = waitpid(pid, &status, 0); // 2 : waitpid into the main shell (minishell)
		if (wpid == ERROR)
			return (ERROR);
	}
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
