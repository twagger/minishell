/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2021/12/27 12:34:38 by twagner          ###   ########.fr       */
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

static void	ms_display_special_status(int status)
{
	if (status == 131)
		printf("Quit : %i\n", status - 128);
	else if (status > 128)
		printf("\n");
}

static int	ms_loop(char **envp, struct termios *termios)
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
		if (ms_enable_raw_mode(termios) == ERROR)
			return (ERROR);
		line = ms_readline(&histo);
		ms_disable_raw_mode(termios);
		if (line)
		{
			ast = ms_parser(ms_tokenizer(line), parsing_table);
			if (!ast)
				printf("minishell: syntax error\n");
			status = ms_execute_ast(ast, envp, status);
			ms_display_special_status(status);
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
	if (ms_loop(envp, &orig_termios) == ERROR)
	{
		ms_disable_raw_mode(&orig_termios);
		return (EXIT_FAILURE);
	}
	ms_disable_raw_mode(&orig_termios);
	return (EXIT_SUCCESS);
}
