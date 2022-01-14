/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:22:12 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/01/14 15:58:54 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	if_quote_close_2(int *start, char *s, t_quote *qu)
{
	if (s[(*start)] == '\'')
	{
		if (qu->sq == 2)
			return (0);
		qu->sq++;
	}
	else if (s[(*start)] == '\"')
	{
		if (qu->dq == 2)
			return (0);
		qu->dq++;
	}
	return (1);
}

int	if_quote_close(int *start, int len, char *s)
{
	t_quote	qu;

	initial_quote(&qu);
	while ((*start) < len)
	{
		if (!if_quote_close_2(start, s, &qu))
			break ;
		if (qu.sq == 1 && !qu.state)
			qu.state = 1;
		else if (qu.dq == 1 && !qu.state)
			qu.state = 2;
		(*start) = (*start) + 1;
		if (qu.sq == 2 && qu.state == 1)
			return (1);
		else if (qu.dq == 2 && qu.state == 2)
			return (2);
		if ((qu.sq == 2 && qu.dq == 2))
			break ;
	}
	if (qu.sq >= 2 && qu.state == 2 && qu.dq != 0)
		return (1);
	else if (qu.dq >= 2 && qu.state == 1 && qu.sq != 0)
		return (2);
	return (0);
}

int	ck_envvar_qu(char *ar, char *new, int *i_new, t_q i)
{
	int	len_var;
	int	tp;

	tp = i.b;
	while (ar[i.b] && i.b < i.e)
	{
		if (ar[i.b] == '$' && ar[i.b + 1])
		{
			len_var = replace_var(&ar[i.b + 1], new, i_new);
			(*i_new) = (int)ft_strlen(new);
			i.b = i.b + len_var;
		}
		else if ((ar[i.b] == '\'' && !ck_db(ar, tp, i.e, '\'') && i.q == 1) || \
				(ar[i.b] == '\"' && !ck_db(ar, tp, i.e, '\"') && i.q == 2))
			i.b++;
		else
		{
			new[*i_new] = ar[i.b];
			i.b++;
			(*i_new) = (*i_new) + 1;
		}		
	}
	new[(*i_new) + 1] = '\0';
	(*i_new) = ft_strlen(new);
	return (i.b);
}

int	replace_quote_2(char *arr, char *new, int *i_new, t_q index)
{
	if ((index.q == 1 && arr[index.b] != '\'') || \
		(index.q == 2 && arr[index.b] != '\"'))
	{
		new[(*i_new)] = arr[index.b];
		(*i_new) = (*i_new) + 1;
	}
	else if (index.q == 2 && arr[index.b] == '\"')
	{
		if (ft_strchr_do(arr, index.b, index.e))
			index.b = ck_envvar_qu(arr, new, i_new, index);
	}
	else if (index.q == 0)
	{
		if (ft_strchr_do(arr, index.b, index.e))
			index.b = ck_envvar_qu(arr, new, i_new, index);
		else
		{
			new[(*i_new)] = arr[index.b];
			(*i_new) = (*i_new) + 1;
		}
	}
	return (index.b);
}

void	replace_quote(char *arr, char *new, int *i_arr, int *i_new)
{
	int	qt;
	int	temp;

	temp = (*i_arr);
	qt = if_quote_close(i_arr, ft_strlen(arr), arr);
	while (temp < (*i_arr))
	{
		if (qt == 1 && arr[temp] == '\'')
		{
			if (!ft_strdb(arr, '\'') && ft_strchr_do(arr, temp, (*i_arr)))
				temp = ck_envvar_qu(arr, new, i_new, (t_q){temp, *i_arr, qt});
		}
		else
			temp = replace_quote_2(arr, new, i_new, (t_q){temp, (*i_arr), qt});
		temp++;
	}
	new[(*i_new) + 1] = '\0';
	(*i_new) = ft_strlen(new);
}
