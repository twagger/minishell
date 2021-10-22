/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/10/22 12:00:41 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ms_visit(t_node *node, char **args, char **envp)
{
	if (!node)
		return (args);
	args = ms_visit(node->left, args, envp);
	args = ms_visit(node->right, args, envp);
	if (node->type == TOK_WORD)
		args = ms_add_one_arg(args, node->data);
	else if (node->type == TOK_NAME)
	{
		args = ms_add_command(args, node->data);
		if (!args)
			return (NULL);
		ms_execute(args, envp);
		ms_free_arg_array(args);
		args = ms_init_arg_array();
	}
	return (args);
}

int	ms_execute_ast(t_node *ast, char **envp)
{
	char	**args;

	args = ms_init_arg_array();
	if (!ms_visit(ast, args, envp))
	{
		ms_free_arg_array(args);
		return (EXIT_FAILURE);
	}
	ms_free_arg_array(args);
	return (EXIT_SUCCESS);
}
