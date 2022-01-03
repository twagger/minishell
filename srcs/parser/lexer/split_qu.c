/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:01:04 by wlo               #+#    #+#             */
/*   Updated: 2022/01/03 21:34:13 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	sep(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

int	int_quote(char *s, char c, int index, char ***arr)
{
	int	len;
	int	i;

	len = len_w_qu(s, c);
	//printf("len: %d\n", len);
	(*arr)[index] = (char *)malloc((len + 1) * sizeof(char));
	if (!(*arr)[index])
		return (0);
	i = 0;
	while (*s && i < len)
	{
		if ((*s != '\"' && c == '\"') || (*s != '\'' && c == '\''))
			(*arr)[index][i++] = *s;
		s++;
	}
	(*arr)[index][i] = '\0';
	if (c == '\"' || c == ' ')
		(*arr)[index] = check_if_envvar((*arr)[index]);
	return (len + 1);
}

char	*ft_split_3_qu(char *s, char c, int *state)
{
	while (*s && (sep(*s, '\'') == 1 || sep(*s, '\"') == 1 || sep(*s, c) == 1))
	{
		if (sep(*s, '\'') == 1)
		{
			s++;
			(*state) = 1;
		}
		if (sep(*s, '\"') == 1)
		{
			s++;
			(*state) = 2;
		}
		else if (sep(*s, c) == 1 && (*state) == 0)
			s++;
		else
			break ;
	}
	return (s);
}

void	ft_split_2_qu(char ***arr, char *s, char c, int count_ws)
{
	int	index;
	int	state;
	int	len;

	index = 0;
	state = 0;
	while (index < count_ws)
	{
		//printf("befor :%s , state:%d\n", s, state);
		s = ft_split_3_qu(s, c, &state);
		//printf("after :%s , state:%d\n", s, state);
		if (state == 0)
			len = int_word(s, c, index, arr);
		else if (state == 1)
		{
			len = int_quote(s, '\'', index, arr);
			state = 0;
		}
		else
		{
			len = int_quote(s, '\"', index, arr);
			state = 0;
		}
		s = s + len;
		//printf("arr[index]:%s\n", (*arr)[index]);
		index++;
	}
	(*arr)[index] = 0;
}

char	**ft_split_qu(char *s, char c)
{
	char	**arr;
	int		count_ws;

	if (!s)
		return (0);
	count_ws = count_w_qu(s);
	//printf("count words:%d\n", count_ws);
	arr = (char **)malloc((count_ws + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	ft_split_2_qu(&arr, s, c, count_ws);
	return (arr);
}
