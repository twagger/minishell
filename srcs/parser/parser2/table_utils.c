/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:01:03 by twagner           #+#    #+#             */
/*   Updated: 2022/01/07 08:50:21 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser2.h"

t_trans *ms_get_entry(t_token *input, t_trans **parsing_table, int state)
{
	int		i;
	int		input_type;
	t_trans *table_entry;

	table_entry = NULL;
	input_type = -1;
	if (input)
		input_type = input->type;
	i = -1;
	while (parsing_table[++i])
	{
		if (parsing_table[i]->state == state)
		{
			if (parsing_table[i]->event == input_type)
				return (parsing_table[i]);
			else if (parsing_table[i]->event == DEFAULT)
				table_entry = parsing_table[i];
		}
	}
	return (table_entry);
}

// Get next state
