/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2022/01/08 14:58:41 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "history.h"

/*
** TMP
*/

void	ms_visit_ast(t_node *node)
{
	if (!node)
		return ;
	ms_visit_ast(node->left);
	ms_visit_ast(node->right);
	if (node->reduc == R_SIMPLE_COMMAND)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_SIMPLE_COMMAND");
	if (node->reduc == R_CMD_NAME)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_CMD_NAME");
	if (node->reduc == R_CMD_WORD)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_CMD_WORD");
	if (node->reduc == R_CMD_PREFIX)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_CMD_PREFIX");
	if (node->reduc == R_CMD_SUFFIX)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_CMD_SUFFIX");
	if (node->reduc == R_IO_REDIRECT)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_IO_REDIRECT");
	if (node->reduc == R_IO_FILE)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_IO_FILE");
	if (node->reduc == R_FILENAME)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_FILENAME");
	if (node->reduc == R_IO_HERE)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_IO_HERE");
	if (node->reduc == R_HERE_END)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_HERE_END");
	if (node->type != -1 && node->type != -2)
		printf("TYPE : %i\tDATA : %s\n", node->type, (char *)node->data);
	if (node->reduc == R_PIPE_SEQUENCE && node->type == ROOT)
		printf("TYPE : %i\tDATA : %s\n", node->type, "LAST SIMPLE COMMAND");
	else if (node->reduc == R_PIPE_SEQUENCE)
		printf("TYPE : %i\tDATA : %s\n", node->type, "SIMPLE COMMAND");
}

/*
** SHELL LOOP
** for DEBUG add part below after ast = ms_parser
**
** printf("TREE\n----------\n");
** ms_visit_ast(ast, POST_ORDER);
** printf("----------\n");
*/
t_env	*g_envp = NULL;

static int	ms_increment_shlvl(void)
{
	int		ret;
	char	*str_inc_level;
	int		i_level;
	char	*level;

	ret = 0;
	level = ms_getenv("SHLVL");
	if (!level)
		ret = ms_setenv("SHLVL", "2");
	else
	{
		i_level = ft_atoi(level);
		str_inc_level = ft_itoa(++i_level);
		if (!str_inc_level)
			return (ERROR);
		ret = ms_setenv("SHLVL", str_inc_level);
		free(str_inc_level);
	}
	return (ret);
}

static void	ms_display_special_status(int status)
{
	if (status == 131)
		printf("Quit : %i\n", status - 128);
	else if (status > 128)
		printf("\n");
}

static int	ms_loop(struct termios *termios)
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
			status = ms_execute_ast(ast, status);
			ms_clear_tree(&ast);
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
	int				exit_code;

	(void)ac;
	(void)av;
	g_envp = init_env(envp);
	if (g_envp == NULL || ms_increment_shlvl() == ERROR)
		return (EXIT_FAILURE);
	term_type = ms_getenv("TERM");
	if (tgetent(NULL, term_type) != 1)
	{
		ms_clearenv();
		return (EXIT_FAILURE);
	}
	exit_code = ms_loop(&orig_termios);
	ms_disable_raw_mode(&orig_termios);
	ms_clearenv();
	if (exit_code == ERROR)
		return (EXIT_FAILURE);
	return ((exit_code * -1) - 2);
}
