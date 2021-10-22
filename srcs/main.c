/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2021/10/22 12:01:09 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_loop(char **envp)
{
	char	*line;
	t_node	*ast;
	int		status;

	status = EXIT_SUCCESS;
	while (status == EXIT_SUCCESS)
	{
		line = readline("\x1B[32mMinishell> \e[0m");
		if (line)
		{
			ast = ms_parser(line, envp);
			if (!ast)
			{
				free(line);
				return (ERROR);
			}
			status = ms_execute_ast(ast, envp);
		}
		else
			printf("\n");
		free(line);
	}
	return (status);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	if (ms_loop(envp) == ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
