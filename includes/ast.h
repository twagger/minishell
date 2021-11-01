/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:19:30 by twagner           #+#    #+#             */
/*   Updated: 2021/11/01 20:59:27 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "minishell.h"

/*
** BINARY TREE (AST) PARAMS
*/
# define ALL 0
# define LEFT 1
# define RIGHT 2
# define TEMP 3
# define TEMP_AND_RIGHT 4

/*
** BINARY TREE (AST) STRUCTURE
*/

typedef struct s_node
{
	int				type;
	void			*data;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_ast_builder
{
	t_node	**temp;
	t_node	*left;
	t_node	*right;	
}			t_ast_builder;

typedef enum e_ast_types
{
	AST_OPE = 0,
	AST_CMD,
	AST_PIPE,
	AST_AND_IF,
	AST_OR_IF,
	AST_DLESS,
	AST_DGREAT,
	AST_RED_TO,
	AST_RED_FROM
}	t_ast_types;

/*
** BINARY TREE (AST) FUNCTIONS
*/

t_node			*ms_create_node(void *data, int type);
t_ast_builder	*ms_create_ast_builder(void);
void			ms_free_ast_builder(t_ast_builder **builder, int to_free);

#endif