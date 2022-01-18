/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:23 by twagner           #+#    #+#             */
/*   Updated: 2022/01/18 09:48:17 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_is_newline_param(char *param)
{
	int	i;

	if (!ft_strcmp(param, "-n"))
		return (1);
	if (param[0] == '-' && param[1] == 'n')
	{
		i = 1;
		while (param[++i])
		{
			if (param[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

int	ms_echo(int ac, char **av)
{
	int	i;
	int	nl;
	int	first;

	nl = 1;
	first = 1;
	i = 0;
	while (av[++i] && ms_is_newline_param(av[i]))
		nl = 0;
	while (i < ac)
	{
		if (!first)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(av[i], 1);
		if (first)
			first = 0;
		++i;
	}
	if (ac >= 1 && nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
