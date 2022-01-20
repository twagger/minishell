/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:36 by twagner           #+#    #+#             */
/*   Updated: 2022/01/20 21:51:53 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_var(char *name)
{
	t_env	*tm;
	t_env	*prev;

	tm = g_envp;
	if (tm != NULL && (ft_strncmp(name, tm->name, ft_strlen(tm->name)) == 0))
	{
		(g_envp) = tm->next;
		free(tm->content);
		free(tm->name);
		free(tm);
		return ;
	}
	while (tm != NULL && (ft_strncmp(name, tm->name, ft_strlen(tm->name)) != 0))
	{
		prev = tm;
		tm = tm->next;
	}
	if (tm == NULL)
		return ;
	prev->next = tm->next;
	free(tm->content);
	free(tm->name);
	free(tm);
}

void	if_var_exit(char *av)
{
	size_t	len;
	t_env	*head;

	head = g_envp;
	while (head)
	{
		len = ft_strlen(head->name);
		if (ft_strncmp(av, head->name, len + 1) == 0)
		{
			delete_var(av);
			return ;
		}
		head = head->next;
	}
}

int	is_param_ok(char	*param)
{
	if ((!ft_isalnum(param[0]) && param[0] != '_') || \
		ft_isdigit(param[0]))
		return (0);
	while (*param)
	{
		if (!ft_isalnum(*param) && *param != '_')
			return (0);
		++param;
	}
	return (1);
}

int	ms_unset(int ac, char **av)
{
	int	i;
	int	re_va;

	(void)ac;
	i = 0;
	re_va = 0;
	while (av[++i])
	{
		if (!av[i][0] || !is_param_ok(av[i]))
		{
			re_va = 1;
			printf("minishell: unset: not a valid identifier\n");
			continue ;
		}
		if_var_exit(av[i]);
	}
	return (re_va);
}
