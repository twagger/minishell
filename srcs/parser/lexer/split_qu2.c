/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:04:13 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/01/17 11:48:15 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	sep(char s)
{
	if (s == ' ' || s == '>' || s == '<' || s == '|')
		return (1);
	return (0);
}

int	count_sep(char *s, int len)
{
	while (sep(*s) && (*s) != ' ')
	{
		s++;
		len++;
	}
	return (len);
}

int	count_len(char *s)
{
	int		len;
	t_quote	q;
	int		i;

	len = 0;
	i = -1;
	initial_quote(&q);
	while (s[++i])
	{
		if (s[i] == '\"')
			q.dq++;
		if (s[i] == '\'')
			q.sq++;
		if (sep(s[i]) && q.dq % 2 == 0 && q.sq % 2 == 0)
			break ;
		if (sep(s[i]) && q.dq % 2 == 1 && q.sq % 2 == 2)
			break ;
		if (sep(s[i]) && q.dq % 2 == 2 && q.sq % 2 == 1)
			break ;
		len++;
	}
	if (sep(*s))
		len = count_sep(s, len);
	return (len);
}

int	db(char *arr, int start, int end, char c)
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

	i = -1;
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
