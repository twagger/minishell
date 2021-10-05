/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/10/05 15:35:16 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getbin_path(char **bin)
{
	char **paths;

	if (bin)
	{
		paths = ft_split(getenv("PATH"), ':');
		if (!paths)
			return (ERROR);
		while (*paths)
		{
			// verifier que le fichier existe avec stat
			// si le fichier existe, mettre a jour **bin et renvoyer 0
		}
		// si le fichier n'existe pas, ne pas mettre a jour bin et renvoyer 0
	}
}

int		ms_execute(char **args)
{
	pid_t	pid;
	pid_t	wpid;
  	int 	status;

 	pid = fork();
	if (pid == ERROR)
	{
		perror("Minishell");
		return (0);
	}
	if (pid == 0)
	{
		if (ft_getbin_path(&args[0]) == ERROR)
			return (ERROR);
		if (execve(args[0], args, NULL) == ERROR)
			perror("Minishell");
		exit (1);
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