/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:25 by twagner           #+#    #+#             */
/*   Updated: 2021/12/28 17:57:13 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_my_envp;

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

void	printf_out_env(t_env *list)
{
	t_env	*temp;

	temp = list;
	while (temp)
	{
		printf("%s=%s\n", temp->name, temp->content);
		temp = temp->next;
	}
}

int	ms_env(int ac, char **av, char **envp)
{
	if (ms_env_arg_errors(ac, av) == ERROR)
		return (1);
	if (!g_my_envp)
		g_my_envp = init_env(envp);
	printf_out_env(g_my_envp);
	return (0);
}
