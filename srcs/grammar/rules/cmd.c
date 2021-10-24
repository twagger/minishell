/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:24:11 by twagner           #+#    #+#             */
/*   Updated: 2021/10/23 10:24:32 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing_tree.h"

/*
** struct s_parser is a data type containing informations about the current parser
** (like the tokens list)
*/
struct s_cmd_word    *cmd_word(struct s_parser *p)
{
    struct s_cmd_word    *w = NULL;

    /*
    ** p->tokens is a linked list containing all the tokens
    ** p->tokens->type is an enum corresponding to the token's type
    */
    if (p->tokens->type == T_WORD)
    {
        w = malloc(sizeof(struct s_cmd_word));
        w->data = strdup(t->data);
        p->tokens = p->tokens->next
        return (w);        
    }
    else
        return (NULL);
}