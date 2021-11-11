/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/11/11 16:09:12 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "parser.h"

int	ms_is_builtin(char *command)
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

/*
** VISIT AST
** This function builds an arg array from the ast to be pushed 
** into Pipex, Execve or a builtin for execution
*/

/* static char	**ms_visit(t_node *node, char **args, char **envp)
{
	if (!node)
		return (args);
	args = ms_visit(node->left, args, envp);
	args = ms_visit(node->right, args, envp);
	if (node->type == A_PARAM)
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
} */

static char	**ms_visit(t_node *node, char **args, char **envp)
{
	if (!node)
		return (args);
	args = ms_visit(node->left, args, envp);
	args = ms_visit(node->right, args, envp);
	args = ms_add_one_arg(args, node->data);
	return (args);
}

int	ms_execute_ast(t_node *ast, char **envp)
{
	int		i;
	char	**args;

	args = ms_init_arg_array();
	args = ms_visit(ast, args, envp);
	if (!args)
	{
		ms_free_arg_array(args);
		return (EXIT_FAILURE);
	}
	else
	{
		i = -1;
		while (args[++i])
			printf("ARGS : %s\n", args[i]);
	}
	// args > Table of arguments
	// if pipe in cmd > pipex (args)
	// else 
	// - buildins or execve (+ redirection ?)
	ms_free_arg_array(args);
	return (EXIT_SUCCESS);
}
