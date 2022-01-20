/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:31 by twagner           #+#    #+#             */
/*   Updated: 2022/01/20 21:49:34 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_list(t_env *ev)
{
	while (ev)
	{
		if (ev->if_env == 1)
			printf("declare -x %s=\"%s\"\n", ev->name, ev->content);
		else
			printf("declare -x %s\n", ev->name);
		ev = ev->next;
	}
}

int	add_newenvp_local(char *av, t_env **envp)
{
	t_env		*re;
	char		*key;

	re = (t_env *)malloc(sizeof(*re));
	if (!re)
		return (1);
	key = ft_strdup(av);
	if (!key)
	{
		free(key);
		free(re);
		return (1);
	}
	re->name = key;
	re->next = 0;
	re->content = 0;
	re->if_env = 0;
	ft_envadd(envp, re);
	return (0);
}

static void	ms_export_2(char **av, int i)
{
	if (ms_is_param_new(av[i], g_envp))
	{
		if (!ft_strchr(av[i], '='))
		{
			add_newenvp_local(av[i], &g_envp);
			return ;
		}
		else if (add_newenvp(av[i], &g_envp))
		{
			printf("minishell: export: error happened while exporting\n");
			return ;
		}
	}
	else if (!ft_strchr(av[i], '='))
		return ;
	else if (realloc_var(av[i], g_envp))
	{
		printf("minishell: export: error happened while realloc\n");
		return ;
	}
}

int	ms_export(int ac, char **av)
{
	int		i;
	int		re_va;

	(void)ac;
	i = 0;
	re_va = 0;
	while (av[++i])
	{
		if (!ms_is_param_ok(av[i]))
		{
			re_va = 1;
			printf("minishell: export: not a valid identifier\n");
			continue ;
		}
		ms_export_2(av, i);
	}
	if (!av[1])
		printf_list(g_envp);
	return (re_va);
}
