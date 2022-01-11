/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:57:26 by twagner           #+#    #+#             */
/*   Updated: 2022/01/10 22:58:34 by ifeelbored       ###   ########.fr       */
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

	//printf("replace2:|%s|,|%s|,|%d|\n", new, newvar, (*i_new));
	i = (*i_new);
	while (newvar && *newvar)
	{
		new[i] = *newvar;
		newvar++;
		i++;
	}
	new[i] = '\0';
	//printf("newcmd:%s\n",new);
}

int	replace_var(char *arr, char *new, int *i_new)
{
	int		len;
	char	*var;
	char	*newvar;
	int		i;

	//如果沒有這個var在env?
	len = env_len(arr);
	// printf("cmd:%s, %d, %d\n",c, len, index);
	if (!len)
		return (0);
	var = malloc((len + 1) * sizeof(char));
	if (!var)
		return (0);
	i = -1;
	while (++i < len)
		var[i] = arr[i];
	var[i] = '\0';
	//printf("var:%s\n",var);
	newvar = ms_getenv(var);
	//printf("newvar:|%s|\n", newvar);
	if (newvar)
		replcace_var_2(new, newvar, i_new);
	//printf("cmddd:%s\n",cmd);
	if (var)
		free(var);
	return (len);
}
