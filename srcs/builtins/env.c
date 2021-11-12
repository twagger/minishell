/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:25 by twagner           #+#    #+#             */
/*   Updated: 2021/11/12 16:10:39 by twagner          ###   ########.fr       */
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

// int	ms_env(int ac, char **av, char **envp)
// {
// 	if (ms_env_arg_errors(ac, av) == ERROR)
// 		return (1);
// 	while (*envp)
// 	{
// 		printf("%s\n", *envp);
// 		++envp;
// 	}
// 	return (0);
// }

int	ms_env(int ac, char **av, char **envp)
{
	if (ms_env_arg_errors(ac, av) == ERROR)
		return (1);
	if (!g_my_envp)
		g_my_envp = init_env(envp);
	printf_out_env(g_my_envp);
	return (0);
}
