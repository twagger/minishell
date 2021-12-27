/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:23 by twagner           #+#    #+#             */
/*   Updated: 2021/12/27 18:30:50 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo(int ac, char **av)
{
	int	i;
	int	nl;
	int	first;

	nl = 0;
	first = 1;
	i = 0;
	if (av[1] && !ft_strncmp(av[1], "-n", 3))
	{
		nl = 1;
		++i;
	}
	while (++i < ac)
	{
		if (!first)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(av[i], 1);
		if (first)
			first = 0;
	}
	if (ac > 1 && !nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
