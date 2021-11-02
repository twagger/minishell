/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/11/02 12:07:16 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "ast.h"

static int	ms_is_builtin(char *command)
{
	if (ft_strncmp(command, "cd", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "env", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "echo", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "pwd", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "exit", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "export", ft_strlen(command)) == 0 || \
		ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		return (1);
	return (0);
}

static char	**ms_visit(t_node *node, char **args, char **envp)
{
	if (!node)
		return (args);
	args = ms_visit(node->left, args, envp);
	args = ms_visit(node->right, args, envp);
	if (node->type == A_OPE)
		args = ms_add_one_arg(args, node->data);
	else if (node->type == A_CMD)
	{
		args = ms_add_command(args, node->data);
		if (!args)
			return (NULL);
		if (ms_is_builtin(args[0]))
			ms_execute_builtin(args, envp);
		else
			ms_execute(args, envp);
		ms_free_arg_array(args);
		args = ms_init_arg_array();
	}
	return (args);
}

int	ms_execute_ast(t_node *ast, char **envp)
{
	char	**args;

	args = ms_init_arg_array();
	if (!ms_visit(ast, args, envp))
	{
		ms_free_arg_array(args);
		return (EXIT_FAILURE);
	}
	ms_free_arg_array(args);
	return (EXIT_SUCCESS);
}
