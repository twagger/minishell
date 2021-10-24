/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:01:04 by wlo               #+#    #+#             */
/*   Updated: 2021/10/21 15:38:57 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

int	if_sep(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

int	count_w_qu(char *s, char c)
{
	int	state;
	int	count;

	state = 1;
	count = 0;
	while (*s)
	{
		//printf("c:%d, state:%d, char:%c\n", count, state, *s);
		if (state == 2 && if_sep(*s, '\'') == 1)
		{
			count++;
			state = 0;
		}
		else if (state == 3 && if_sep(*s, '\"') == 1)
		{
			count++;
			state = 0;
		}
		else if (state == 2)
			state = 2;
		else if (state == 3)
			state = 3;
		else if (if_sep(*s, '\'') == 1)
			state = 2;
		else if (if_sep(*s, '\"') == 1)
			state = 3;	
		else if (state < 2 && if_sep(*s, c) == 1)
			state = 1;
		else
		{	
			if (state == 1)
				count++;
			state = 0;
		}
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
	while (*s && if_sep(*s, c) == 0)
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
	//printf("here\n");
	return (len_ws);
}

int	int_quote(char *s, char c,int index, char ***arr)
{
	int	len;
	int	i;

	len = len_w_qu(s, c);
	(*arr)[index] = (char *)malloc((len + 1) * sizeof(char));
	if (!(*arr)[index])
		return (0);
	i = 0;
	while (*s && i < len)
		(*arr)[index][i++] = *s++;
	(*arr)[index][i] = '\0';
	//printf("qoute:%s\n", (*arr)[index]);
	return (len + 1);
}

void	ft_split_2_qu(char ***arr, char *s, char c, int count_ws)
{
	int	index;
	int	len_ws;
	int	i;
	int	state;
	int	len;

	index = 0;
	state = 0;
	while (index < count_ws)
	{
		while (*s && (if_sep(*s, '\'') == 1 || if_sep(*s, '\"') == 1 || if_sep(*s, c) == 1))
		{
			if(if_sep(*s, '\'') == 1)
			{
				s++;
				state = 1;
			}
			if(if_sep(*s, '\"') == 1)
			{
				s++;
				state = 2;
			}
			else if (if_sep(*s, c) == 1 && state == 0)
				s++;
			else
				break ;
		}
		if (state == 0)
			len = int_word(s, c, index, arr);
		else if (state == 1)
		{
			len = int_quote(s, '\'', index, arr);
			state = 0;
		}
		else
		{
			len = int_quote(s, '\"', index, arr);
			//replace var
			(*arr)[index] = check_if_envvar((*arr)[index]);
			state = 0;
		}
		s = s + len;
		//printf("index:%s\n",(*arr)[index]);
		index++;
	}
	(*arr)[index] = 0;
}

char	**ft_split_qu(char *s, char c)
{
	char	**arr;
	int		count_ws;

	if (!s)
		return (0);
	count_ws = count_w_qu(s, c);
	printf("count:%d\n", count_ws);
	arr = (char **)malloc((count_ws + 1) * sizeof(char *));
	if (!arr)
		return (0);
	ft_split_2_qu(&arr, s, c, count_ws);
	return (arr);
}

// int main()
// {
// 	char **arr;
// 	int i = 0;
// 	arr = ft_split_qu("echo \"how are you? \"\"firend\" || && >> file \'$USER\' ", ' ');
// 	while(arr[i])
// 	{
// 		printf("arr:%s\n", arr[i]);
// 		i++;
// 	}
// 	return 0;
// }