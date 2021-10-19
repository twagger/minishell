/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/10/19 16:24:57 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_visit(t_node	*node, char **args, char **envp)
{
	if (!node)
		return (0);
	ms_visit(node->left, args, envp);
	ms_visit(node->right, args, envp);
	if (node->type == TOK_WORD)
	{
		ms_add_one_arg(args, node->data);
	}
	else if (node->type == TOK_NAME)
	{
		if (ms_getbin_path((char **)&node->data) == ERROR)
			return (ERROR);
		if (execve((char *)node->data, args, NULL) == ERROR)
			perror("Minishell");
		ms_empty_arg_array(args);
	}
	return (0);
}

int	ms_execute_ast(t_node *ast, char **envp)
{
	char **args;
	
	(void)envp;
	args = ms_init_arg_array();
	if (ms_visit(ast, args, envp) == ERROR)
		return (1);
	return (0);
}
