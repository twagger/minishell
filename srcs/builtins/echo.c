/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:23 by twagner           #+#    #+#             */
/*   Updated: 2021/11/26 22:36:37 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo(int ac, char **av)
{
	int		i;
	char	nl;
	char	sep;

	nl = '\n';
	sep = '\0';
	i = 0;
	while (++i < ac)
	{
		if (i == 1 && !ft_strncmp(av[i], "-n", 3))
			nl = '\0';
		else
		{
			ft_putchar_fd(sep, 1);
			ft_putstr_fd(av[i], 1);
			sep = ' ';
		}
	}
	if (ac > 1)
		ft_putchar_fd(nl, 1);
	return (0);
}
