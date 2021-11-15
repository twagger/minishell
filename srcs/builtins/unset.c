/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:36 by twagner           #+#    #+#             */
/*   Updated: 2021/11/15 21:06:57 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_my_envp;

void	delete_var(char *name)
{
	t_env	*temp;
	t_env	*prev;

	temp = g_my_envp;
    if (temp != NULL && (ft_strncmp(name, temp->name, ft_strlen(temp->name)) == 0)) 
    {
        (g_my_envp) = temp->next;
        free(temp->content);
		free(temp->name);      
        return ; 
    }
    while (temp != NULL && (ft_strncmp(name, temp->name, ft_strlen(temp->name)) != 0)) 
    {
        prev = temp; 
        temp = temp->next;
    }
    if (temp == NULL) 
       return; 
     prev->next = temp->next;
	 free(temp->content);
	 free(temp->name);
}
void	if_var_exit(char *av)
{
	size_t	len;
	t_env	*head;

	head = g_my_envp;
	while(head)
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
	(void)ac;
	(void)envp;

	int	i;

	i = 0;
	while(av[++i])
		if_var_exit(av[i]);
	//Parcourir envp pour voir si la variable est dans la liste
	//Si pas dans la liste, return
	//Si dans la liste
	//malloc un char ** de la taille de envp - 1 + NULL
	//strdup tous les elements de envp SAUF celui a supprimer
	//free envp si ce n'est pas l'original
	//retourner le nouveau char **
	return (0);
}
