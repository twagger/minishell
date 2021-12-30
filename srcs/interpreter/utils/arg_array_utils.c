/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_array_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:02:55 by twagner           #+#    #+#             */
/*   Updated: 2021/12/30 13:34:36 by twagner          ###   ########.fr       */
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
	int		ac;
	char	**new;

	if (!args)
		return (NULL);
	ac = ms_args_len(args);
	new = (char **)malloc(sizeof(*new) * (ac + 2));
	if (!new)
	{
		ms_free_str_array(args);
		return (NULL);
	}
	new[ac + 1] = NULL;
	i = -1;
	while (args[++i])
		new[i] = ft_strdup(args[i]);
	new[i] = ft_strdup(data);
	ms_free_str_array(args);
	return (new);
}

char	**ms_add_arg_front(char **args, char *cmd)
{
	int		i;
	int		ac;
	char	**new;

	if (!args)
		return (NULL);
	ac = ms_args_len(args);
	new = (char **)malloc(sizeof(*new) * (ac + 2));
	if (!new)
	{
		ms_free_str_array(args);
		return (NULL);
	}
	new[ac + 1] = NULL;
	new[0] = ft_strdup(cmd);
	i = -1;
	while (args[++i])
		new[i + 1] = ft_strdup(args[i]);
	ms_free_str_array(args);
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
