/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:39:32 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/01/19 23:00:44 by wlo              ###   ########.fr       */
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
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

t_env	*ft_envnew(char *envp, int if_env)
{
	t_env		*re;
	char		*key;
	char		*value;

	re = (t_env *)malloc(sizeof(*re));
	if (!re)
		return (NULL);
	key = ft_substr(envp, 0, ft_strchr(envp, '=') - envp);
	value = ft_substr(envp, ft_strchr(envp, '=') - envp + 1, \
		ft_strlen(envp) - ft_strlen(key) - 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		free(re);
		return (NULL);
	}
	re->name = key;
	re->content = value;
	re->next = 0;
	re->if_env = if_env;
	return (re);
}

t_env	*init_env(char **envp)
{
	t_env	*new;
	t_env	*list;

	list = NULL;
	while (*envp)
	{
		new = ft_envnew(*envp, 1);
		if (!new)
			return (NULL);
		ft_envadd(&list, new);
		envp++;
	}
	return (list);
}

int	add_newenvp(char *cmd, t_env **envp)
{
	t_env	*new;

	if (!(ft_strchr(cmd, '+')))
		new = ft_envnew(cmd, 1);
	else
		new = ft_envnew_1(cmd, 1);
	if (!new)
		return (1);
	ft_envadd(envp, new);
	return (0);
}
