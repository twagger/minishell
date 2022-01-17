/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:55:55 by twagner           #+#    #+#             */
/*   Updated: 2022/01/17 18:35:39 by ifeelbored       ###   ########.fr       */
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
** ENUMS
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
t_token	*ms_tokenizer(char *line, int exit_code);
t_token	*ft_newtoken(void *content, int c);
void	ft_tokenadd_back(t_token **lst, t_token *new);
void	ms_free_tokens(t_token *tokens);
t_token	*check_each(int len, char *s, char *code);
void	initial_quote(t_quote *quote);
void	initial(char *new);
int		db(char *arr, int start, int end, char c);
int		ft_strdb(char *s, char c);
int		count_len(char *s);
int		ft_strchr_do(char *arr, int start, int end);
int		replace_quote(t_cd cd, char *new, int *i_arr, int *i_new);
int		replace_var(t_cd cd, char *new, int *i_new);
int		sep(char s);

/*
** PARSER
*/
t_node	*ms_parser(t_token *input, t_trans **parsing_table);
int		ms_push_input(t_stack **stack, t_token *input);
int		ms_push_reduction(t_stack **stack, int reduction);
int		ms_push_state(t_stack **stack, int state);
t_trans	*ms_get_entry(t_token *input, t_trans **parsing_table, t_stack *stack);
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
t_node	*ms_fix_param_types(t_node *tree);
int		ms_execute_ast(t_node *ast, t_garbage_coll *garcol);

#endif