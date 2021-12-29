/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:31 by twagner           #+#    #+#             */
/*   Updated: 2021/12/29 15:25:20 by twagner          ###   ########.fr       */
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

	if (ft_strchr(cmd, '+'))
	{
		content = ft_strjoin((*envp)->content, ft_strchr(cmd, '=') + 1);
		if (!content)
			return (1);
		free((*envp)->content);
		(*envp)->content = content;
	}
	else
	{
		content = ft_strdup(ft_strchr(cmd, '='));
		if (!content)
			return (1);
		free((*envp)->content);
		(*envp)->content = content;
	}
	return (0);
}

int	realloc_var(char *cmd, t_env *envp)
{
	size_t	len;
	char	*name;

	len = 0;
	len = ft_strchr(cmd, '+') - cmd;
	if (!len)
		len = ft_strchr(cmd, '=') - cmd;
	name = ft_strduplen(cmd, len);
	if (!name)
		return (1);
	while (envp)
	{
		if (ft_strncmp(name, envp->name, len + 1) == 0)
			realloc_var_2(cmd, &envp);
		envp = envp->next;
	}
	return (0);
}

static void	ms_export_2(char **av, int i)
{
	while (av[++i])
	{
		if (!ms_is_param_ok(av[i]))
		{
			printf("Not a valid identifier\n");
			continue ;
		}
		if (ms_is_param_new(av[i], g_envp))
		{
			if (add_newenvp(av[i], &g_envp))
			{
				printf("Error happened while exporting var\n");
				continue ;
			}
		}
		else
		{
			if (realloc_var(av[i], g_envp))
			{
				printf("Error happened while realloc var\n");
				continue ;
			}
		}
	}
}

int	ms_export(int ac, char **av)
{
	int		i;

	(void)ac;
	i = 0;
	ms_export_2(av, i);
	return (0);
}
