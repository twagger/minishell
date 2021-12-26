/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:33:35 by twagner           #+#    #+#             */
/*   Updated: 2021/12/26 15:50:32 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H
# include "parser.h"

/*
** STRUCTURES
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
** FUNCTIONS
*/

int		ms_getbin_path(char **bin);
char	**ms_init_arg_array(void);
char	**ms_add_arg_back(char **array, char *data);
char	**ms_add_arg_front(char **array, char *cmd);
void	ms_free_arg_array(char **array);

int		ms_is_builtin(char *command);
int		ms_execute_builtin(char **args, char **envp);

int		ms_exec_pipeline(t_node *ast, char **envp, int exit_code, int nb);
int		ms_exec_command(t_node *ast, char **envp);
int		ms_exec_simple_command(t_node *ast, char **envp, int exit_code, int *fd);
int		ms_exec_piped_command(t_node *ast, char **envp, int exit_code);
int		ms_exec_comb_command(t_node *node, char **envp, int nb_pipe);

void	ms_do_redirections(t_node *node);
void	ms_save_std_fd(int *fd);
int		ms_restore_std_fd(int *fd);

t_pipe	*ms_init_pipes(int nb);
void	ms_free_pipe_list(t_pipe *pipe);
void	ms_update_curr_fds(t_pipe *pipe);
void	ms_connect_pipe(t_pipe *pipe);
void	ms_close_unused_fds(t_pipe *pipe);

int		ms_search_ast(t_node *node, int needle, int nb);

void	ms_activate_signal_handler(void);
void	ms_ignore_signals(void);
int		ms_get_exit_status(int status);

#endif
