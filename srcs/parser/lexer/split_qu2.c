/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:26:04 by twagner           #+#    #+#             */
/*   Updated: 2022/01/10 15:38:38 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

typedef struct s_quote
{
	int				sq;
	int				dq;
	int 			state;
	int				last_id;
} t_quote;

void initial_quote(t_quote *quote)
{
	quote->sq = 0;
	quote->dq = 0;
	quote->last_id = 0;
}
int	srch_sp_inqu(char *s, char c)
{
	int i;

	i = -1;
	while(s[++i])
	{
		if(s[i] == ' ')
			return (1);
		else if (s[i] == c)
			return (0);
	}
	return (0);
}

t_quote	count_w_qu_2(t_quote *quote, char *s, int *count, int index)
{
	if (quote->dq == 1 && sep(s[index], '\"') == 1)
	{
		quote->last_id=index+1;
		if(srch_sp_inqu(&s[quote->last_id], '\"') == 0 && s[index + 1] == '\0')
			(*count) = (*count) + 1;
		initial_quote(quote);
		quote->state = 0;
	}
	else if (quote->state == 2)
		quote->state = 2;
	else if (sep(s[index], '\"') == 1)
	{	
		quote->state = 2;
		quote->dq++;
	}
	else if (sep(s[index], '\'') == 1)
	{
		quote->state = 2;
		quote->sq++;
	}
	else
		quote->state = 1;
	return (*quote);
}

int	count_w_qu(char *s)
{
	int	count;
	int index;
	t_quote quote;

	count = 0;
	index = -1;
	initial_quote(&quote);
	quote.state = 1;
	while (s[++index])
	{
		if (quote.state < 2 && sep(s[index], ' ') == 1)
		{
			if (s[index -1]&& s[index -1] != ' ')
				count++;
			quote.state = 1;
		}
		else if (quote.sq == 1 && sep(s[index], '\'') == 1)
		{
			quote.last_id=index+1;
			if(srch_sp_inqu(&s[quote.last_id], '\'') == 0 && s[index + 1] == '\0')
				count++;	
			initial_quote(&quote);
			quote.state = 0;
		}
		else
			quote = count_w_qu_2(&quote, s, &count, index);
	}
	if (quote.state == 1 || quote.state == 2)
		count++;
	return (count);
}