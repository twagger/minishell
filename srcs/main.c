/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2021/11/13 16:54:04 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "history.h"

/*
** SHELL LOOP
** for DEBUG add part below after ast = ms_parser
**
** printf("TREE\n----------\n");
** ms_visit_ast(ast, POST_ORDER);
** printf("----------\n");
*/

static int	ms_loop(char **envp)
{
	char	*line;
	t_trans	**parsing_table;
	int		status;
	t_node	*ast;

	status = EXIT_SUCCESS;
	parsing_table = ms_init_parsing_table();
	if (!parsing_table)
		status = ERROR;
	while (status == EXIT_SUCCESS)
	{
		line = ms_readline("\x1B[32mMinishell> \e[0m");
		//line = readline("\x1B[32mMinishell> \e[0m"); -> use this one instead of the other one to get standard behaviour
		if (line)
		{
			ast = ms_parser(ms_tokenizer(line), parsing_table);
			printf("TREE (POST ORDER)\n----------\n");
			ms_visit_ast(ast, POST_ORDER);
			printf("----------\n");
			ms_execute_ast(ast, envp);
		}
		else
			printf("\n");
		free(line);
	}
	ms_free_table(parsing_table);
	return (status);
}

int	main(int ac, char **av, char **envp)
{
	struct termios	orig_termios;
	char 			*term_type;

	g_my_envp = 0;
	(void)ac;
	(void)av;
	term_type = getenv("TERM");
	if (tgetent(NULL, term_type) != 1)
		return (EXIT_FAILURE);
	if (ms_enable_raw_mode(&orig_termios) == ERROR)
		return (EXIT_FAILURE);
	if (ms_loop(envp) == ERROR)
	{
		ms_disable_raw_mode(&orig_termios);
		return (EXIT_FAILURE);
	}
	ms_disable_raw_mode(&orig_termios);
	return (EXIT_SUCCESS);
}
