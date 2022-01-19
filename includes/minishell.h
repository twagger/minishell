/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:53 by twagner           #+#    #+#             */
/*   Updated: 2022/01/19 22:55:56 by ifeelbored       ###   ########.fr       */
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
# include <fcntl.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <signal.h>
# include "libft.h"

/*
** PARAMS
*/
# define ERROR -1
# define RET_OK 0
# define ST_EXIT -2
# define ERROR_BIN_NOT_FOUND 127

/*
** STRUCTURES
*/

/*
** history
*/
typedef struct s_history
{
	int					type;
	char				*data;
	char				*saved_data;
	struct s_history	*previous;
	struct s_history	*next;
}						t_history;

typedef struct s_env
{
	char			*name;
	char			*content;
	int				if_env;
	struct s_env	*next;
}					t_env;

/*
** lexer
*/

typedef struct s_cd
{
	char	*ar;
	char	*code;

}	t_cd;

typedef struct s_quote
{
	int				sq;
	int				dq;
	int				state;
	int				last_id;
}	t_quote;

typedef struct s_q
{
	int				b;
	int				e;
	int				q;
}	t_q;

typedef struct s_token
{
	int				type;
	void			*value;
	int				qt_rm;
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
	int				qt_rm;
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
	int				qt_rm;
	void			*data;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*next;
}					t_node;

/*
** interpreter
*/
typedef struct s_pipe
{
	int				fd[2];
	int				is_curr_read;
	int				is_curr_write;
	struct s_pipe	*next;
}					t_pipe;

typedef enum e_pipe_ends
{
	READ_END,
	WRITE_END
}	t_pipe_ends;

/*
** garbage
*/
typedef struct s_garbage_coll
{
	char		**envp;
	t_history	*histo;
	t_trans		**ptable;
	t_node		*tree;
	int			*heredoc_fds;
}				t_garbage_coll;

extern t_env	*g_envp;

/*
** FUNCTIONS
*/

/*
** core
*/
int		ms_is_builtin(char *command);
int		ms_execute_builtin(char **args);

/*
** env
*/
int		ms_setenv(char *name, char *value);
char	*ms_getenv(char *var);
void	ms_clearenv(void);
void	ft_envadd(t_env **lst, t_env *new);
char	**ms_g_envp_to_envp(void);

/*
** builtins
*/
int		ms_echo(int ac, char **av);
int		ms_cd(int ac, char **av);
int		ms_pwd(int ac, char **av);
int		ms_env(int ac, char **av);
int		ms_export(int ac, char **av);
int		ms_is_param_new(char *param, t_env *envp);
int		ms_is_param_ok(char	*param);
int		add_newenvp(char *cmd, t_env **envp);
t_env	*ft_envnew_1(char *envp, int if_env);
t_env	*init_env(char **envp);
int		realloc_var(char *cmd, t_env *envp);
int		ms_unset(int ac, char **av);
int		ms_exit(int ac, char **av);

/*
** builtins utils
*/
char	**ms_split_cdpath(char const *s, char c);
char	*ms_convert_canonical(char *path);
char	*ms_join_with_slash(char *s1, char *s2);

/*
** global utils
*/
void	ms_free_str_array(char **str);
void	*ms_free_str_array_null(char **str);
int		ms_increment_shlvl(void);

#endif