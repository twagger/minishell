/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:33:35 by twagner           #+#    #+#             */
/*   Updated: 2021/11/12 18:15:46 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H
# include "minishell.h"
# include "parser.h"

/*
** INTERPRETER FUNCTIONS
*/

int			ms_getbin_path(char **bin);
char		**ms_init_arg_array(void);
char		**ms_add_arg_back(char **array, char *data);
char		**ms_add_arg_front(char **array, char *cmd);
void		ms_free_arg_array(char **array);

int			ms_exec_pipeline(t_node *ast, char **envp);
int			ms_exec_command(t_node *ast, char **envp);
int			ms_exec_simple_command(t_node *ast, char **envp);

#endif