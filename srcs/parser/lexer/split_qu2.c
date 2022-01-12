/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:04:13 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/01/12 18:38:42 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	sep(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

int	count_len(char *s)
{
	int	len;
	int	dq;
	int	sq;

	len = 0;
	dq = 0;
	sq = 0;
	while (*s)
	{
		if (*s == '\"')
			dq++;
		if (*s == '\'')
			sq++;
		if (*s == ' ' && dq % 2 == 0 && sq % 2 == 0)
			break ;
		if (*s == ' ' && dq % 2 == 1 && sq % 2 == 2)
			break ;
		if (*s == ' ' && dq % 2 == 2 && sq % 2 == 1)
			break ;
		len++;
		s++;
	}
	return (len);
}

int	ck_db(char *arr, int start, int end, char c)
{
	int	n;

	n = 0;
	while (arr[start] && start <= end)
	{
		if (arr[start] == c)
			n++;
		start++;
	}
	if (n == 1)
		return (1);
	return (0);
}

int	ft_strdb(char *s, char c)
{
	int	i;
	int	y;

	i = -1;
	y = 0;
	while (s[++i])
	{
		if (s[i] == c)
		{
			while (s[++i])
			{
				if (s[i] == '$')
					return (1);
				if (s[i] == c)
					return (0);
			}
		}
	}
	return (0);
}

void	initial(char *new)
{
	int	i;

	i = -1;
	while (++i < 1000)
		new[i] = '\0';
}
