/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:01:04 by wlo               #+#    #+#             */
/*   Updated: 2022/01/20 17:31:34 by ifeelbored       ###   ########.fr       */
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

void	initial(char *new)
{
	int	i;

	i = -1;
	while (++i < 1000)
		new[i] = '\0';
}

int	check_envvar(t_cd cd, char *new, int *i_arr, int *i_new)
{
	int	temp;
	int	len_var;

	temp = (*i_arr);
	len_var = 0;
	while (cd.ar[temp] != '$')
		temp++;
	if (cd.ar[temp + 1])
		len_var = replace_var((t_cd){&cd.ar[(temp) + 1], cd.code}, new, i_new);
	else
	{
		new[0] = '$';
		new[1] = '\0';
		len_var = 0;
	}
	(*i_new) = ft_strlen(new);
	(*i_arr) = (*i_arr) + len_var + 1;
	return (len_var);
}

t_token	*check_quote(char *arr, int *if_qu, char *code)
{
	char	new[1000];
	int		i_arr;
	int		i_new;
	char	*try;
	t_token	*token;

	i_arr = 0;
	i_new = 0;
	initial(new);
	while (arr[i_arr])
	{
		if (arr[i_arr] == '\"' || arr[i_arr] == '\'')
			*if_qu = replace_quote((t_cd){arr, code}, new, &i_arr, &i_new);
		else if (arr[i_arr] == '$')
			check_envvar((t_cd){arr, code}, new, &i_arr, &i_new);
		else
			new[i_new++] = arr[i_arr++];
		new[i_new] = '\0';
	}
	free(arr);
	if (!ft_strcmp(new, "\0") && *if_qu == 0)
		return (NULL);
	try = ft_strdup(new);
	token = ft_newtoken(try, *if_qu);
	return (token);
}

t_token	*check_each(int len, char *s, char *code)
{
	int		i;
	char	*arr;
	int		if_qu;
	t_token	*current;

	i = 0;
	if_qu = 0;
	arr = (char *)malloc((len + 1) * sizeof(char));
	if (!arr)
		return (0);
	while (i < len)
	{		
		arr[i++] = *s;
		s++;
	}
	arr[i] = '\0';
	current = check_quote(arr, &if_qu, code);
	return (current);
}
