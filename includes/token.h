/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:15:58 by twagner           #+#    #+#             */
/*   Updated: 2021/10/24 11:17:40 by twagner          ###   ########.fr       */
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
	0 WORD = 0,
	1 ASSIGNMENT_WORD,
	2 NEWLINE,
	3 IO_NUMBER,
	4 AND_IF,
	5 OR_IF,
	6 DLESS,
	7 DGREAT,
	8 PIPE,
	9 RED_TO,
	10 RED_FROM
} 	e_token_types;

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
char 	*check_if_envvar(char *cmd);

#endif