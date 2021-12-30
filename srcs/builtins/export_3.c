/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:39:32 by ifeelbored        #+#    #+#             */
/*   Updated: 2021/12/30 11:30:03 by twagner          ###   ########.fr       */
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

t_env	*ft_envnew(char *envp)
{
	t_env		*re;
	char		**sep;

	re = (t_env *)malloc(sizeof(*re));
	if (!re)
		return (NULL);
	sep = ft_split(envp, '=');
	if (!sep)
		return (NULL);
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
			return (NULL);
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
