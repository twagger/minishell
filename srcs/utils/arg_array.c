/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:02:55 by twagner           #+#    #+#             */
/*   Updated: 2021/10/19 16:24:50 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_arg_array(char **array)
{
	while (*array)
	{
		free(*array);
		++array;
	}
	free(array);
}

void	ms_empty_arg_array(char **array)
{
	while (*array)
	{
		free(*array);
		++array;
	}
	*array = NULL;
}

int	ms_add_one_arg(char **array, char *data)
{
	int		i;
	int		ac;
	char	**new;

	ac = 0;
	while (array[ac])
		++ac;
	new = (char **)malloc(sizeof(*new) * (ac + 2));
	if (!new)
	{
		ms_free_arg_array(array);
		return (ERROR);
	}
	new[ac + 1] = NULL;
	i = -1;
	while (array[++i])
		new[i] = ft_strdup(array[i]);
	new[i] = ft_strdup(data);
	ms_empty_arg_array(array);
	*array = new[0];
	/**/
	i = -1;
	while (array[++i])
		printf("NODE : %s\n", array[i]);
	printf("----------\n");
	/**/
	return (0);
}

char	**ms_init_arg_array()
{
	char	**array;

	array = (char **)malloc(sizeof(*array));
	if (!array)
		return (NULL);
	*array = NULL;
	return (array);
}
