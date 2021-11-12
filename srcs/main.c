/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2021/11/12 14:40:07 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
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

static int	ms_loop(char **envp)
{
	char	*line;
	t_token	*tok_list;
	t_trans	**table;
	int		status;
	t_node	*ast;

	(void)envp;
	tok_list = NULL;
	status = EXIT_SUCCESS;
	table = ms_init_parsing_table();
	if (!table)
		status = ERROR;
	while (status == EXIT_SUCCESS)
	{
		line = readline("\x1B[32mMinishell> \e[0m");
		if (line)
		{
			tok_list = ms_tokenizer(line);
			if (!tok_list)
				status = ERROR;
			printf_out(tok_list);
			printf("PARSER\n----------\n");
			ast = ms_parser(tok_list, table);
			if (!ast)// || (ast && ms_execute_ast(ast, envp) == ERROR))
				status = ERROR;
			printf("----------\n");
			printf("TREE\n----------\n");
			ms_visit_ast(ast, POST_ORDER);
			ms_execute_ast(ast, NULL);
			printf("----------\n");
		}
		else
			printf("\n");
		free(line);
	}
	ms_free_tokens(tok_list);
	ms_free_table(table);
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
	(void)ac;
	(void)av;
	g_my_envp = 0;
	if (ms_loop(envp) == ERROR)
		return (EXIT_FAILURE);
	// test_env(envp);
	return (EXIT_SUCCESS);
}
