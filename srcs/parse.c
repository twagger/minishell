/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:57:26 by twagner           #+#    #+#             */
/*   Updated: 2021/10/13 16:37:14 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Basic parser to allow Tom to work on exec
*/
int		check_special_char(char *c, char *line)
{
	int sq;
	int dq;

	sq = 0;
	dq = 0;
	while(*c)
	{
		if (*c == '\\' || *c == ';')
			return (1);
		c++;
	}
	while(*line)
	{
		if (*line == '\'')
			sq++;
		else if (*line == '\"')
			dq++;
		line++;
	}
	if (sq % 2 || dq % 2)
		return (1);
	return (0);
}

char	**ms_parser(char *line)
{
	char	**res;
	int		i;

	i = -1;
	res = ft_split(line, ' ');
	while(res[++i])
	{
		if(check_special_char(res, line))
			return (0);
	}
	return (res);
}
