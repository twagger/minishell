/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:28 by twagner           #+#    #+#             */
/*   Updated: 2021/11/13 10:12:37 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define NO_ARG -2

static int	ms_is_operand_ok(char *op)
{
	int	i;
	int	res;

	res = 0;
	if (op[0] == '-' || op[0] == '+')
		i = 0;
	else
		i = -1;
	while (op[++i])
	{
		if (ft_isdigit(op[i]))
			res = 1;
		else
		{
			res = 0;
			break ;
		}
	}
	return (res);
}

static int	ms_exit_arg_errors(int ac, char **av)
{
	if (ac == 1)
		return (NO_ARG);
	if (ac == 2)
	{
		if (ms_is_operand_ok(av[1]))
			return (0);
		ft_putstr_fd("exit: bad operand\n", 2);
		return (ERROR);
	}
	if (ac > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (ERROR);
	}
	return (0);
}

int	ms_exit(int ac, char **av)
{
	int	code;
	int ret;

	ret = ms_exit_arg_errors(ac, av);
	if (ret == ERROR)
		return (1);
	if (ret != NO_ARG)
		code = ft_atoi(av[1]);
	if (ac == 2)
	{
		if (code >= 0 && code <= 255)
			exit(code);
		else
			exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
