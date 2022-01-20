/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:38:56 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/01/20 16:13:36 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check if the param is like this : name=[value]
** I don't handle yet '+=' operator
** param in the cmds
*/
int	if_str_in_str(char *a, char *b)
{
	int	x1;
	int	x2;

	x1 = 0;
	x2 = 0;
	if (!a || !b)
		return (1);
	while (a[x1] && b[x2])
	{
		if (a[x1] == b[x2])
		{
			while (b[x2] && a[x1 + x2])
			{
				if (b[x2] != a[x1 + x2])
					return (1);
				x2++;
			}
			return (0);
		}
		x1++;
	}
	return (1);
}

static int	ms_is_param_ok_2(char *param)
{
	while (*param)
	{
		if (*param == '=')
			break ;
		if (!ft_isalnum(*param) && *param != '_')
			return (0);
		++param;
	}
	return (1);
}

int	ms_is_param_ok(char	*param)
{
	if ((!ft_isalnum(param[0]) && param[0] != '_') || \
		ft_isdigit(param[0]))
		return (0);
	if (!if_str_in_str(param, "+="))
	{
		while (*param)
		{
			if (*param == '+')
				break ;
			if (!ft_isalnum(*param) && *param != '_')
				return (0);
			++param;
		}
	}
	else
		return (ms_is_param_ok_2(param));
	return (1);
}

/*
** Check if the param already exists in envp
*/

int	ms_is_param_new(char *param, t_env *envp)
{
	size_t	pos_equal;

	if (ft_strchr(param, '+'))
		pos_equal = ft_strchr(param, '+') - param;
	else if (ft_strchr(param, '='))
		pos_equal = ft_strchr(param, '=') - param;
	else
		pos_equal = ft_strlen(param);
	while (envp)
	{
		if (ft_strncmp(param, envp->name, ft_strlen(envp->name)) == 0)
		{	
			if (pos_equal != ft_strlen(envp->name))
				return (1);
			return (0);
		}
		envp = envp->next;
	}
	return (1);
}

t_env	*ft_envnew_1(char *envp, int if_env)
{
	t_env		*re;
	char		*key;
	char		*value;

	re = (t_env *)malloc(sizeof(*re));
	if (!re)
		return (NULL);
	key = ft_substr(envp, 0, ft_strchr(envp, '+') - envp);
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
