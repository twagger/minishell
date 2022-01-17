/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:57:26 by twagner           #+#    #+#             */
/*   Updated: 2022/01/17 17:59:52 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	env_len(char *c)
{
	int	len;

	len = 0;
	if (!*c)
		return (0);
	while (c[len])
	{
		if (ft_isalnum(c[len]) || c[len] == '_')
			len++;
		else
			break ;
	}
	if (len == 0)
		return (-1);
	return (len);
}

int	replcace_var_2(char *new, char *newvar, int *i_new, int len)
{
	int		i;

	i = (*i_new);
	while (newvar && *newvar)
	{
		new[i] = *newvar;
		newvar++;
		i++;
	}
	new[i] = '\0';
	return (len);
}

int	replace_var(t_cd cd, char *new, int *i_new)
{
	int		len;
	char	*var;
	char	*newvar;
	int		i;

	if (*(cd.ar) == '?')
		return (replcace_var_2(new, cd.code, i_new, 1));
	len = env_len(cd.ar);
	var = malloc((len + 1) * sizeof(char));
	if (!var || !len)
		return (0);
	if (len < 0)
		return (replcace_var_2(new, "$", i_new, 0));
	i = -1;
	while (++i < len)
		var[i] = cd.ar[i];
	var[i] = '\0';
	newvar = ms_getenv(var);
	if (var)
		free(var);
	if (newvar)
		replcace_var_2(new, newvar, i_new, len);
	return (len);
}
