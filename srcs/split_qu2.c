/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:22:27 by wlo               #+#    #+#             */
/*   Updated: 2021/10/25 16:25:31 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

int	count_w_qu_2(int state, char *s, char c, int *count)
{
	if (state == 2)
		state = 2;
	else if (state == 3)
		state = 3;
	else if (sep(*s, '\'') == 1)
		state = 2;
	else if (sep(*s, '\"') == 1)
		state = 3;
	else if (state < 2 && sep(*s, c) == 1)
		state = 1;
	else
	{	
		if (state == 1)
			(*count) = (*count) + 1;
		state = 0;
	}
	return (state);
}

int	count_w_qu(char *s, char c)
{
	int	state;
	int	count;

	state = 1;
	count = 0;
	while (*s)
	{
		if (state == 2 && sep(*s, '\'') == 1)
		{
			count++;
			state = 0;
		}
		else if (state == 3 && sep(*s, '\"') == 1)
		{
			count++;
			state = 0;
		}
		else
			state = count_w_qu_2(state, s, c, &count);
		s++;
	}
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
		count++;
		s++;
	}
	return (count);
}

int	int_word(char *s, char c, int index, char ***arr)
{
	int	len_ws;
	int	i;

	len_ws = len_w_qu(s, c);
	if (!len_ws)
		len_ws = len_w_qu(s, '\0');
	(*arr)[index] = (char *)malloc((len_ws + 1) * sizeof(char));
	if (!(*arr)[index])
		return (0);
	i = 0;
	while (*s && i < len_ws)
		(*arr)[index][i++] = *s++;
	(*arr)[index][i] = '\0';
	(*arr)[index] = check_if_envvar((*arr)[index]);
	return (len_ws);
}