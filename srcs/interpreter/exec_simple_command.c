/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/11/12 11:17:22 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "parser.h"

/*
** SIMPLE COMMAND
** Execute a simple command (command with/ without parameters),
** no redirection, pipe or delimiter
*/

int	ms_is_builtin(char *command)
{
	if (ft_strncmp(command, "cd", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "env", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "echo", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "pwd", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "exit", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "export", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		return (1);
	return (0);
}

int	ms_execute_builtin(char **args, char **envp)
{
	int	ac;
	int	ret;

	ret = 0;
	ac = 0;
	while (args[ac])
		++ac;
	if (ft_strncmp(args[0], "cd", 3) == 0)
		ret = ms_cd(ac, args);
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		ret = ms_pwd(ac, args);
	if (ft_strncmp(args[0], "echo", 3) == 0)
		ret = ms_echo(ac, args);
	if (ft_strncmp(args[0], "env", 4) == 0)
		ret = ms_env(ac, args, envp);
	if (ft_strncmp(args[0], "export", 7) == 0)
		ret = ms_export(ac, args, envp);
	if (ft_strncmp(args[0], "unset", 6) == 0)
		ret = ms_unset(ac, args, envp);
	if (ft_strncmp(args[0], "exit", 5) == 0)
		ret = ms_exit(ac, args);
	return (ret);
}

int	ms_execute(char **args, char **envp)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == ERROR)
	{
		perror("Minishell");
		return (0);
	}
	if (pid == 0)
	{
		if (ms_getbin_path(&args[0]) == ERROR)
			return (ERROR);
		if (execve(args[0], args, envp) == ERROR)
			perror("Minishell");
	}
	else
	{
		wpid = waitpid(pid, &status, 0);
		if (wpid == ERROR)
		{
			perror("Minishell");
			return (1);
		}
	}
	return (1);
}

static char	**ms_visit(t_node *node, char **args, char **envp)
{
	if (!node)
		return (args);
	args = ms_visit(node->left, args, envp);
	args = ms_visit(node->right, args, envp);
	if (node->type == A_PARAM)
		args = ms_add_arg_back(args, node->data);
	else if (node->type == A_CMD)
	{
		args = ms_add_arg_front(args, node->data);
		if (!args)
			return (NULL);
		if (ms_is_builtin(args[0]))
			ms_execute_builtin(args, envp);
		else
			ms_execute(args, envp);
		ms_free_arg_array(args);
		args = ms_init_arg_array();
	}
	return (args);
}

int	ms_exec_simple_command(t_node *ast, char **envp)
{
	char	**args;

	args = ms_init_arg_array();
	args = ms_visit(ast, args, envp);
	if (!args)
	{
		ms_free_arg_array(args);
		return (ERROR);
	}
	ms_free_arg_array(args);
	return (EXIT_SUCCESS);
}
