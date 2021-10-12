/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:23 by twagner           #+#    #+#             */
/*   Updated: 2021/10/12 16:51:14 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	int		i;
	char	nl;

	nl = '\n';
	if (ac < 2)
		return (0);
	i = 0;
	while (++i < ac)
	{
		if (i == 1 && !ft_strncmp(av[i], "-n", 3))
			nl = '\0';
		else
			printf("%s%c", av[i], nl);
	}
	return (0);
}
