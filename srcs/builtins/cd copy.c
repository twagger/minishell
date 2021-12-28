/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:20 by twagner           #+#    #+#             */
/*   Updated: 2021/12/28 09:25:55 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_go_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("cd: error: HOME in undefined in PATH\n", 2);
		return (1);
	}
	else
	{
		if (chdir(home) == ERROR)
		{
			perror("cd");
			return (1);
		}
		return (1);
	}
}

char	*ms_build_dir(int ac, char **av)
{
	char	*dir;
	char	*prev;
	char	*step_1;
	int		i;

	dir = NULL;
	i = 0;
	while (++i < ac)
	{
		step_1 = NULL;
		prev = dir;
		if (!dir)
			dir = ft_strjoin("", av[i]);
		else
		{
			step_1 = ft_strjoin(dir, " ");
			dir = ft_strjoin(step_1, av[i]);
		}
		free(step_1);
		free(prev);
		if (!dir)
			return (NULL);
	}
	return (dir);
}

char	*ms_build_curpath(char *dir)
{
	char	*curpath;
	char	*step_1;
	char	*cwd;

	if (dir[0] == '/')
		curpath = ft_strdup(dir);
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			perror("cd");
			return (NULL);
		}
		step_1 = ft_strjoin(cwd, "/");
		curpath = ft_strjoin(step_1, dir);
		free(step_1);
	}
	return (curpath);
}

int	ms_cd(int ac, char **av)
{
	char	*curpath;
	char	*dir;

	if (ac == 1)
		return (ms_go_home());
	if (ac > 2)
	{
		dir = ms_build_dir(ac, av);
		if (!dir)
			return (1);
	}
	else
		dir = ft_strdup(av[1]);
	curpath = ms_build_curpath(dir);
	if (!curpath)
		return (1);
	if (chdir(curpath) == ERROR)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(av[1]);
		free(curpath);
		free(dir);
		return (1);
	}
	//set the PWD env variable to currpath
	free(curpath);
	free(dir);
	return (1);
}
