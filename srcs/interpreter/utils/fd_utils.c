/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 09:08:21 by twagner           #+#    #+#             */
/*   Updated: 2021/12/26 09:19:09 by twagner          ###   ########.fr       */
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