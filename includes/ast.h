/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:19:30 by twagner           #+#    #+#             */
/*   Updated: 2021/11/07 11:51:12 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "minishell.h"

/*
** BINARY TREE (AST) PARAMS
*/
# define AST 0
# define BUFFER 1
# define ALL 2
# define NO_REDUC -1
# define KEEP 0
# define POP 1
# define PRE_ORDER 0
# define IN_ORDER 1
# define POST_ORDER 2

/*
** BINARY TREE (AST) STRUCTURE
*/

typedef struct s_node
{
	int				type;
	int				reduc;
	void			*data;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_ast_builder
{
	t_node	**buffer;
	t_node	*ast;
}			t_ast_builder;

typedef enum e_ast_types
{
	A_CMD = 0,
	A_OPE,
	A_FILE,
	A_HERE,
	A_AND_IF = 4,
	A_OR_IF,
	A_DLESS,
	A_DGREAT,
	A_PIPE,
	A_RED_TO,
	A_RED_FROM
}	t_ast_types;

/*
** BINARY TREE (AST) FUNCTIONS
*/
t_node			*ms_create_node(void *data, int type, int reduc);
void			ms_free_tree(t_node	*node);
void			ms_visit_ast(t_node *node, int mode);

t_ast_builder	*ms_create_ast_builder(void);
int				ms_buffer_add_back(t_ast_builder **builder, t_node *new);
t_node			*ms_buffer_remove(t_ast_builder **builder, int to_remove);
void			ms_free_ast_builder(t_ast_builder **builder, int to_free);

#endif