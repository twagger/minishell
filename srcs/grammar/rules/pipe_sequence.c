/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:23:05 by twagner           #+#    #+#             */
/*   Updated: 2021/10/24 11:34:28 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "state_machine.h"

struct s_pipe_sequence    *pipe_sequence(struct s_parser *p)
{
    struct s_pipe_sequence    *ps;
    struct s_simple_command   *sc;

    ps = malloc(sizeof(struct s_pipe_sequence));
    while (sc = simple_command(p))
    {
        /* This function pushes a new element into a linked list */
        ft_lstpush(sc, &ps->simple_commands);
        if (p->tokens->type == T_PIPE)
            p->tokens = p->tokens->next;
    }
    if (ps->sc)
        return (ps);
    free(ps);
    return (NULL);
}
