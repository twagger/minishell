/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:53 by twagner           #+#    #+#             */
/*   Updated: 2021/10/19 15:40:04 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include "libft.h"

/*
** GLOBAL PARAMS
*/
# define ERROR -1
# define ERROR_BIN_NOT_FOUND 127

/*
** AST NODE TYPES
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
} 	t_ast_node_types;

/*
** DATA STRUCTURES
*/
typedef struct s_node
{
	int				type;
	void			*data;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

/*
** CORE FUNCTIONS
*/
t_node	*ms_parser(char *line, char **envp);
int		ms_execute(char **args);
int		ms_execute_ast(t_node *ast, char **envp);

/*
** AST UTILS
*/
t_node	*ms_create_node(void *data, int type);

/*
** UTILS
*/
int		ft_cleaner(char *line, char **args, int exit_code);
int		ms_getbin_path(char **bin);
char	**ms_init_arg_array();
int		ms_add_one_arg(char **array, char *data);
void	ms_free_arg_array(char **array);
void	ms_empty_arg_array(char **array);

/*
** BUILTINS
*/
int		ms_echo(int ac, char **av);
int		ms_cd(int ac, char **av);
int		ms_pwd(int ac, char **av);
int		ms_env(int ac, char **av, char **envp);
//int		ms_export(int ac, char **av, char **envp, t_param *prm);
int		ms_unset(int ac, char **av, char **envp);
int		ms_exit(int ac, char **av);


#endif