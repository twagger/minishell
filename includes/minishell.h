/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:53 by twagner           #+#    #+#             */
/*   Updated: 2021/12/28 18:05:04 by ifeelbored       ###   ########.fr       */
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
# define ERROR_BIN_NOT_FOUND 127

/*
** STRUCTURES
*/

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

/*
** FUNCTIONS
*/

/*
** core
*/
int		ms_execute(char **args, char **envp);
int		ms_is_builtin(char *command);
int		ms_execute_builtin(char **args, char **envp);

/*
** builtins
*/
int		ms_echo(int ac, char **av);
int		ms_cd(int ac, char **av, char **envp);
int		ms_pwd(int ac, char **av);
int		ms_env(int ac, char **av, char **envp);
int		ms_export(int ac, char **av, char **envp);
int		ms_is_param_new(char *param, t_env *envp);
int		ms_is_param_ok(char	*param);
int		add_newenvp(char *cmd, t_env **envp);
t_env	*init_env(char **envp);
int		ms_unset(int ac, char **av, char **envp);
int		ms_exit(int ac, char **av);

/*
** builtins utils
*/
char	**ms_split_cdpath(char const *s, char c);
char	*ms_convert_canonical(char *path);

#endif