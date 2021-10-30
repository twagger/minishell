/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2021/10/30 14:35:25 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "token.h"
#include "lr_parser.h"

static int	ms_loop(char **envp)
{
	char	*line;
	t_token	*tok_list;
	t_trans	**table;
	int		status;

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
			status = ms_parser(tok_list, table);
		}
		else
			printf("\n");
		free(line);
	}
	ms_free_tokens(tok_list);
	ms_free_table(table);
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
