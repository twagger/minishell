/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:01:04 by wlo               #+#    #+#             */
/*   Updated: 2022/01/14 15:57:33 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_envvar(char *arr, char *new, int *i_arr, int *i_new)
{
	int	temp;
	int	len_var;

	temp = (*i_arr);
	len_var = 0;
	while (arr[temp] != '$')
		temp++;
	if (arr[temp + 1])
		len_var = replace_var(&arr[(temp) + 1], new, i_new);
	(*i_new) = ft_strlen(new);
	(*i_arr) = (*i_arr) + len_var;
	return (len_var);
}

char	*check_quote(char *arr)
{
	char	new[1000];
	int		i_arr;
	int		i_new;
	char	*try;

	i_arr = 0;
	i_new = 0;
	initial(new);
	while (arr[i_arr])
	{
		if (arr[i_arr] == '\"' || arr[i_arr] == '\'')
			replace_quote(arr, new, &i_arr, &i_new);
		else if (arr[i_arr] == '$')
			check_envvar(arr, new, &i_arr, &i_new);
		else
			new[i_new++] = arr[i_arr++];
		new[i_new] = '\0';
	}
	new[i_new] = '\0';
	try = ft_strdup(new);
	if (arr)
		free(arr);
	return (try);
}

int	check_each(char ***arr, int len, char *s, int index)
{
	int	i;

	i = 0;
	(*arr)[index] = (char *)malloc((len + 1) * sizeof(char));
	if (!(*arr)[index])
		return (0);
	while (i < len)
	{		
		(*arr)[index][i++] = *s;
		s++;
	}
	(*arr)[index][i] = '\0';
	(*arr)[index] = check_quote((*arr)[index]);
	return (len);
}

void	ft_split_2_qu(char ***arr, char *s, int count_ws)
{
	int	index;
	int	len;

	index = 0;
	while (index < count_ws)
	{
		while (*s == ' ')
			s++;
		len = count_len(s);
		check_each(arr, len, s, index);
		s = s + len + 1;
		index++;
	}
	(*arr)[index] = 0;
}

char	**ft_split_qu(char *s, char c)
{
	char	**arr;
	int		count_ws;

	(void)c;
	if (!s)
		return (0);
	count_ws = count_w_qu(s);
	arr = (char **)malloc((count_ws + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	ft_split_2_qu(&arr, s, count_ws);
	return (arr);
}
