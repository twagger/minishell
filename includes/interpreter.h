/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:33:35 by twagner           #+#    #+#             */
/*   Updated: 2021/11/12 11:42:04 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H
# include "minishell.h"
# include "parser.h"

/*
** INTERPRETER STRUCTURES
*/

typedef struct s_arglist
{
	int					type;
	void				*data;
	struct s_arglist	*next;
}						t_arglist;

/*
** INTERPRETER FUNCTIONS
*/

int			ms_getbin_path(char **bin);
char		**ms_init_arg_array(void);
char		**ms_add_arg_back(char **array, char *data);
char		**ms_add_arg_front(char **array, char *cmd);
void		ms_free_arg_array(char **array);

t_arglist	*ms_arglist_new(void *data, int type);
t_arglist	*ms_arglist_last(t_arglist *lst);
void		ms_arglistadd_back(t_arglist **alst, t_arglist *new);
void		ms_arglistadd_front(t_arglist **alst, t_arglist *new);
void		ms_arglist_clear(t_arglist **lst);

int			ms_exec_pipeline(t_arglist *args, char **envp, int nb_pipe);
int			ms_exec_command(t_arglist *args, char **envp);
int			ms_exec_simple_command(t_arglist *arglist, char **envp);

# endif