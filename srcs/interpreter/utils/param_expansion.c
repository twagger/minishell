/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:25:08 by twagner           #+#    #+#             */
/*   Updated: 2022/01/17 19:13:01 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

static int	ms_get_doll_len(char *str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (ft_isalnum((int)str[i]) || str[i] == '_')
			++i;
		else
			break ;
	}
	return (i);
}

static char	*ms_exp(char *str, int len)
{
	char	*original;
	char	*expanded;

	original = (char *)malloc(sizeof(*original) * len);
	if (!original)
		return (NULL);
	ft_strlcpy(original, str + 1, len);
	original[len - 1] = 0;
	expanded = ms_getenv(original);
	free(original);
	return (expanded);
}

char	*ms_update_hd(char *before, char *expanded, char *after, int len)
{
	char	*result;
	char	*step_1;

	if (!before || !after)
		return (NULL);
	if (len == 1)
	{
		step_1 = ft_strjoin(before, "$");
		if (!step_1)
			return (NULL);
		result = ft_strjoin(step_1, after);
		free(step_1);
		return (result);
	}
	else if (!expanded)
		return (ft_strjoin(before, after));
	step_1 = ft_strjoin(before, expanded);
	if (!step_1)
		return (NULL);
	result = ft_strjoin(step_1, after);
	free(step_1);
	return (result);
}

int	ms_param_expansion(char **str, int to_expand)
{
	int		i;
	int		len;
	char	*before;
	char	*after;
	char	*tmp;

	i = -1;
	while (!to_expand && (*str)[++i])
	{
		if ((*str)[i] == '$')
		{
			len = ms_get_doll_len((*str + i));
			before = ft_substr(*str, 0, i);
			after = ft_substr(*str, i + len, ft_strlen(*str) - (i + len));
			tmp = *str;
			*str = ms_update_hd(before, ms_exp((*str + i), len), after, len);
			free(tmp);
			free(before);
			free(after);
			if (!*str)
				return (ERROR);
		}
	}
	return (0);
}
