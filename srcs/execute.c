/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/10/22 15:37:01 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	/*if (ft_strncmp(args[0], "export", 7) == 0)
		ret = ms_export(ac, args, envp, prm);*/
	if (ft_strncmp(args[0], "unset", 6) == 0)
		ret = ms_unset(ac, args, envp);
	if (ft_strncmp(args[0], "exit", 5) == 0)
		ret = ms_exit(ac, args);
	return (ret);
}

static int	ms_command_launcher(char **args, char **envp)
{
	(void)envp;
	if (ms_getbin_path(&args[0]) == ERROR)
		return (ERROR);
	if (execve(args[0], args, NULL) == ERROR)
		perror("Minishell");
	return (EXIT_SUCCESS);
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
		if (ms_command_launcher(args, envp) == ERROR)
			return (1);
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
