/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:36 by twagner           #+#    #+#             */
/*   Updated: 2021/12/29 15:27:14 by twagner          ###   ########.fr       */
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

int	ms_unset(int ac, char **av)
{
	int	i;

	(void)ac;
	i = 0;
	while (av[++i])
		if_var_exit(av[i]);
	return (0);
}
