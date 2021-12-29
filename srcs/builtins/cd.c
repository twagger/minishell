/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:20 by twagner           #+#    #+#             */
/*   Updated: 2021/12/29 12:27:14 by twagner          ###   ########.fr       */
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

static char	*ms_set_cdpath_currpath(char *rep)
{
	char	**cdpath;
	char	*trypath;
	int		i;

	if (!getenv("CDPATH"))
		return (ft_strdup(rep));
	cdpath = ms_split_cdpath(getenv("CDPATH"), ':');
	if (!cdpath)
		return (NULL);
	i = -1;
	while (cdpath[++i])
	{
		trypath = ms_join_with_slash(cdpath[i], rep);
		if (access(trypath, F_OK | R_OK) == 0)
		{
			ms_clear_str_array(cdpath);
			return (trypath);
		}
		free(trypath);
	}
	ms_clear_str_array(cdpath);
	return (ft_strdup(rep));
}

static char	*ms_build_curpath(char *input)
{
	char	*curpath;
	char	*tmp;

	if (input[0] == '/')
		curpath = ft_strdup(input);
	else if (!ft_strcmp(".", input) || !ft_strcmp("..", input))
		curpath = ms_join_with_slash(getenv("PWD"), input);
	else
	{
		curpath = ms_set_cdpath_currpath(input);
		if (!ft_strcmp(curpath, input))
			curpath = ms_join_with_slash(getenv("PWD"), input);
	}
	curpath = ms_convert_canonical(curpath);
	tmp = curpath;
	if (input[0] == '/')
	{
		curpath = ft_strjoin("/", tmp);
		free(tmp);
	}
	return (curpath);
}

int	ms_cd(int ac, char **av, char **envp)
{
	char	*curpath;

	(void)envp;
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
		// change PWD
		// change OLDPWD
		free(curpath);
	}
	return (1);
}
