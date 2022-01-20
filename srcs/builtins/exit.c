/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:28 by twagner           #+#    #+#             */
/*   Updated: 2022/01/20 20:52:55 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#define NO_ARG -2
#define NO_NUM_ARG -3

static int	ms_is_operand_numeric(char *str)
{
	int			sign;
	long long	result;
	int			ret;

	ret = 1;
	sign = 1;
	result = 0;
	if (ft_strlen(str) > 20)
		return (0);
	if (*str == '+' || *str == '-')
	{
		sign = sign + (43 - *str);
		++str;
	}
	while (ft_isdigit(*str))
	{
		result = (result * 10) + (*str - 48);
		++str;
	}
	if (sign == 1 && result < 0)
		ret = 0;
	else if (sign == -1 && (result * -1) > 0)
		ret = 0;
	return (ret);
}

static int	ms_is_operand_ok(char *op)
{
	int	i;
	int	res;

	res = 0;
	if (!ms_is_operand_numeric(op))
		return (0);
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
	int	num_args;

	num_args = 0;
	if (ac == 1)
		return (NO_ARG);
	if (ac >= 2)
	{
		if (!ms_is_operand_ok(av[1]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			num_args = -3;
		}
	}
	if (ac > 2 && !num_args)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (ERROR);
	}
	return (num_args);
}

int	ms_exit(int ac, char **av)
{
	int	code;
	int	ret;

	ret = ms_exit_arg_errors(ac, av);
	if (ret == ERROR)
		return (1);
	if (ret == NO_NUM_ARG)
		return (-257);
	if (ret != NO_ARG)
		code = ft_atoi(av[1]);
	if (ac == 2)
	{
		if (code < 0)
			code = 256 + (code % 256);
		return (ST_EXIT + (code * -1));
	}
	return (ST_EXIT);
}
