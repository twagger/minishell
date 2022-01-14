/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:55:10 by twagner           #+#    #+#             */
/*   Updated: 2022/01/14 15:00:39 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** INCREMENT SHLVL
** Increment shlvl variable each time we launch a minishell
*/

int	ms_increment_shlvl(void)
{
	int		ret;
	char	*str_inc_level;
	int		i_level;
	char	*level;

	ret = 0;
	level = ms_getenv("SHLVL");
	if (!level)
		ret = ms_setenv("SHLVL", "2");
	else
	{
		i_level = ft_atoi(level);
		str_inc_level = ft_itoa(++i_level);
		if (!str_inc_level)
			return (ERROR);
		ret = ms_setenv("SHLVL", str_inc_level);
		free(str_inc_level);
	}
	return (ret);
}
