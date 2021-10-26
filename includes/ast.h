/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:19:30 by twagner           #+#    #+#             */
/*   Updated: 2021/10/26 15:19:36 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "minishell.h"

/*
** BINARY TREE (AST) STRUCTURE
*/
typedef enum e_ast_node_types
{
	TOK_WORD,
	TOK_NAME,
	TOK_FILE,
	TOK_LESS,
	TOK_GREAT,
	TOK_DLESS,
	TOK_DGREAT,
	TOK_PIPE,
	TOK_AND_IF,
	TOK_OR_IF,
	TOK_ASSIGNMENT_WORD,
	TOK_NEWLINE,
	TOK_IO_NUMBER
}	t_ast_node_types;

typedef struct s_node
{
	int				type;
	void			*data;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

/*
** BINARY TREE (AST) FUNCTIONS
*/
t_node	*ms_create_node(void *data, int type);
int		ms_execute_ast(t_node *ast, char **envp);

#endif