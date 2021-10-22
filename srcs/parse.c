/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:57:26 by twagner           #+#    #+#             */
/*   Updated: 2021/10/22 11:58:02 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Fake parser to allow Tom to work on exec
** Always return the same tree on this command : echo "Test" > toto && touch tata titi tutu
** tThis is quick qnd dirty (memleaks included :))
*/

t_node	*ms_parser(char *line, char **envp)
{
	t_node	*root;

	(void)envp;
	(void)line;
	/*root = ms_create_node((void*)ft_strdup("&&"), TOK_AND_IF);
	root->left = ms_create_node((void*)ft_strdup(">"), TOK_GREAT);
	root->left->left = ms_create_node((void*)ft_strdup("echo"), TOK_NAME);
	root->left->left->left = ms_create_node((void*)ft_strdup("Test"), TOK_WORD);
	root->left->right = ms_create_node((void*)ft_strdup("toto"), TOK_FILE);
	root->right = ms_create_node((void*)ft_strdup("touch"), TOK_NAME);
	root->right->left = ms_create_node((void*)ft_strdup("tutu"), TOK_WORD);
	root->right->left->left = ms_create_node((void*)ft_strdup("titi"), TOK_WORD);
	root->right->left->left->left = ms_create_node((void*)ft_strdup("tata"), TOK_WORD);*/
	root = ms_create_node((void*)ft_strdup("echo"), TOK_NAME);
	root->left = ms_create_node((void*)ft_strdup("tutu"), TOK_WORD);
	root->left->left = ms_create_node((void*)ft_strdup("tata"), TOK_WORD);
	root->left->left->left = ms_create_node((void*)ft_strdup("titi"), TOK_WORD);
	return (root);
}
