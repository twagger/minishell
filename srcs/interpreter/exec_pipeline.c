/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:55:34 by twagner           #+#    #+#             */
/*   Updated: 2021/11/12 14:47:29 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "parser.h"

static char	**ms_visit(t_node *node, char **args, char **envp)
{
	if (!node)
		return (args);
	args = ms_visit(node->left, args, envp);
	args = ms_visit(node->right, args, envp);
	if (node->type == A_PARAM)
		args = ms_add_arg_back(args, node->data);
	else if (node->type == A_CMD)
	{
		args = ms_add_arg_front(args, node->data);
		if (!args)
			return (NULL);
	}
	return (args);
}

int	ms_exec_pipeline(t_node *node, char **envp, int nb_pipe)
{
	char	**args;

	(void)envp;
	(void)nb_pipe;
	args = ms_init_arg_array();
	args = ms_visit(node, args, envp);
	if (!args)
	{
		ms_free_arg_array(args);
		return (ERROR);
	}
	ms_free_arg_array(args);
	return (EXIT_SUCCESS);
}
