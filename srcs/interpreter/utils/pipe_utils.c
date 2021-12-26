/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:48:17 by twagner           #+#    #+#             */
/*   Updated: 2021/12/26 15:22:45 by twagner          ###   ########.fr       */
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

void	ms_connect_pipe(t_pipe *pipe)
{
	t_pipe	*begin;

	begin = pipe;
	while (pipe)
	{
		if (pipe->is_curr_read)
			dup2(pipe->fd[READ_END], STDIN_FILENO);
		if (pipe->is_curr_write)
			dup2(pipe->fd[WRITE_END], STDOUT_FILENO);
		close(pipe->fd[READ_END]);
		close(pipe->fd[WRITE_END]);
		pipe = pipe->next;
	}
	pipe = begin;
}

t_pipe	*ms_pipe_new(void)
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
		pipe->is_curr_write = 1;
	return (pipe);
}
