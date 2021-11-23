/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/11/23 16:36:44 by twagner          ###   ########.fr       */
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
	pid_t	pid;
	pid_t	wpid;
	int		ret;
	int		status;

	pid = fork();
	ret = 0;
	if (pid == ERROR)
		return (ERROR);
	if (pid == 0)
		ret = ms_command_launcher(args, envp);
	else
	{
		wpid = waitpid(pid, &status, 0);
		if (wpid == ERROR)
			return (ERROR);
	}
	return (ret);
}

static char	**ms_visit(t_node *node, char **args, char **envp)
{
	if (!node)
		return (args);
	args = ms_visit(node->left, args, envp);
	args = ms_visit(node->right, args, envp);
	if (node->type == A_PARAM)
	{
		if (ft_strcmp(node->data, "$?") == 0)
			args = ms_add_arg_back(args, ft_itoa(errno));
		else
			args = ms_add_arg_back(args, node->data);
	}
	else if (node->type == A_CMD)
	{
		if (ft_strcmp(node->data, "$?") == 0)
		{
			args = ms_add_arg_back(args, "echo");
			args = ms_add_arg_back(args, ft_itoa(errno));
		}
		else
			args = ms_add_arg_back(args, node->data);
	}
	return (args);
}

int	ms_exec_simple_command(t_node *ast, char **envp)
{
	char	**args;
	int		ret;

	args = ms_init_arg_array();
	args = ms_visit(ast, args, envp);
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
	else if (ret > 0)
		perror("Minishell");
	return (errno);
}
