/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:48:17 by twagner           #+#    #+#             */
/*   Updated: 2021/12/03 12:29:55 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

void	ms_free_pipe_list(t_pipe *pipe)
{
	t_pipe	*next;

	while (pipe)
	{
		next = pipe->next;
		free(pipe);
		pipe = next;
	}
}

int	ms_close_unused_fds(t_pipe *pipe)
{
	// close all FD except when curr == 1
}

int	ms_connect_read_fd(t_pipe *pipe)
{
	// if pipe->is_curr_in && pipe->is_curr_out 
		// ne rien faire, on est sur le premier
	// else
	// trouver le pipe avec un is_curr_in a 1
	// dup2(0, pipe->fd[0])
}

int	ms_connect_write_fd(t_pipe *pipe)
{
	// trouver le pipe avec un is_curr_out a 1
	// dup2(1, pipe->fd[1])
}

int	ms_update_curr_fds(t_pipe *pipe)
{
	// update the curr FDS before fork
}

t_pipe	*ms_pipe_new()
{
	t_pipe	*new;

	new = (t_pipe *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	pipe(new->fd);
	new->is_curr_in = 0;
	new->is_curr_out = 0;
	new->next = NULL;
	return (new);
}

void	ms_pipe_add_back(t_pipe **lst, t_pipe *new) 
{
	t_pipe	*begin;

	begin = *lst;
	if (*lst)
	{
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = new;
		*lst = begin;
	}
	else
	{
		if (new)
		{
			new->is_curr_in = 1;
			new->is_curr_out = 1;
		}
		*lst = new;
	}
}

t_pipe	*ms_init_pipes(int nb)
{
	int		i;
	t_pipe	*pipe;

	i = -1;
	pipe = NULL;
	while (++i < nb)
		ms_pipe_add_back(&pipe, ms_pipe_new());
	return (pipe);
}
