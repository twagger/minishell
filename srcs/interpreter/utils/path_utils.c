/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:32:01 by twagner           #+#    #+#             */
/*   Updated: 2022/01/20 22:20:49 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

/*
** Concat a directory and a binary name, test if the binary is in the dir.
** If it is not, returns null, then, returns the full path to the bin.
*/

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

/*
** For every dir, try to build a path with the binary.
** If the binary is found, return the full path, if not, return bin name
*/

char	*ms_getgood_path(char **dir, char *bin)
{
	char	*bin_path;
	char	**begin;

	begin = dir;
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
			free(begin);
			free(bin);
			return (bin_path);
		}
		free(bin_path);
		free(*dir);
		++dir;
	}
	free(begin);
	return (bin);
}

/*
** Function to return the best possible path for an executable (*bin).
*/

int	ms_getbin_path(char **bin)
{
	char	*path;
	char	**dir;

	if (ft_strchr(*bin, '/'))
		return (0);
	path = ms_getenv("PATH");
	if (!path)
		dir = ft_split(".", ':');
	else
		dir = ft_split(path, ':');
	if (!dir)
		return (ERROR);
	*bin = ms_getgood_path(dir, *bin);
	return (0);
}
