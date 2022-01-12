/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:01:04 by wlo               #+#    #+#             */
/*   Updated: 2022/01/12 11:23:43 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	sep(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

int		count_len(char *s)
{
	int len;
	int dq;
	int	sq;

	len = 0;
	dq = 0;
	sq = 0;
	while(*s)
	{
		if (*s == '\"')
			dq++;
		if (*s == '\'')
			sq++;
		if (*s == ' ' && dq%2 == 0 && sq%2 == 0)
			break;
		if (*s == ' ' && dq%2 == 1 && sq%2 == 2)
		 	break;
		if (*s == ' ' && dq%2 == 2 && sq%2 == 1)
		 	break;
		len++;
		s++;
	}
	return (len);
}

int if_quote_close(int *start, int len, char *s)
{
	int sq;
	int dq;
	int status;

	sq = 0;
	dq = 0;
	status = 0;
	while((*start) < len)
	{
		//"iuh'jio'" 不是引號先結束作為判斷...如果不是“‘”’這種情況
		if (s[(*start)] == '\'')
		{
			if (sq == 2)
				break;
			sq++;
		}
		else if (s[(*start)] == '\"')
		{
			if (dq == 2)
				break;
			dq++;
		}
		if (sq == 1 && !status)
			status = 1;
		else if (dq == 1 && !status)
			status = 2;
		(*start) = (*start) + 1;
		if (sq == 2 && status == 1)
			return (1);
		else if (dq == 2 && status == 2)
			return (2);
		if ((sq == 2 && dq == 2)) //為什麼是＆＆不是｜｜
			break ;
	}
	if (sq >= 2 && status == 2 && dq != 0 )
		return (1);
	else if (dq >= 2 && status == 1 && sq != 0)
		return (2);
	return (0);
}
int check_db(char *arr, int start, int end, char c)
{
	int n;

	n = 0;
	while(arr[start] && start <= end)
	{
		if(arr[start] == c)
			n++;
		start++;	
	}
	if(n == 1)
		return (1);
	return (0);
}

int	check_envvar_qu(char *arr, char *new, int begin, int end,int *i_new, int quote)
{
	//如果是有引號的 引號裡面所有的var都要check
	int len_var;
	int temp;

	temp = begin;
	//printf("QU:%s, %d, %d\n", arr, begin, end);
	//printf("QU: %d, %d\n", arr, begin, end);
	while (arr[begin] && begin < end)
	{
		//printf("NEW ADD 1:%d, %d\n", (*i_new), check_db(arr, begin, end, '\"'));
		//printf("chech env in quafter:|%s|, %d, %d, %d\n", arr, begin, end, *i_new);
		if (arr[begin] == '$' && arr[begin + 1])
		{
			len_var = replace_var(&arr[begin + 1], new, i_new);
			(*i_new) = (int)ft_strlen(new);
			begin = begin + len_var + 1;
		} 
		else if ((arr[begin] == '\'' && !check_db(arr, temp, end, '\'') && quote == 1) || (arr[begin] == '\"' && !check_db(arr, temp , end, '\"') && quote == 2))
			begin++;
		else
		{
			new[*i_new] = arr[begin];
			begin++;
			(*i_new) = (*i_new) + 1;
			//printf("chech env in quother1:|%s|, %d, %d, %d\n", new, begin, end, *i_new);			
		}
			
	}
	new[(*i_new) + 1] = '\0';
	(*i_new) = ft_strlen(new);
	return (begin);
}
int	check_envvar(char *arr, char *new, int *i_arr, int *i_new)
{
	int temp;
	int len_var;

	temp = (*i_arr);
	len_var = 0;
	while(arr[temp] != '$')
		temp++;
	if (arr[temp + 1])
		len_var = replace_var(&arr[(temp) + 1], new, i_new);
	(*i_new) = ft_strlen(new);
	(*i_arr) = (*i_arr) + len_var + 1;
	return (len_var);
}
int ft_strchr_do(char *arr, int start, int end)
{
	while(arr[start] && start <= end)
	{
		if (arr[start] == '$')
			return (1);
		start++;
	}
	return (0);
}

int ft_strdb(char *s, char c)
{
	int i;
	int y;

	i = -1;
	y = 0;
	while(s[++i])
	{
		if(s[i] == c)
		{
			while(s[++i])
			{
				if(s[i] == '$')
					return (1);
				if(s[i] == c)
					return (0);
			}
		}
	}
	return (0);
}
//當有quote
void	replace_quote(char *arr, char *new,int *i_arr, int *i_new)
{
	int	quote;
	int temp;
	int	start;

	temp = (*i_arr);
	start = (*i_new);
	quote = if_quote_close(i_arr, ft_strlen(arr) , arr);
	//printf("QU:%d\n", quote);
	while(temp < (*i_arr))
	{
		if (quote == 1 && arr[temp] == '\'')
		{

			//printf("CHECK:%d\n", ft_strdb(arr,'\''));
			if (!ft_strdb(arr,'\'') && ft_strchr_do(arr, temp, (*i_arr)))
				temp = check_envvar_qu(arr, new, temp, *i_arr, i_new, quote);
		}
		else if (quote == 1 && arr[temp] != '\'')
		{
			new[(*i_new)] = arr[temp];
			(*i_new) = (*i_new) + 1;
		}
		else if (quote == 2 && arr[temp] == '\"')
		{
			//printf("quote:%d\n", *i_arr);
			if (ft_strchr_do(arr, temp, (*i_arr)))
				temp = check_envvar_qu(arr, new, temp, *i_arr, i_new, quote);
		}
		else if (quote == 2 && arr[temp] != '\"')
		{
			new[(*i_new)] = arr[temp];
			(*i_new) = (*i_new) + 1;
		}
		else if (quote == 0)
		{
			if (ft_strchr_do(arr, temp, (*i_arr)))
				temp = check_envvar_qu(arr, new, temp, *i_arr, i_new, quote);
			else
			{
				new[(*i_new)] = arr[temp];
				(*i_new) = (*i_new) + 1;
			}
		}
		//printf("NEW in loop:%s, %d\n", new, (*i_new));
		temp++;
	}
	new[(*i_new)+1] = '\0';
	(*i_new) = ft_strlen(new);
	//printf("NEW3:%s, %d\n", new ,(*i_new));
}

void initial(char *new)
{
	int	i;

	i = -1;
	while(++i < 1000)
		new[i] = '\0';
}
char	*check_quote(char *arr)
{
	char new[1000];
	int i_arr;
	int i_new;
	char *try;

	i_arr = 0;
	i_new = 0;
	initial(new);
	while(arr[i_arr])
	{
		if (arr[i_arr] == '\"' || arr[i_arr] == '\'')
			replace_quote(arr, new, &i_arr,&i_new);
		else if (arr[i_arr] == '$')
			check_envvar(arr, new, &i_arr, &i_new);
		else
			new[i_new++] = arr[i_arr++];
		new[i_new] = '\0';
		//printf("IN LOOP:|%s|, |%d|, |%d|\n", new, i_arr, i_new);
	}
	new[i_new] = '\0';
	try =ft_strdup(new);
	if (arr)
		free(arr);
	return (try);
}
int		check_each(char ***arr, int len, char *s, int index)
{
	int i;

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
	int	state;
	int	len;

	index = 0;
	state = 0;
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