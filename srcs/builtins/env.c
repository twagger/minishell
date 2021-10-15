/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:25 by twagner           #+#    #+#             */
/*   Updated: 2021/10/15 12:28:42 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_env_arg_errors(int ac, char **av)
{
	if (ac > 1)
	{
		if (av[1][0] == '-')
		{
			ft_putstr_fd("usage: env\n", 2);
			return (ERROR);
		}
		perror("env");
		return (ERROR);
	}
	return (0);
}

int	ms_env(int ac, char **av)
{
	if (ms_env_arg_errors(ac, av) == ERROR)
		return (1);
	
	return (1);
}