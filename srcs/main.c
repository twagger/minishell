/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2021/11/13 10:48:08 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	printf_out(t_token *all)
{
	printf("----------\nLEXER\n----------\n");
	while (all)
	{
		printf("int : %d - value : %s\n", all->type, (char *)all->value);
		all = all->next;
	}
	printf("----------\n"); 
}

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
		line = readline("\x1B[32mMinishell> \e[0m");
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

/* void	test_env(char **envp)
{
	int		status;
	char	*line;
	char	**cmds;

	status = EXIT_SUCCESS;
	while (status == EXIT_SUCCESS)
	{
		line = readline("\x1B[32mMinishell> \e[0m");
		if (line)
		{
			cmds = ft_split(line, ' ');
			if (ms_is_builtin(cmds[0]))
				ms_execute_builtin(cmds, envp);
			else
				ms_execute(cmds, envp);
		}
		else
			printf("\n");
		free(line);
	}
} */

int	main(int ac, char **av, char **envp)
{
	char	*term_type;

	g_my_envp = 0;
	(void)ac;
	(void)av;
	term_type = getenv("TERM");
	if (tgetent(NULL, term_type) != 1) ;
	if (ms_loop(envp) == ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
