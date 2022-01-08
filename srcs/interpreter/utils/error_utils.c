/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 15:42:00 by twagner           #+#    #+#             */
/*   Updated: 2022/01/08 15:46:17 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

void	ms_print_exec_error(char *cmd, int error_code)
{
	if (error_code == 127)
		printf("minishell: %s: command not found\n", cmd);
	else
		printf("minishell: %s\n", strerror(error_code));
}