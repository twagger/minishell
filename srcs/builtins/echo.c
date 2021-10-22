/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:23 by twagner           #+#    #+#             */
/*   Updated: 2021/10/22 11:49:37 by twagner          ###   ########.fr       */
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
	if (ac < 2)
		return (1);
	i = 0;
	while (++i < ac)
	{
		if (i == 1 && !ft_strncmp(av[i], "-n", 3))
			nl = '\0';
		else
		{
			printf("%c%s", sep, av[i]);
			sep = ' ';
		}
	}
	printf("%c", nl);
	return (1);
}
