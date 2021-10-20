/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:01:04 by wlo               #+#    #+#             */
/*   Updated: 2021/10/20 16:30:34 by wlo              ###   ########.fr       */
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
		if (state == 2 && (if_sep(*s, '\'') == 1 || if_sep(*s, '\"') == 1))
		{
			count++;
			state = 0;
		}
		else if ((if_sep(*s, '\'') == 1 || if_sep(*s, '\"') == 1) || state == 2)
			state = 2;
		else if (state != 2 && if_sep(*s, c) == 1)
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
	(*arr)[index] = (char *)malloc((len_ws + 1) * sizeof(char));
	if (!(*arr)[index])
		return (0);
	i = 0;
	while (*s && i < len_ws)
		(*arr)[index][i++] = *s++;
	(*arr)[index][i] = '\0';
	return (len_ws);
}

int	int_quote(char *s, int index, char ***arr)
{
	int	len_ws_1;
	int	len_ws_2;
	int	len;
	int	i;

	len_ws_1 = len_w_qu(s, '\'');
	len_ws_2 = len_w_qu(s, '\"');
	if (len_ws_1 < len_ws_2)
		len = len_ws_1;
	else
		len = len_ws_2;
	(*arr)[index] = (char *)malloc((len + 1) * sizeof(char));
	if (!(*arr)[index])
		return (0);
	i = 0;
	while (*s && i < len)
		(*arr)[index][i++] = *s++;
	(*arr)[index][i] = '\0';
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
		while (*s && (((if_sep(*s, '\'' == 1) || if_sep(*s, '\"') == 1)) 
				|| if_sep(*s, c) == 1))
		{
			if((if_sep(*s, '\'' == 1) || if_sep(*s, '\"') == 1))
			{
				s++;
				state = 1;
			}
			else if (if_sep(*s, c) == 1 && state == 0)
				s++;
		}
		if (state == 0)
			len = int_word(s, c, index, arr);
		else
		{
			len = int_quote(s, index, arr);
			state = 0;
		}
		s = s + len;
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