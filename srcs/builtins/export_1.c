/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 22:53:17 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/01/20 21:38:08 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strduplen(char *s, size_t len)
{
	size_t	i;
	char	*arr;

	arr = (char *)malloc((len + 1) * sizeof(char));
	if (!arr)
		return (0);
	i = 0;
	while (i < len)
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

int	realloc_var_2(char *cmd, t_env **envp)
{
	char		*content;

	(*envp)->if_env = 1;
	if (ft_strchr(cmd, '+'))
	{
		content = ft_strjoin((*envp)->content, ft_strchr(cmd, '=') + 1);
		if ((*envp)->content)
			free((*envp)->content);
		(*envp)->content = content;
	}
	else
	{
		content = ft_strdup(ft_strchr(cmd, '=') + 1);
		if ((*envp)->content)
			free((*envp)->content);
		(*envp)->content = content;
	}
	return (0);
}

int	realloc_var(char *cmd, t_env *envp)
{
	long	len;
	char	*name;

	len = 0;
	len = ft_strchr(cmd, '+') - cmd;
	if (len < 0)
		len = ft_strchr(cmd, '=') - cmd;
	if (len < 0)
		len = (long)ft_strlen(cmd);
	name = ft_strduplen(cmd, (size_t)len);
	if (!name)
		return (1);
	while (envp)
	{
		if (ft_strncmp(name, envp->name, len + 1) == 0)
			realloc_var_2(cmd, &envp);
		envp = envp->next;
	}
	free(name);
	return (0);
}
