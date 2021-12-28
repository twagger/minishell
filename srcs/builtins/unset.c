/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:36 by twagner           #+#    #+#             */
/*   Updated: 2021/12/28 15:36:47 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_my_envp;

void	delete_var(char *name)
{
	t_env	*tm;
	t_env	*prev;

	tm = g_my_envp;
	if (tm != NULL && (ft_strncmp(name, tm->name, ft_strlen(tm->name)) == 0))
	{
		(g_my_envp) = tm->next;
		free(tm->content);
		free(tm->name);
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
}

void	if_var_exit(char *av)
{
	size_t	len;
	t_env	*head;

	head = g_my_envp;
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

int	ms_unset(int ac, char **av, char **envp)
{
	int	i;

	(void)ac;
	(void)envp;
	i = 0;
	while (av[++i])
		if_var_exit(av[i]);
	return (0);
}
