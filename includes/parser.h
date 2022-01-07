/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:55:55 by twagner           #+#    #+#             */
/*   Updated: 2022/01/07 23:02:50 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER2_H
# define PARSER2_H
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
	ACT_SHIFT,
	ACT_REDUCE,
	ACT_ACCEPT,
	ACT_REJECT
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
	struct s_node	*next;
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
** LEXER
*/
t_token	*ms_tokenizer(char *line);
t_token	*ft_newtoken(void *content);
char	**ft_split_qu(char *s, char c);
int		count_w_qu(char *s);
int		int_word(char *s, char c, int index, char ***arr);
char	*check_if_envvar(char *cmd);
int		len_w_qu(char *s, char c);
int		sep(char s, char c);
void	ft_tokenadd_back(t_token **lst, t_token *new);
void	ms_free_tokens(t_token *tokens);

/*
** PARSER
*/
t_node	*ms_parser(t_token *input, t_trans **parsing_table);
int		ms_push_input(t_stack **stack, t_token *input);
int		ms_push_reduction(t_stack **stack, int reduction);
int		ms_push_state(t_stack **stack, int state);
t_trans	*ms_get_entry(t_token *input, t_trans **parsing_table, int state);
int		ms_get_next_state(t_stack *stack, t_trans **parsing_table);

/*
** PARSING TABLE
*/
t_trans	**ms_init_parsing_table(void);
void	ms_free_table(t_trans **trans);

/*
** STACK
*/
t_stack	*ms_init_stack(void);
void	ms_clear_stack(t_stack *stack);
t_stack	*ms_pop_stack(t_stack **stack, int nb);
void	ms_add_popped(t_stack **popped, t_stack *stack);
t_node	*ms_stack_to_node(t_stack *popped);

/*
** CLEANING
*/
void	ms_clear_input(t_token *input);
void	ms_clear_tree(t_node **node);
void	ms_parser_cleaning(\
	t_node **tree, t_stack *stack, t_token *input, int ret);

/*
** OUTPUT
*/
int		ms_add_tree(t_node **tree, t_stack **popped, int reduction);
int		ms_execute_ast(t_node *ast, int exit_code);

#endif