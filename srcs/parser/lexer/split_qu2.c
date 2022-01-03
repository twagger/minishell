/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:26:04 by twagner           #+#    #+#             */
/*   Updated: 2022/01/03 12:38:32 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int check_quote(char c, char *s , int index, int state)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (++i < index - 1)
	{
		if (s[i] == c)
			count++;
	}
	if (s[index - 1] && count % 2 == 1)
		return (state);
	else if (s[index - 1] && s[index - 1] != ' ')
		return (state);
	else if (c == '\'')
		state = 2;
	else if (c == '\"')
		state = 3;
	return (state);
}

int	count_w_qu_2(int state, char *s, int *count, int index)
{
	if (state == 3 && sep(s[index], '\"') == 1)
	{
		(*count) = (*count) + 1;
		state = 0;
	}
	else if (state == 2)
		state = 2;
	else if (state == 3)
		state = 3;
	else if (sep(s[index], '\'') == 1)
		state = check_quote('\'', s, index, state);	
	else if (sep(s[index], '\"') == 1)
		state = check_quote('\"', s, index, state);
	else if (state < 2 && sep(s[index - 1], ' ') == 1)
		state = 1;
	else
	{	
		if (state == 1)
			(*count) = (*count) + 1;
		state = 0;
	}
	return (state);
}

int	count_w_qu(char *s)
{
	int	state;
	int	count;
	int index;

	state = 1;
	count = 0;
	index = -1;
	while (s[++index])
	{
		if (state == 2 && sep(s[index], '\'') == 1)
		{
			count++;
			state = 0;
		}
		else
			state = count_w_qu_2(state, s, &count, index);
			//printf("state:%d, %d\n, ", state, count);
	}
	if (s[index - 1] && state == 1)
		count++;
	return (count);
}

char	*ft_searchchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (0);
}

int	len_w_qu(char *s, char c)
{
	int	count;

	count = 0;
	if (!ft_strchr(s, (int)c))
		return (0);
	while (*s && sep(*s, c) == 0)
	{
		if (*s ! '\'' && *s != '\"')
			count++;
		s++;
	}
	// while (*s && sep(*s, ' ') == 0)
	// {
	// 	if (*s != ' ')
	// 		count++;
	// 	s++;
	// }
	return (count);
}

int	int_word(char *s, char c, int index, char ***arr)
{
	int	len_ws;
	int	i;

	len_ws = len_w_qu(s, c);
	printf("len: %d\n", len_ws);
	if (!len_ws)
		len_ws = len_w_qu(s, '\0');
	(*arr)[index] = (char *)malloc((len_ws + 1) * sizeof(char));
	if (!(*arr)[index])
		return (0);
	i = 0;
	while (*s && i < len_ws)
	{
		//if (*s != '\"' && *s != '\'')
		(*arr)[index][i++] = *s++;
	}
	(*arr)[index][i] = '\0';
	(*arr)[index] = check_if_envvar((*arr)[index]);
	return (len_ws);
}
