/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:18:13 by twagner           #+#    #+#             */
/*   Updated: 2021/11/11 16:11:43 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"
# include "token.h"

/*
** PARSER PARAMS
*/
# define NB_TRANS 156
# define AUTOMATON "./srcs/parser/parser/parsing_table"
# define NO_ACTION -1
# define DEFAULT -1
# define SHIFT 0
# define REDUCE 1
# define ACCEPT 2

typedef enum e_rules
{
	R_AND_OR = 100,
	R_PIPE_SEQUENCE,
	R_SIMPLE_COMMAND,
	R_CMD_NAME,
	R_CMD_WORD,
	R_CMD_PREFIX,
	R_CMD_SUFFIX,
	R_IO_REDIRECT,
	R_IO_FILE,
	R_FILENAME,
	R_IO_HERE,
	R_HERE_END
}	t_rules;

/*
** AST PARAMS
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
# define LEFT 0
# define RIGHT 1
# define ROOT 2

typedef enum e_ast_types
{
	A_CMD = 0,
	A_PARAM,
	A_FILE,
	A_AND_IF,
	A_OR_IF,
	A_DLESS,
	A_DGREAT,
	A_PIPE,
	A_RED_TO,
	A_RED_FROM,
	A_LIMITER
}	t_ast_types;

/*
** PARSER STRUCTURES
*/

typedef struct s_trans
{
	int	state;
	int	event;
	int	action;
	int	next;
	int	nb_reduce;
}		t_trans;

typedef struct s_stack
{
	int				type;
	int				state;
	void			*data;
	struct s_stack	*next;
}	t_stack;

/*
** AST STRUCTURE
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

/*
** PARSER FUNCTIONS
*/
t_node	*ms_parser(t_token *tok_list, t_trans **table);

t_trans	**ms_init_parsing_table(void);
void	ms_free_table(t_trans **trans);

t_stack	*ms_new_stack_item(void *content, int type, int state);
t_stack	**ms_pop_stack(t_stack **stack, int nb);
int		ms_add_front(t_stack **stack, t_stack *item);
void	ms_free_stack_item(t_stack *stack);
int		ms_free_stack(t_stack **stack, int return_code);

int		ms_ast_builder(t_ast_builder **builder, t_stack **popped, int reduc);

/*
** AST FUNCTIONS
*/
t_node	*ms_new_node(void *data, int type, int reduc);
void	ms_free_tree(t_node	*node);
void	ms_visit_ast(t_node *node, int mode);

int		ms_init_ast_builder(t_ast_builder **builder);
t_node	*ms_get_popped(t_ast_builder **builder, int reduc, int action);
int		ms_buffer_add_back(t_ast_builder **builder, t_node *new);
t_node	*ms_buffer_remove(t_ast_builder **builder, int to_remove);
void	ms_free_ast_builder(t_ast_builder **builder, int to_free);
int		ms_build_subtree(t_ast_builder **builder, t_stack **popped, \
			int reduc, t_node **node);
t_node	*ms_simplify_tree(t_node *tree);

int		ms_execute_ast(t_node *ast, char **envp);

#endif