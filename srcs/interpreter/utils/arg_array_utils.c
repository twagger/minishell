/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_array_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:02:55 by twagner           #+#    #+#             */
/*   Updated: 2022/01/20 22:03:38 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

static int	ms_args_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (i);
}

char	**ms_add_arg_back(char **args, char *data)
{
	int		i;
	char	**new;

	if (!args)
		return (NULL);
	new = (char **)malloc(sizeof(*new) * (ms_args_len(args) + 2));
	if (!new)
		return (ms_free_str_array_null(args));
	i = -1;
	while (args[++i])
	{
		new[i] = ft_strdup(args[i]);
		if (!new[i])
		{
			ms_free_str_array(args);
			return (ms_free_str_array_null(new));
		}
	}
	ms_free_str_array(args);
	new[i] = ft_strdup(data);
	if (!new[i])
		return (ms_free_str_array_null(new));
	new[i + 1] = NULL;
	return (new);
}

char	**ms_init_arg_array(void)
{
	char	**array;

	array = (char **)malloc(sizeof(*array));
	if (!array)
		return (NULL);
	*array = NULL;
	return (array);
}

/*
** ARGS[0] EXPANDED
** If args[0] is from an expanded token, we should split it
*/

char	**ms_add_expanded_cmd(char **args, t_node *node)
{
	int		i;
	int		j;
	char	**splitted;

	splitted = ft_split(node->data, ' ');
	if (!splitted)
		return (NULL);
	i = -1;
	while (splitted[++i])
	{
		args = ms_add_arg_back(args, splitted[i]);
		if (!args)
		{
			j = -1;
			while (splitted[++j])
				free(splitted[j]);
			free(splitted);
			return (NULL);
		}
	}
	j = -1;
	while (splitted[++j])
		free(splitted[j]);
	free(splitted);
	return (args);
}
