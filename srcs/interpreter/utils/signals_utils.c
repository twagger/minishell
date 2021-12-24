/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:06:31 by twagner           #+#    #+#             */
/*   Updated: 2021/12/24 11:01:23 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

void	ms_sig_handler(int sig)
{
	exit(sig);
}

void	ms_activate_signal_handler(void)
{
	signal(SIGINT, ms_sig_handler);
	signal(SIGQUIT, ms_sig_handler);
}

void	ms_ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}