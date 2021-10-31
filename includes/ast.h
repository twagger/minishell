/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:19:30 by twagner           #+#    #+#             */
/*   Updated: 2021/10/31 10:24:16 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "minishell.h"

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

t_node	*ms_create_node(void *data, int type);

#endif