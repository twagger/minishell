/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:42:03 by twagner           #+#    #+#             */
/*   Updated: 2021/11/23 15:47:29 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_handler(int sig, siginfo_t *siginfo, void *context)
{
	if (context && siginfo)
		usleep(1);
	if (sig == SIGUSR1)
		g_byte.c += 1 << (7 - g_byte.size);
	++g_byte.size;
	if (g_byte.size == 8)
	{
		write(1, &g_byte.c, 1);
		ft_init_byte(&g_byte);
	}
}

int	ms_activate_signal(void)
{
	struct sigaction	act;

	act.sa_sigaction = &ft_signal_handler;
	sigaction(SIGINT, &act, NULL);
	return (0);
}