/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 10:01:48 by twagner           #+#    #+#             */
/*   Updated: 2021/12/29 16:04:28 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ms_envnew(char *name, char *value)
{
	t_env		*new;

	new = (t_env *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->name = ft_strdup(name);
	new->content = ft_strdup(value);
	if (!new->content || !new->name)
		return (NULL);
	return (new);
}

int	ms_setenv(char *name, char *value)
{
	t_env	*temp;
	t_env	*new;

	temp = g_envp;
	while (temp)
	{
		if (!ft_strcmp(name, temp->name))
		{
			if (ft_strcmp(value, temp->content))
			{
				free(temp->content);
				temp->content = ft_strdup(value);
				if (!temp->content)
					return (ERROR);
			}
			return (0);
		}
		temp = temp->next;
	}
	new = ms_envnew(name, value);
	if (!new)
		return (ERROR);
	ft_envadd(&g_envp, new);
	return (0);
}

char	*ms_getenv(char *var)
{
	t_env	*temp;

	temp = g_envp;
	while (temp)
	{
		if (!ft_strcmp(var, temp->name))
			return (temp->content);
		temp = temp->next;
	}
	return (NULL);
}

void	ms_clearenv(void)
{
	t_env	*next;

	while (g_envp)
	{
		next = g_envp->next;
		free(g_envp->name);
		free(g_envp->content);
		free(g_envp);
		g_envp = next;
	}
}
