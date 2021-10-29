/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2021/10/29 11:14:05 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "token.h"
#include "lr_parser.h"

/*static int	ms_loop(char **envp)
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
}*/
void	printf_out(t_token *all)
{
	while (all->next)
	{
		printf("int :%d\n", all->type);
		printf("value:|%s|\n", (char *)all->value);
		all = all->next;
}
	printf("int :%d\n", all->type);
	printf("value:|%s|\n", (char *)all->value);
}

static int	ms_loop(char **envp)
{
	char	*line;
	t_token	*tok_list;
	t_trans	**trans;
	int		status;

	(void)envp;
	trans = ms_init_state_machine();
	if (!trans)
		return (ERROR);
	status = EXIT_SUCCESS;
	while (status == EXIT_SUCCESS)
	{
		line = readline("\x1B[32mMinishell> \e[0m");
		if (line)
		{
			tok_list = ms_tokenizer(line);
			if (!tok_list)
			{
				free(line);
				return (ERROR);
			}
			printf_out(tok_list);
			ms_parser(tok_list, trans);
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
