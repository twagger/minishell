/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:20 by twagner           #+#    #+#             */
/*   Updated: 2021/12/28 16:04:37 by twagner          ###   ########.fr       */
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
			perror("minishell: cd:");
			return (1);
		}
	}
	return (0);
}

char	*ms_set_pwd_currpath(char *rep)
{
	char	*pwd;
	char	*step1;
	char	*fullpath;

	pwd = getenv("PWD");
	step1 = ft_strjoin("/", rep);
	if (!step1)
		return (NULL);
	fullpath = ft_strjoin(pwd, step1);
	if (!fullpath)
	{
		free(step1);
		return (NULL);
	}
	return (fullpath);
}

char	*ms_set_cdpath_currpath(char *rep)
{
	char	**cdpath;
	char	*step1;
	char	*trypath;

	if (!getenv("CDPATH"))
		return (ft_strdup(rep));
	cdpath = ms_split_cdpath(getenv("CDPATH"), ':');
	if (!cdpath)
		return (NULL);
	while (*cdpath)
	{
		step1 = ft_strjoin("/", rep);
		if ((*cdpath)[0] == 0)
			trypath = ft_strjoin(".", step1);
		else
			trypath = ft_strjoin(*cdpath, step1);
		free(step1);
		if (!trypath)
			return (NULL);
		if (access(trypath, F_OK | R_OK) == 0)
			return (trypath);
		free(trypath);
		++cdpath;
	}
	return (ft_strdup(rep));
}

int	ms_cd(int ac, char **av, char **envp)
{
	char	*curpath;

	(void)envp;
	if (ac == 1)
		return (ms_go_home());
	if (ac >= 2)
	{
		if (av[1][0] == '/')
			curpath = ft_strdup(av[1]);
		else if (!ft_strcmp(".", av[1]) || !ft_strcmp("..", av[1]))
			curpath = ms_set_pwd_currpath(av[1]);
		else
		{
			curpath = ms_set_cdpath_currpath(av[1]);
			if (!ft_strcmp(curpath, av[1]))
				curpath = ms_set_pwd_currpath(av[1]);
		}
		curpath = ms_convert_canonical(curpath);
		if (chdir(curpath) == ERROR)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(av[1]);
			free(curpath);
			return (1);
		}
		// change PWD
		// change OLDPWD
		free(curpath);
	}
	return (1);
}
