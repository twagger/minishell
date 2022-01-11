/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2022/01/10 16:06:59 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "history.h"

t_env	*g_envp = NULL;

/*
** SHELL LOOP
** for DEBUG add part below after ast = ms_parser
*/

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
