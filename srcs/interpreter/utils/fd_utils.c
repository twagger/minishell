/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 09:08:21 by twagner           #+#    #+#             */
/*   Updated: 2021/12/26 14:48:22 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

void	ms_save_std_fd(int *fd)
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
}

int	ms_restore_std_fd(int *fd)
{
	fd[0] = dup2(fd[0], STDIN_FILENO);
	fd[1] = dup2(fd[1], STDOUT_FILENO);
	if (fd[0] == ERROR || fd[1] == ERROR)
		return (ERROR);
	return (0);
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

void	ms_update_curr_fds(t_pipe *pipe)
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
