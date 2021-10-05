/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:05:59 by twagner           #+#    #+#             */
/*   Updated: 2021/10/05 14:18:26 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cleaner(char *line, char **args, int exit_code)
{
	int	i;
	free(line);
	if (args)
	{
		i = -1;
		while (args[++i])
			free(args[i]);
	}
	return (exit_code);
}
