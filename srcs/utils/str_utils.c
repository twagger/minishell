/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:25:31 by twagner           #+#    #+#             */
/*   Updated: 2022/01/15 10:10:05 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_str_array(char **str)
{
	char	**begin;

	if (str)
	{
		begin = str;
		while (*str)
		{
			free(*str);
			++str;
		}
		free(begin);
	}
}

void	*ms_free_str_array_null(char **str)
{
	ms_free_str_array(str);
	return (NULL);
}
