/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:01:04 by wlo               #+#    #+#             */
/*   Updated: 2022/01/08 11:38:58 by ifeelbored       ###   ########.fr       */
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
	int status;

	status = 0;
	len = len_w_qu(s, c);
	printf("len: %d,s:%s\n", len ,s);
	(*arr)[index] = (char *)malloc((len + 1) * sizeof(char));
	if (!(*arr)[index])
		return (0);
	i = 0;
	while (*s && i < len)
	{
		if (!status)
		{
			if (*s == '\'')
				status = 1;
			if (*s == '\"')
				status = 2;
		}
		if (status == 0 ||(*s != '\"' && status == 2) ||  (*s != '\'' && status == 1))
		{
			printf("c:%c,status:%d\n", *s, status);
			(*arr)[index][i++] = *s;
		}
		s++;
	}
	(*arr)[index][i] = '\0';
	printf("(*arr)[index][i]:%s\n", (*arr)[index]);
	if (status == 2 || status == 0)
		(*arr)[index] = check_if_envvar((*arr)[index]);
	return (len + 1);
}

char	*ft_split_3_qu(char *s, char c, int *state)
{
	while (*s && (sep(*s, '\'') == 1 || sep(*s, '\"') == 1 || sep(*s, c) == 1))
	{
		if (sep(*s, '\'') == 1)
		{
			printf("1\n");
			s++;
			(*state) = 1;
		}
		if (sep(*s, '\"') == 1)
		{
			printf("2\n");
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

int which_quote(char c)
{
	if (c == '\'')
		return 1;
	if (c == '\"')
		return 2;
	return 0;
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
		//年再一起的引號算同一個字
		if (*s == '\"')
			dq++;
		if (*s == '\'')
			sq++;
		if (*s == ' ' && dq%2 == 0 && sq%2 == 0)//沒有引號
			break;
		if (*s == ' ' && dq%2 == 1 && sq%2 == 2)
		 	break;
		if (*s == ' ' && dq%2 == 2 && sq%2 == 1)
		 	break;
		len++;
		//printf("s:%s, %d: sq:%d, dq:%d\n", s, len, sq, dq);
		s++;
	}
	return (len);
}
int if_quote_close(int *start, int len, char *s)
{
	//是誰先關了？
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
			sq++;
		else if (s[(*start)] == '\"')
			dq++;
		if (sq == 1 && !status)
			status = 1;
		else if (dq == 1 && !status)
			status = 2;
		(*start) = (*start) + 1;
		if (sq == 2 && status == 1)
			return (1);
		else if (dq == 2 && status == 2)
			return (2);
		if (sq == 2 && dq == 2) //為什麼是＆＆不是｜｜
			break ;
	}
	if (sq >= 2 && status == 2)
		return (1);
	else if (dq >= 2 && status == 1)
		return (2);
	return (0);
}
char*	remalloc_forrest(char *arr, char *origi, int len, int index)
{
	char *new;
	int len_total;
	int	i;

	i = -1;
	len_total = ft_strlen(arr) + len - index;
	printf("replce:LEN:%d, len:%d,index:%d\n", len_total, len, index);
	new = malloc(sizeof(char)*(len_total+1));
	if (!new)
		return (NULL);
	while(arr[++i])
		new[i]=arr[i];
	while(index < len && origi[index])
	{
		//printf("replce:%d, %c, %d\n",index, origi[index], i);
		new[i++] = origi[index++];
	}
	new[i]='\0';
	free(origi);
	return (new);

}
char *check_if_envvar_one(char *cmd, char*origi, int index)
{
	char	*new;

	new = NULL;
	while (cmd[index])
	{
		printf("inside:%d, %c\n", index,cmd[index]);
		if (cmd[index] == '$')
		{
			if (cmd[index + 1])
				new = replace_var(&cmd[index + 1], origi, index);
			if (new[0])
				cmd = new;
			else
				cmd = "\0";
			//如果很多var?://如果是空白？
			printf("new :|%s|\n", new);
		}
		index++;
	}
	if (new)
	{
		//free(cmd);
		return (new);
	}
	return (cmd);
}
int		search_mark(char *s, int index)
{
	while(s[index])
	{
		if(s[index] == '$')
			return (index);
		index++;
	}
	return (0);
}
void	replace_quote(char **arr,int start, int len)
{
	int quote;
	char *new;
	int last;
	int x;
	int temp;

	x = -1;
	last = 0;//跟著new(原本)
	new = ft_strdup(*arr);
	quote = if_quote_close(&start, len , new);
	printf("new:%s,quote:%d, start:%d, len:%d\n",(*arr), quote,start,len);
	//new
	while (quote != 0) // 1.完全沒有引號或是跑完引號部分了
	{
		temp = last;
		while(last < start)
		{
			if (quote == 1 && new[last] != '\'')
				(*arr)[++x] = new[last];
			if (quote == 2 && new[last] != '\"')
				(*arr)[++x] = new[last];
			last++;
		}
		//取代var
		if (quote == 2)
		{
			(*arr)[x+1] = '\0';
			printf("ARR:|%s|,|%zu|,|%d|\n",(*arr),ft_strlen(ft_strrchr((*arr), '$')),(int)ft_strlen(*arr)-temp );
			if (ft_strchr((*arr), '$'))
			{
				temp = ft_strlen(ft_strrchr((*arr), '$'));
				(*arr) = check_if_envvar_one((*arr), new, ft_strlen(*arr)-temp);
				x = ft_strlen(*arr);
			}
		}
		last = start;
		quote = if_quote_close(&start, len , new);
		printf("in new:%s,quote:%d, start:%d, len:%d\n",(*arr), quote,start,len);
	}
	//printf("compare:|%s|, |%s|, |%d|, %d\n", new, (*arr), x, ft_strcmp(new, (*arr)));
	// if (x > 0 && (start <= len)	&& !ft_strchr(new, '$'))
	// {
	// 	printf("ADD 0\n");
		(*arr)[x+1] = '\0';
	// }
	if (ft_strcmp(new, (*arr)) == 0)//完全沒有引號的情況
	{
		printf("CHECK:%s,%s\n", new,(*arr));
		if (ft_strchr(new, '$'))
			(*arr)=check_if_envvar(new);
		free(new);
		return ;
	}
	//有引號被調整完後，後面還有cmd  如果後面還有$?? 
	if (ft_strchr(new, '$') && !ft_strchr((*arr), '$') && (new)[last])
	{
		printf("???\n");
		(*arr) = remalloc_forrest((*arr), new, len, last);
	}
	else if ((new)[last])//給沒有引號或是引號裡有var..的後面
	{	
		printf("last:%d, len:%d\n", last, len);
		while (last < len)
			(*arr)[++x]= new[last++];
		(*arr)[x+1]='\0';
		printf("last:%d, i:%d\n", last, x);
	}
	printf("new:%s\n",(*arr));
}
int		check_quote(char ***arr, int len, char *s, int index)
{
	int i;
	int status;

	i = 0;
	status = 0;
	(*arr)[index] = (char *)malloc((len + 1) * sizeof(char));
	if (!(*arr)[index])
		return (0);
	//複製字 判斷quote需要複製？
	//要一起處理quote跟var嗎？
	while (*s && i < len)
	{		
		(*arr)[index][i++] = *s;
		s++;
	}
	(*arr)[index][i] = '\0';
	printf("(*arr)[index][i]:%s\n", (*arr)[index]);
	replace_quote(&(*arr)[index], status, len);
	// if (status == 2 || status == 0)
	// 	(*arr)[index] = check_if_envvar((*arr)[index]);
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
		printf("befor :%s\n", s);
		while (*s == ' ')
				s++;
		// s = ft_split_3_qu(s, ' ', &state);
		len = count_len(s);
		printf("len:%d\n", len);
		check_quote(arr, len, s, index);
		//if (!replace_quote(arr, len, s, index))

		// if (state == 0)
		// 	len = int_word(s, ' ', index, arr);
		// else if (state == 1)
		// {
		// 	len = int_quote(s - 1, '\'', index, arr);
		// 	state = 0;
		// }
		// else
		// {
		// 	len = int_quote(s - 1, '\"', index, arr);
		// 	state = 0;
		// }
		s = s + len + 1;
		//printf("arr[index]:%s\n", (*arr)[index]);
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
	printf("count words:%d\n", count_ws);
	arr = (char **)malloc((count_ws + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	ft_split_2_qu(&arr, s, count_ws);
	return (arr);
}
