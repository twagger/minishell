/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sig_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:27:50 by twagner           #+#    #+#             */
/*   Updated: 2022/01/11 16:15:20 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

void	ms_hd_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		close(0);
	}
}

void	ms_activate_hd_signal_handler(void)
{
	signal(SIGINT, ms_hd_sig_handler);
	signal(SIGQUIT, ms_hd_sig_handler);
}

void	ms_restore_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
