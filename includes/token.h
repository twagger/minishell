/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:15:58 by twagner           #+#    #+#             */
/*   Updated: 2021/10/31 21:33:30 by twagner          ###   ########.fr       */
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
	END = -2,
	WORD = 0,
	ASSIGNMENT_WORD,
	TOK_NEWLINE,
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
int		count_w_qu(char *s, char c);
int		int_word(char *s, char c, int index, char ***arr);
char	*check_if_envvar(char *cmd);
int		len_w_qu(char *s, char c);
int		sep(char s, char c);
t_token	*ft_newtoken(void *content);
void	ft_tokenadd_back(t_token **lst, t_token *new);
void	ms_free_tokens(t_token *tokens);

#endif