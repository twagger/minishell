/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:23:19 by twagner           #+#    #+#             */
/*   Updated: 2021/10/16 14:44:55 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_execute_builtin(char **args, char **envp, t_param *prm)
{
	int	ac;
	int	ret;

	ret = 0;
	ac = 0;
	while (args[ac])
		++ac;
	if (ft_strncmp(args[0], "cd", 3) == 0)
		ret = ms_cd(ac, args);
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		ret = ms_pwd(ac, args);
	if (ft_strncmp(args[0], "echo", 3) == 0)
		ret = ms_echo(ac, args);
	if (ft_strncmp(args[0], "env", 4) == 0)
		ret = ms_env(ac, args, envp);
	if (ft_strncmp(args[0], "export", 7) == 0)
		ret = ms_export(ac, args, envp, prm);
	if (ft_strncmp(args[0], "unset", 6) == 0)
		ret = ms_unset(ac, args, envp);
	if (ft_strncmp(args[0], "exit", 5) == 0)
		ret = ms_exit(ac, args);
	return (ret);
}
