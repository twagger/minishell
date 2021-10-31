/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:53 by twagner           #+#    #+#             */
/*   Updated: 2021/10/31 09:23:50 by twagner          ###   ########.fr       */
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
# include "libft.h"

/*
** GLOBAL PARAMS
*/
# define ERROR -1
# define ERROR_BIN_NOT_FOUND 127

/*
** CORE FUNCTIONS
*/

int		ms_execute(char **args, char **envp);
int		ms_execute_builtin(char **args, char **envp);

/*
** UTILS
*/

int		ft_cleaner(char *line, char **args, int exit_code);
int		ms_getbin_path(char **bin);
char	**ms_init_arg_array(void);
char	**ms_add_one_arg(char **array, char *data);
char	**ms_add_command(char **array, char *cmd);
void	ms_free_arg_array(char **array);

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