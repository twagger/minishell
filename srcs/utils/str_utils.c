/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:25:31 by twagner           #+#    #+#             */
/*   Updated: 2021/12/30 14:59:27 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_str_array(char **str)
{
	if (str)
	{
		while (*str)
		{
			free(*str);
			++str;
		}
	}
}

void	*ms_free_str_array_null(char **str)
{
	ms_free_str_array(str);
	return (NULL);
}
