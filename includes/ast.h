/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:19:30 by twagner           #+#    #+#             */
/*   Updated: 2021/11/02 15:17:50 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "minishell.h"

/*
** BINARY TREE (AST) PARAMS
*/
# define LEFT 0
# define RIGHT 1
# define TEMP 2
# define TEMP_AND_RIGHT 3
# define ALL 4

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
	int		current_branch;
	t_node	*buffer;
	t_node	*branch[2];
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

typedef enum e_ast_build
{
	B_PUT_TO_BUFFER = 0,
	B_DO_NOTHING,
	B_SWITCH_BRANCH,
	B_APPLY_RULE,
	B_BUFFER_THEN_RULE = 100
}	t_ast_build;

/*
** BINARY TREE (AST) FUNCTIONS
*/

t_node			*ms_create_node(void *data, int type);
t_ast_builder	*ms_create_ast_builder(void);
void			ms_free_ast_builder(t_ast_builder **builder, int to_free);

#endif