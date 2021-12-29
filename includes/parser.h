/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:18:13 by twagner           #+#    #+#             */
/*   Updated: 2021/12/29 15:14:21 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

/*
** PARSER PARAMS
*/
# define NB_TRANS 100
# define AUTOMATON "./srcs/parser/parser/parsing_table"
# define NO_ACTION -1
# define DEFAULT -1
# define TO_PROMOTE 0
# define TO_CHILD 1
# define ROOT -2

typedef enum e_actions
{
	SHIFT,
	REDUCE,
	ACCEPT
}	t_actions;

typedef enum e_rules
{
	R_PIPE_SEQUENCE = 100,
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

/*
** STRUCTURES
*/

/*
** lexer
*/
typedef enum e_token_types
{
	T_END = -2,
	T_WORD = 0,
	T_RED_TO,
	T_RED_FROM,
	T_DLESS,
	T_DGREAT,
	T_PIPE	
}	t_token_types;

typedef struct s_token
{
	int				type;
	void			*value;
	struct s_token	*next;
}					t_token;

/*
** parser
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
** ast
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
	A_RED_TO,
	A_RED_FROM,
	A_DLESS,
	A_DGREAT,
	A_PIPE,
	A_PARAM,
	A_FILE,
	A_LIMITER
}	t_ast_types;

/*
**FUNCTIONS
*/

/*
** lexer
*/
t_token	*ms_tokenizer(char *line);
t_token	*ft_newtoken(void *content);
char	**ft_split_qu(char *s, char c);
int		check_special_char(char *c, char *line);
int		count_w_qu(char *s, char c);
int		int_word(char *s, char c, int index, char ***arr);
char	*check_if_envvar(char *cmd);
int		len_w_qu(char *s, char c);
int		sep(char s, char c);
void	ft_tokenadd_back(t_token **lst, t_token *new);
void	ms_free_tokens(t_token *tokens);

/*
** parser
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
** ast
*/
t_node	*ms_new_node(void *data, int type, int reduc);
void	ms_free_tree(t_node	*node);
void	ms_visit_ast(t_node *node, int mode);
int		ms_init_ast_builder(t_ast_builder **builder);
t_node	*ms_get_popped(t_ast_builder **builder, int reduc, int action);
int		ms_buffer_add_back(t_ast_builder **builder, t_node *new);
t_node	*ms_buffer_remove(t_ast_builder **builder, int to_remove);
void	ms_free_ast_builder(t_ast_builder **builder, int to_free);
t_node	*ms_fix_param_types(t_node *tree);
int		ms_execute_ast(t_node *ast, int exit_code);
int		ms_build_subtree(t_ast_builder **builder, t_stack **popped, \
		t_node **node);

#endif