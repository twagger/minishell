/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:02:55 by twagner           #+#    #+#             */
/*   Updated: 2021/10/22 11:09:21 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_args_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (i);
}

void	ms_free_arg_array(char **args)
{
	if (args)
	{
		while (*args)
		{
			free(*args);
			++args;
		}
	}
}

char	**ms_add_one_arg(char **args, char *data)
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
		ms_free_arg_array(args);
		return (NULL);
	}
	new[ac + 1] = NULL;
	i = -1;
	while (args[++i])
		new[i] = ft_strdup(args[i]);
	new[i] = ft_strdup(data);
	ms_free_arg_array(args);
	return (new);
}

char	**ms_add_command(char **args, char *cmd)
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
		ms_free_arg_array(args);
		return (NULL);
	}
	new[ac + 1] = NULL;
	new[0] = ft_strdup(cmd);
	i = -1;
	while (args[++i])
		new[i + 1] = ft_strdup(args[i]);
	ms_free_arg_array(args);
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
