/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:01:04 by wlo               #+#    #+#             */
/*   Updated: 2022/01/16 23:57:56 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	try = ft_strdup(new);
		token = ft_newtoken(try, *if_qu);
	if (arr)
		free(arr);
	return (token);
}

t_token	*check_each(int len, char *s, char *code)
{
	int	i;
	char *arr;
	int if_qu;
	t_token *current;

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
void printf_token(t_token *token)
{
	while(token->next)
	{
		printf("value:%s, %d\n", token->value, token->qt_rm);
		token = token->next;
	}
	printf("value:%s, %d\n", token->value, token->qt_rm);
}

t_token	*ft_split_qu(char *s, char *code)
{
	t_token	*all;
	t_token *current;
	int len ;

	if (!s)
		return (0);
	all = 0;
	while (*s)
	{
		while (*s == ' ' && *s)
			s++;
		len = count_len(s);
		if (!len)
			break ;
		current = check_each(len, s, code);
		printf("current:%s, %d\n", (char*)current->value, current->qt_rm);
		ft_tokenadd_back(&all, current);
		s = s + len;
	}
	return (all);
}
