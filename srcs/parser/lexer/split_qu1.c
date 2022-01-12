/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:27:01 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/01/12 18:38:54 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_strchr_do(char *arr, int start, int end)
{
	while (arr[start] && start <= end)
	{
		if (arr[start] == '$')
			return (1);
		start++;
	}
	return (0);
}
