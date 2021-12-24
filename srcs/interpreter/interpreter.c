/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/12/24 11:08:36 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "parser.h"

/*
** INTERPRETER
** The interpreter browse the AST in a certain order and push the arguments
** to the right executer (pipeline, command, simple command)
*/

int	ms_search_ast(t_node *node, int needle, int nb)
{
	if (!node)
		return (nb);
	if (node->type == needle)
		++nb;
	nb = ms_search_ast(node->left, needle, nb);
	nb = ms_search_ast(node->right, needle, nb);
	return (nb);
}

int	ms_execute_ast(t_node *ast, char **envp, int exit_code)
{
	int	nb;

	if (!ast)
		return (EXIT_FAILURE);
	nb = ms_search_ast(ast, A_PIPE, 0);
	if (nb)
		return (ms_exec_pipeline(ast, envp, exit_code, nb));
	else if (ms_search_ast(ast, T_RED_TO, 0) \
			|| ms_search_ast(ast, T_RED_FROM, 0) \
			|| ms_search_ast(ast, T_DLESS, 0) \
			|| ms_search_ast(ast, T_DGREAT, 0))
		ms_do_redirections(ast, envp, exit_code);
	return (ms_exec_simple_command(ast, envp, exit_code));
}
