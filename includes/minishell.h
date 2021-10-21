/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:53 by twagner           #+#    #+#             */
/*   Updated: 2021/10/21 14:59:00 by wlo              ###   ########.fr       */
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
//# include "libft.h"

/*
** GLOBAL PARAMS
*/
# define ERROR -1
# define BUILTINS_PATH "/srcs/builtins"

/*
** CORE FUNCTIONS
*/
char	**ms_parser(char *line);
char	**ft_split_qu(char *s, char c);
char	*check_if_envvar(char *cmd);
int		check_special_char(char *c, char *line);
int		ms_execute(char **args);

/*
** UTILS
*/
int		ft_cleaner(char *line, char **args, int exit_code);
int		ms_getbin_path(char **bin);

#endif