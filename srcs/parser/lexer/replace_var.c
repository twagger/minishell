/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:57:26 by twagner           #+#    #+#             */
/*   Updated: 2022/01/13 17:58:22 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(char *c)
{
	int	len;

	len = 0;
	while (c[len])
	{
		if (ft_isalnum(c[len]) || c[len] == '_')
			len++;
		else
			return (len);
	}
	return (len);
}

void	replcace_var_2(char *new, char *newvar, int *i_new)
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
}

int	replace_var(char *arr, char *new, int *i_new)
{
	int		len;
	char	*var;
	char	*newvar;
	int		i;

	if (*arr == '?')
	{
		replcace_var_2(new, "$?U^W7SuvelH7EbjFA6*Ku", i_new);
		return (2);
	}
	len = env_len(arr);
	var = malloc((len + 1) * sizeof(char));
	if (!var || !len)
		return (0);
	i = -1;
	while (++i < len)
		var[i] = arr[i];
	var[i] = '\0';
	newvar = ms_getenv(var);
	if (newvar)
		replcace_var_2(new, newvar, i_new);
	if (var)
		free(var);
	return (len);
}
