/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_wd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:10:55 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/01/17 00:39:09 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	initial_quote(t_quote *quote)
{
	quote->sq = 0;
	quote->dq = 0;
	quote->state = 0;
	quote->last_id = 0;
}

int	srch_sp_inqu(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == ' ')
			return (1);
		else if (s[i] == c)
			return (0);
	}
	return (0);
}
