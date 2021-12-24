/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/12/24 11:01:49 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "parser.h"

/*
** SIMPLE COMMAND
** Execute a simple command (command with/ without parameters),
** no redirection, pipe or delimiter
** The input of the simple command is an arg list with the command as last arg
*/

static int	ms_command_launcher(char **args, char **envp)
{
	int	ret;

	(void)envp;
	if (ms_getbin_path(&args[0]) == ERROR)
		return (ERROR);
	ret = execve(args[0], args, NULL);
	if (ret == ERROR)
	{
		if (errno == EAGAIN)
			ret = 126;
		else
			ret = 127;
	}
	return (ret);
}

int	ms_execute(char **args, char **envp)
{
	pid_t				pid;
	pid_t				wpid;
	int					status;

	pid = fork();
	if (pid == ERROR)
		return (ERROR);
	if (pid == 0)
	{
		ms_activate_signal_handler();
		exit(ms_command_launcher(args, envp));
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wpid = waitpid(pid, &status, 0);
		if (wpid == ERROR)
			return (ERROR);
	}
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static char	**ms_visit(t_node *node, char **args, char **envp, int exit_code)
{
	if (!node)
		return (args);
	args = ms_visit(node->left, args, envp, exit_code);
	args = ms_visit(node->right, args, envp, exit_code);
	if (node->type == A_PARAM)
	{
		if (ft_strcmp(node->data, "$?") == 0)
			args = ms_add_arg_back(args, ft_itoa(exit_code));
		else
			args = ms_add_arg_back(args, node->data);
	}
	else if (node->type == A_CMD)
	{
		if (ft_strcmp(node->data, "$?") == 0)
			args = ms_add_arg_back(args, ft_itoa(exit_code));
		else
			args = ms_add_arg_back(args, node->data);
	}
	return (args);
}

int	ms_exec_simple_command(t_node *ast, char **envp, int exit_code)
{
	char	**args;
	int		ret;

	args = ms_init_arg_array();
	args = ms_visit(ast, args, envp, exit_code);
	if (!args)
	{
		ms_free_arg_array(args);
		return (ERROR);
	}
	if (ms_is_builtin(args[0]))
		ret = ms_execute_builtin(args, envp);
	else
		ret = ms_execute(args, envp);
	ms_free_arg_array(args);
	if (ret == ERROR)
		return (ERROR);
	else if (ret > 0 && ret < 128)
		printf("Minishell: %s\n", strerror(ret));
	return (ret);
}
