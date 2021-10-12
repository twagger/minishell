/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/10/12 15:45:27 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_execute(char **args)
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
		if (execve(args[0], args, NULL) == ERROR)
			perror("Minishell");
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
