/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/10/19 13:11:33 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_visit(t_node	*node, char **args, char **envp)
{
	if (!node)
		return ;
	ms_visit(node->left, args, envp);
	// in-order ok pour &&  | post-order pour le reste 
	ms_visit(node->right, args, envp);
	if (node->type == TOK_WORD)
	{
		printf("WORD : %s\n", node->data);
		// add the word to an arg list that will be given to execve as second parameter
	}
	else if (node->type == TOK_NAME)
	{
		printf("NAME : %s\n", node->data);
		// check if the name is a builtin > if it is, execute the builtin
		// if it is not a builtin > launch execve with the node data as first parameter and arglist as second parameter
		// clean the args
	}
	else if (node->type == TOK_FILE)
	{
		printf("FILE : %s\n", node->data);
	}
	else if (node->type == TOK_GREAT)
	{
		printf("GREAT : %s\n", node->data);
	}
	else if (node->type == TOK_AND_IF)
	{
		printf("AND_IF : %s\n", node->data);
	}
}

int	ms_execute_ast(t_node *ast, char **envp)
{
	char **args;
	
	args = NULL;
	// inialize an arglist
	(void)envp;
	ms_visit(ast, args, envp);
	return (1);
}
