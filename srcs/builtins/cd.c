/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:20 by twagner           #+#    #+#             */
/*   Updated: 2022/01/18 11:28:00 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_join_with_slash(char *s1, char *s2)
{
	char	*step1;
	char	*result;

	step1 = ft_strjoin("/", s2);
	if (!step1)
		return (NULL);
	result = ft_strjoin(s1, step1);
	free(step1);
	if (!result)
		return (NULL);
	return (result);
}

static int	ms_go_home(void)
{
	char	*home;

	home = ms_getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: error: HOME in undefined in PATH\n", 2);
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
	ms_setenv("OLDPWD", ms_getenv("PWD"));
	ms_setenv("PWD", home);
	return (0);
}

static char	*ms_set_cdpath_currpath(char *rep)
{
	char	**cdpath;
	char	*trypath;
	int		i;

	if (!ms_getenv("CDPATH"))
		return (ft_strdup(rep));
	cdpath = ms_split_cdpath(ms_getenv("CDPATH"), ':');
	if (!cdpath)
		return (NULL);
	i = -1;
	while (cdpath[++i])
	{
		trypath = ms_join_with_slash(cdpath[i], rep);
		if (access(trypath, F_OK | R_OK) == 0)
		{
			ms_free_str_array(cdpath);
			return (trypath);
		}
		free(trypath);
	}
	ms_free_str_array(cdpath);
	return (ft_strdup(rep));
}

static char	*ms_build_curpath(char *input)
{
	char	*curpath;
	char	*tmp;

	if (input[0] == '/')
		curpath = ft_strdup(input);
	else if (!ft_strncmp(".", input, 1) || !ft_strncmp("..", input, 2))
		curpath = ms_join_with_slash(ms_getenv("PWD"), input);
	else
	{
		curpath = ms_set_cdpath_currpath(input);
		if (!ft_strcmp(curpath, input))
		{
			tmp = curpath;
			curpath = ms_join_with_slash(ms_getenv("PWD"), input);
			free(tmp);
		}
	}
	curpath = ms_convert_canonical(curpath);
	tmp = curpath;
	if (tmp == NULL)
		curpath = ft_strdup("/");
	else
		curpath = ft_strjoin("/", tmp);
	free(tmp);
	return (curpath);
}

int	ms_cd(int ac, char **av)
{
	char	*curpath;

	if (ac == 1)
		return (ms_go_home());
	if (ac >= 2)
	{
		curpath = ms_build_curpath(av[1]);
		if (chdir(curpath) == ERROR)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(curpath);
			free(curpath);
			return (1);
		}
		ms_setenv("OLDPWD", ms_getenv("PWD"));
		ms_setenv("PWD", curpath);
		free(curpath);
	}
	return (0);
}
