/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:48:17 by twagner           #+#    #+#             */
/*   Updated: 2021/12/23 23:27:29 by twagner          ###   ########.fr       */
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

void	ms_close_unused_fds(t_pipe *pipe)
{
	t_pipe	*begin;

	begin = pipe;
	while (pipe)
	{
		if (!pipe->is_curr_read)
			close(pipe->fd[1]);
		if (!pipe->is_curr_write)
			close(pipe->fd[0]);
		pipe = pipe->next;
	}
	pipe = begin;
}

int	ms_update_curr_fds(t_pipe *pipe)
{
	int		change_next;
	t_pipe	*begin;

	begin = pipe;
	change_next = 0;
	while (pipe)
	{
		if (change_next)
		{
			pipe->is_curr_write = 1;
			change_next = 0;
		}
		else if (!pipe->is_curr_read && pipe->is_curr_write)
		{
			pipe->is_curr_read = 1;
			pipe->is_curr_write = 0;
			change_next = 0;
		}
		else if (pipe->is_curr_read && !pipe->is_curr_write)
			pipe->is_curr_read = 0;
		pipe = pipe->next;
	}
	pipe = begin;
}

void	ms_connect_read_fd(t_pipe *pipe)
{
	t_pipe	*begin;

	begin = pipe;
	while (pipe)
	{
		if (pipe->is_curr_read)
			dup2(0, pipe->fd[0]);
		if (pipe->is_curr_write)
			dup2(1, pipe->fd[1]);
		pipe = pipe->next;
	}
	pipe = begin;
}

t_pipe	*ms_pipe_new()
{
	t_pipe	*new;

	new = (t_pipe *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	pipe(new->fd);
	new->is_curr_read = 0;
	new->is_curr_write = 0;
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
		*lst = new;
}

t_pipe	*ms_init_pipes(int nb)
{
	int		i;
	t_pipe	*pipe;

	i = -1;
	pipe = NULL;
	while (++i < nb)
		ms_pipe_add_back(&pipe, ms_pipe_new());
	if (pipe)
		pipe->is_curr_read = 1;
	return (pipe);
}
