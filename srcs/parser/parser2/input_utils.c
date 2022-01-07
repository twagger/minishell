/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:58:18 by twagner           #+#    #+#             */
/*   Updated: 2022/01/07 08:50:07 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser2.h"

void	ms_clear_input(t_token *input)
{
	t_token	*next;

	while (input)
	{
		next = input->next;
		free(input->value);
		free(input);
		input = next;
	}
}