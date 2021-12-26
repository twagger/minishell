/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/12/26 14:49:39 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "parser.h"

/*
** INTERPRETER
** The interpreter browse the AST in a certain order and push the arguments
** to the right executer (pipeline, command, simple command)
*/

int	ms_search_ast(t_node *node, int needle, int nb, int limiter)
{
	if (!node)
		return (nb);
	if (node->type == needle)
		++nb;
	nb = ms_search_ast(node->left, needle, nb, limiter);
	if (limiter != -1 && node->type == limiter)
		return (nb);
	nb = ms_search_ast(node->right, needle, nb, limiter);
	return (nb);
}

int	ms_execute_ast(t_node *ast, char **envp, int exit_code)
{
	int	nb;
	int	fd[2];

	if (!ast)
		return (EXIT_FAILURE);
	fd[0] = -1;
	nb = ms_search_ast(ast, A_PIPE, 0, A_PIPE);
	if (nb)
		return (ms_exec_pipeline(ast, envp, exit_code, nb));
	else if (ms_search_ast(ast, T_RED_TO, 0, -1) \
			|| ms_search_ast(ast, T_RED_FROM, 0, -1) \
			|| ms_search_ast(ast, T_DLESS, 0, -1) \
			|| ms_search_ast(ast, T_DGREAT, 0, -1))
	{
		ms_save_std_fd((int *)fd);
		ms_do_redirections(ast);
	}
	return (ms_exec_simple_command(ast, envp, exit_code, fd));
}
