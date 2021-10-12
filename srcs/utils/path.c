/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:32:01 by twagner           #+#    #+#             */
/*   Updated: 2021/10/12 15:47:20 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_path(void)
{
	char	*step_1;
	char	*step_2;
	char	*step_3;

	step_1 = ft_strjoin(getcwd(NULL, 0), BUILTINS_PATH);
	step_2 = ft_strjoin(step_1, ":");
	step_3 = ft_strjoin(step_2, getenv("PATH"));
	free(step_1);
	free(step_2);
	return (step_3);
}

char	*ms_build_bin_path(char *path, char *bin)
{
	char	*bin_path;
	char	*dir;

	dir = ft_strjoin(path, "/");
	bin_path = ft_strjoin(dir, bin);
	if (!bin_path)
	{
		free(dir);
		return (NULL);
	}
	free(dir);
	if (access(bin_path, F_OK | X_OK) == 0)
		return (bin_path);
	free(bin_path);
	return (NULL);
}

char	*ms_getgood_path(char **dir, char *bin)
{
	char	*bin_path;

	while (*dir)
	{
		bin_path = ms_build_bin_path(*dir, bin);
		if (bin_path)
		{
			while (*dir)
			{
				free(*dir);
				++dir;
			}
			return (bin_path);
		}
		free(bin_path);
		free(*dir);
		++dir;
	}
	return (bin);
}

int	ms_getbin_path(char **bin)
{
	char	*path;
	char	**dir;

	if (!bin)
		return (ERROR);
	path = ms_get_path();
	dir = ft_split(path, ':');
	if (!dir)
	{	
		free(path);
		return (ERROR);
	}
	*bin = ms_getgood_path(dir, *bin);
	return (0);
}
