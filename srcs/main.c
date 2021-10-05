/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2021/10/05 12:25:59 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_loop(void)
{
	int	status;

	status = 1;
	while (status)
	{
		printf("\e[1;34mMinishell > ");
		// get line
		// parsing
		// executing
	}
}

int	main(void)
{
	ms_loop();
	return (0);
}
