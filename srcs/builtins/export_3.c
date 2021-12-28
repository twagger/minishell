/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:39:32 by ifeelbored        #+#    #+#             */
/*   Updated: 2021/12/28 17:54:04 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
** Count the number of new params to add to the current envp
*/
int	total_params(t_env *envp)
{
	int	total;

	total = 0;
	while (envp)
	{
		total++;
		envp = envp->next;
	}
	return (total);
}

void	ft_envadd(t_env **lst, t_env *new)
{
	t_env	*current;

	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	current = (*lst);
	while (current->next != 0)
	{
		current = current->next;
	}
	current->next = new;
}

t_env	*ft_envnew(char *envp)
{
	t_env		*re;
	char		**sep;

	re = (t_env *)malloc(sizeof(t_env));
	if (!re)
		return (0);
	sep = ft_split(envp, '=');
	if (!sep)
		return (0);
	re->name = sep[0];
	re->content = sep[1];
	re->next = 0;
	return (re);
}

t_env	*init_env(char **envp)
{
	t_env	*new;
	t_env	*list;

	list = NULL;
	while (*envp)
	{
		new = ft_envnew(*envp);
		if (!new)
			return (0);
		ft_envadd(&list, new);
		envp++;
	}
	return (list);
}

int	add_newenvp(char *cmd, t_env **envp)
{
	t_env	*new;

	new = ft_envnew(cmd);
	if (!new)
		return (1);
	ft_envadd(envp, new);
	return (0);
}
