/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2021/10/12 12:39:33 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		line = readline("\x1B[32mMinishell> \e[0m");
		if (line)
		{
			args = ms_parser(line);
			if (!args)
				return (ft_cleaner(line, NULL, ERROR));
			status = ms_execute(args);
		}
		else
			printf("\n");
		ft_cleaner(line, args, 0);
	}
	return (0);
}

int	main(void)
{
	if (ms_loop() == ERROR)
		return (1);
	return (0);
}
