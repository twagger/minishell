/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:22:12 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/01/20 11:26:04 by ifeelbored       ###   ########.fr       */
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

int	ck_envvar_qu(t_cd c, char *new, int *i_new, t_q i)
{
	int	len_var;
	int	tp;

	tp = i.b;
	while (c.ar[i.b] && i.b < i.e)
	{
		if (c.ar[i.b] == '$' && c.ar[i.b + 1])
		{
			len_var = replace_var((t_cd){&c.ar[i.b + 1], c.code}, new, i_new);
			(*i_new) = (int)ft_strlen(new);
			i.b = i.b + len_var + 1;
		}
		else if ((c.ar[i.b] == '\'' && !db(c.ar, tp, i.e, '\'') && i.q == 1) || \
				(c.ar[i.b] == '\"' && !db(c.ar, tp, i.e, '\"') && i.q == 2))
			i.b++;
		else
		{
			new[*i_new] = c.ar[i.b];
			i.b++;
			(*i_new) = (*i_new) + 1;
		}		
	}
	new[(*i_new) + 1] = '\0';
	(*i_new) = ft_strlen(new);
	return (i.b);
}

int	replace_quote_2(t_cd cd, char *new, int *i_new, t_q index)
{
	if ((index.q == 1 && cd.ar[index.b] != '\'') || \
		(index.q == 2 && cd.ar[index.b] != '\"'))
	{
		new[(*i_new)] = cd.ar[index.b];
		(*i_new) = (*i_new) + 1;
	}
	else if (index.q == 2 && cd.ar[index.b] == '\"')
	{
		if (ft_strchr_do(cd.ar, index.b, index.e))
			index.b = ck_envvar_qu(cd, new, i_new, index);
	}
	else if (index.q == 0)
	{
		if (ft_strchr_do(cd.ar, index.b, index.e))
			index.b = ck_envvar_qu(cd, new, i_new, index);
		else
		{
			new[(*i_new)] = cd.ar[index.b];
			(*i_new) = (*i_new) + 1;
		}
	}
	return (index.b);
}

int	replace_quote(t_cd cd, char *new, int *i_arr, int *i_new)
{
	int	qt;
	int	temp;
	int	if_qu;

	temp = (*i_arr);
	if_qu = 0;
	qt = if_quote_close(i_arr, ft_strlen(cd.ar), cd.ar);
	if (qt == 1 || qt == 2)
		if_qu = 1;
	while (temp < (*i_arr))
	{
		if (qt == 1 && cd.ar[temp] == '\'')
		{
			if (!ft_strdb(cd.ar, '\'') && ft_strchr_do(cd.ar, temp, (*i_arr)))
				temp = ck_envvar_qu(cd, new, i_new, (t_q){temp, *i_arr, qt});
		}
		else
			temp = replace_quote_2(cd, new, i_new, (t_q){temp, (*i_arr), qt});
		temp++;
	}
	new[(*i_new) + 1] = '\0';
	(*i_new) = ft_strlen(new);
	return (if_qu);
}
