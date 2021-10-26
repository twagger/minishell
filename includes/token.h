/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:15:58 by twagner           #+#    #+#             */
/*   Updated: 2021/10/26 11:29:53 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "minishell.h"

/*
** TOKEN STRUCTURES
*/
typedef enum e_token_types
{
	WORD = 0,
	ASSIGNMENT_WORD,
	NEWLINE,
	IO_NUMBER,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	PIPE,
	RED_TO,
	RED_FROM
}	t_token_types;

typedef struct s_token
{
	int				type;
	void			*value;
	struct s_token	*next;
}					t_token;

/*
** TOKEN FUNCTIONS
*/
t_token	*ms_tokenizer(char *line);
char	**ft_split_qu(char *s, char c);
int		check_special_char(char *c, char *line);
char	*check_if_envvar(char *cmd);

#endif