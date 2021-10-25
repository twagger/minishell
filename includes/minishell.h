/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:53 by twagner           #+#    #+#             */
/*   Updated: 2021/10/25 16:25:28 by wlo              ###   ########.fr       */
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
# include "../libft/libft.h"

/*
** GLOBAL PARAMS
*/
# define ERROR -1
# define BUILTINS_PATH "/srcs/builtins"

typedef enum e_token_types
{
	WORD,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	PIPE,
	RED_TO,
	RED_FROM,
}	t_token_types;

typedef struct s_token
{
	int				type;
	void			*value;
	struct s_token	*next;
}	t_token;

/*
** CORE FUNCTIONS
*/
t_token	*ms_tokenizer(char *line);
char	**ms_parser(char *line);
char	**ft_split_qu(char *s, char c);
char	*check_if_envvar(char *cmd);
int		ft_strnchr(const char *s, char c, int index);
int		check_special_char(char *c, char *line);
int		sep(char s, char c);
int		count_w_qu_2(int state, char *s, char c, int *count);
int		count_w_qu(char *s, char c);
char	*ft_searchchr(char *s, char c);
int		len_w_qu(char *s, char c);
int		int_word(char *s, char c, int index, char ***arr);
int		ms_execute(char **args);

/*
** UTILS
*/
int		ft_cleaner(char *line, char **args, int exit_code);
int		ms_getbin_path(char **bin);

#endif