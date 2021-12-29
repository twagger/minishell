/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:25 by twagner           #+#    #+#             */
/*   Updated: 2021/12/29 15:24:13 by twagner          ###   ########.fr       */
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

void	printf_out_env(void)
{
	t_env	*temp;

	temp = g_envp;
	while (temp)
	{
		printf("%s=%s\n", temp->name, temp->content);
		temp = temp->next;
	}
}

int	ms_env(int ac, char **av)
{
	if (ms_env_arg_errors(ac, av) == ERROR)
		return (1);
	printf_out_env();
	return (0);
}
