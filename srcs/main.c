/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2021/11/16 15:37:37 by twagner          ###   ########.fr       */
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
t_env	*g_my_envp;

static int	ms_loop(char **envp)
{
	char		*line;
	int			status;
	t_node		*ast;
	t_history	*histo;
	t_trans		**parsing_table;

	histo = NULL;
	status = 0;
	parsing_table = ms_init_parsing_table();
	if (!parsing_table)
		status = ERROR;
	while (status >= 0)
	{
		line = ms_readline(&histo);
		if (line)
		{
			ast = ms_parser(ms_tokenizer(line), parsing_table);
			printf("TREE\n----------\n");
			ms_visit_ast(ast, POST_ORDER);
			printf("----------\n");
			status = ms_execute_ast(ast, envp);
		}
		else
			printf("\n");
	}
	ms_histo_clear(histo);
	ms_free_table(parsing_table);
	return (status);
}

int	main(int ac, char **av, char **envp)
{
	struct termios	orig_termios;
	char			*term_type;

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
