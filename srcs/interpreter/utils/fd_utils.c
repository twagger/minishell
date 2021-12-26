/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 09:08:21 by twagner           #+#    #+#             */
/*   Updated: 2021/12/26 15:29:15 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

void	ms_save_std_fd(int *fd)
{
	fd[READ_END] = dup(STDIN_FILENO);
	fd[WRITE_END] = dup(STDOUT_FILENO);
}

int	ms_restore_std_fd(int *fd)
{
	fd[READ_END] = dup2(fd[READ_END], STDIN_FILENO);
	fd[WRITE_END] = dup2(fd[WRITE_END], STDOUT_FILENO);
	if (fd[READ_END] == ERROR || fd[WRITE_END] == ERROR)
		return (ERROR);
	return (0);
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
			change_next = 1;
		}
		else if (pipe->is_curr_read && !pipe->is_curr_write)
			pipe->is_curr_read = 0;
		pipe = pipe->next;
	}
	pipe = begin;
}
