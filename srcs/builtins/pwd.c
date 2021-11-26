/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:33 by twagner           #+#    #+#             */
/*   Updated: 2021/11/26 11:12:46 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(int ac, char **av)
{
	(void)av;
	if (ac > 1)
	{
		printf("usage: pwd\n");
		return (2);
	}
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}
