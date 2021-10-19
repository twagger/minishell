/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2021/10/19 12:50:35 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	ms_is_builtin(char *command)
{
	if (ft_strncmp(command, "cd", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "env", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "echo", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "pwd", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "exit", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "export", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		return (1);
	return (0);
}*/

int	ms_loop(char **envp)
{
	char	*line;
	t_node	*ast;
	int		status;

	status = 0;
	while (!status)
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
		return (1);
	return (0);
}
