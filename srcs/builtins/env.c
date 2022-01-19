/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:25 by twagner           #+#    #+#             */
/*   Updated: 2022/01/19 22:44:13 by ifeelbored       ###   ########.fr       */
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
		if (temp->if_env == 1)
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
