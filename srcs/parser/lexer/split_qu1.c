/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:27:01 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/01/13 17:49:03 by ifeelbored       ###   ########.fr       */
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

int	ft_strcmp_exit(char *s, char *c)
{
	int	i;
	int	n;
	int	len1;
	int	len2;

	i = 0;
	n = 0;
	len1 = ft_strlen(s);
	len2 = ft_strlen(c);
	while (s[i])
	{
		if (s[i] == '$' && i + len2 <= len1 && !ft_strncmp(&s[i], c, len2))
		{
			n++;
			i = i + 22;
		}
		else
			i++;
	}
	return (n);
}

void	free_arr(char *arr, char *exit)
{
	if (arr)
		free(arr);
	if (exit)
		free(exit);
}

int	len_int(const char *s)
{
	int	length;

	length = 0;
	while (*s)
	{
		++length;
		s++;
	}
	return (length);
}

char	*re_exitcode(char *a, char *exit, char *c)
{
	char	*new;
	int		x;
	int		y;
	int		n;

	y = 0;
	x = 0;
	n = ft_strcmp_exit(a, c);
	new = (char *)malloc((ft_strlen(a) - n * 22 + ft_strlen(exit) * n + 1));
	if (!new)
		return (NULL);
	while (a[x])
	{	
		if (a[x] == '$' && x + 22 <= len_int(a) && !ft_strncmp(&a[x], c, 22))
		{
			ft_strcpy(&new[y], exit);
			x = x + 22;
			y = y + ft_strlen(exit);
		}
		else
			new[y++] = a[x++];
	}
	new[y] = '\0';
	free_arr(a, exit);
	return (new);
}
