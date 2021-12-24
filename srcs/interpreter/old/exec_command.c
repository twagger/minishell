// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exec_command.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/11/12 09:55:22 by twagner           #+#    #+#             */
// /*   Updated: 2021/11/12 14:52:53 by twagner          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "interpreter.h"
// #include "parser.h"

// // typedef struct s_cmds
// // {
// // 	char			**cmds;
// // 	char			*redi;
// // 	int				type;
// // }	t_cmds;

// static int	ms_args_len(char **args)
// {
// 	int	i;

// 	i = 0;
// 	while (args[i])
// 		++i;
// 	return (i);
// }

// static void	ms_free_arg_array_re(char **args)
// {
// 	if (args)
// 	{
// 		while (*args)
// 		{
// 			free(*args);
// 			++args;
// 		}
// 	}
// }

// t_cmds	*ms_init_arg_array_re(void)
// {

// 	t_cmds	*args;
// 	char	**array;
// 	char	*redi;

// 	args = malloc(sizeof(t_cmds));
// 	if (!args)
// 		return (NULL);
// 	array = (char **)malloc(sizeof(*array));
// 	if (!array)
// 		return (NULL);
// 	*array = NULL;
// 	redi = NULL;
// 	args->cmds = array;
// 	args->redi = redi;
// 	args->type = 0;
// 	return (args);
// }

// void	read_line(int fd, char *keyword)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("heredoc> ");
// 		if (line)
// 		{
// 			if (!ft_strcmp(line, keyword))
// 			{
// 				free(line);
// 				break ;
// 			}
// 			write(fd, line, ft_strlen(line));
// 			write(fd, "\n", 1);
// 		}
// 		free(line);
// 	}
// }

// t_cmds *ms_add_arg_back_cmd(t_cmds *args, char *data)
// {
// 	int		i;
// 	int		ac;
// 	char	**new;

// 	if (!args)
// 		return (NULL);
// 	ac = ms_args_len(args->cmds);
// 	new = (char **)malloc(sizeof(*new) * (ac + 2));
// 	if (!new)
// 	{
// 		ms_free_arg_array_re(args->cmds);
// 		return (NULL);
// 	}
// 	new[ac + 1] = NULL;
// 	i = -1;
// 	while (args->cmds[++i])
// 		new[i] = ft_strdup(args->cmds[i]);
// 	new[i] = ft_strdup(data);
// 	ms_free_arg_array_re(args->cmds);
// 	args->cmds = new;
// 	return (args);
// }

// t_cmds *ms_add_arg_front_cmd(t_cmds *args, char *cmd)
// {
// 	int		i;
// 	int		ac;
// 	char	**new;

// 	if (!args)
// 		return (NULL);
// 	ac = ms_args_len(args->cmds);
// 	new = (char **)malloc(sizeof(*new) * (ac + 2));
// 	if (!new)
// 	{
// 		ms_free_arg_array_re(args->cmds);
// 		return (NULL);
// 	}
// 	new[ac + 1] = NULL;
// 	new[0] = ft_strdup(cmd);
// 	i = -1;
// 	while (args->cmds[++i])
// 		new[i + 1] = ft_strdup(args->cmds[i]);
// 	ms_free_arg_array_re(args->cmds);
// 	args->cmds = new;
// 	return (args);
// }

// t_cmds *ms_add_arg(t_cmds *args, char *data)
// {
// 	char	*new;

// 	new = ft_strdup(data);
// 	args->redi = new;
// 	return (args);
// }

// void rediction_execut(t_cmds *args, char **envp)
// {
// 	int		file;
// 	int		copy;

// 	file = 0;
// 	fprintf(stderr,"exute%s, %s, %d\n", args->cmds[0], args->redi, args->type);
// 	if (args->type == A_RED_FROM)
// 	{
// 		copy = dup(STDIN_FILENO);
// 		file = open(args->redi, O_RDONLY);
// 		if (file < 0)
// 		{
// 			perror("open:");
// 			exit(1);
// 		}
// 		if (dup2(file, STDIN_FILENO) < 0)
// 		{
// 			perror("dup2 in open:");
// 			exit(1);
// 		}
// 	}
// 	else if (args->type == A_RED_TO)
// 	{
// 		copy = dup(STDOUT_FILENO);
// 		file = open(args->redi, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 		if (file < 0)
// 		{
// 			perror("open:");
// 			exit(1);
// 		}
// 		if (dup2(file, STDOUT_FILENO) < 0)
// 		{
// 			perror("dup2 in open:");
// 			exit(1);
// 		}
// 	}
// 	else if (args->type == A_DGREAT)
// 	{
// 		copy = dup(STDOUT_FILENO);
// 		file = open(args->redi, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 		if (file < 0)
// 		{
// 			perror("open:");
// 			exit(1);
// 		}
// 		if (dup2(file, STDOUT_FILENO) < 0)
// 		{
// 			perror("dup2 in open:");
// 			exit(1);
// 		}
// 	}
// 	else
// 	{
// 		fprintf(stderr,"here_doc\n");
// 		copy = dup(STDIN_FILENO);
// 		file = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 		if (file < 0)
// 		{
// 			perror("open:");
// 			exit(1);
// 		}
// 		read_line(file, args->redi);
// 		close(file);
// 		file = open(".temp", O_RDONLY);
// 		if (dup2(file, STDIN_FILENO) < 0)
// 		{
// 			perror("dup2 in open:");
// 			exit(1);
// 		}
// 	}
// 	if (ms_is_builtin(args->cmds[0]))
// 		ms_execute_builtin(args->cmds, envp);
// 	else
// 	{
// 		ms_execute(args->cmds, envp);
// 		fprintf(stderr,"exute??\n");
// 	}
// 	if (args->type == A_DGREAT ||  args->type == A_RED_TO)
// 	{
// 		dup2(copy, 1);
// 	}
// 	else if (args->type == A_RED_FROM || args->type == A_DLESS)
// 	{
// 		dup2(copy, 0);
// 	}
// 	if (file)
// 		close(file);
// 	if (!access(".temp", F_OK))
//         unlink(".temp");
// }
// static t_cmds *ms_visit(t_node *node, t_cmds *args, char **envp)
// {
// 	if (!node)
// 		return (args);
// 	if (node->type != -1)
// 		printf("node: %s,%d\n", node->data, node->type);
// 	args = ms_visit(node->left, args, envp);
// 	args = ms_visit(node->right, args, envp);
// 	if (node->type == A_PARAM)
// 		args = ms_add_arg_back_cmd(args, node->data);
// 	else if (node->type == A_CMD)
// 	{
// 		args = ms_add_arg_front_cmd(args, node->data);
// 		if (!args)
// 			return (NULL);
// 		if (args->type != 0)
// 			rediction_execut(args, envp);
// 		ms_free_arg_array_re(args->cmds);
// 		args = ms_init_arg_array_re();
// 	}
// 	else if (node->type == A_FILE || node->type == A_LIMITER)
// 	{
// 		args = ms_add_arg(args, node->data);
// 	}
// 	else if (node->type == 5 || node->type == 6 || 
// 				node->type == 8 || node->type == 9)
// 	{
// 		args->type = node->type;
// 	}
// 	return (args);
// }

// int	ms_exec_command(t_node *ast, char **envp)
// {
// 	t_cmds	*args;

// 	args = ms_init_arg_array_re();
// 	args = ms_visit(ast, args, envp);
// 	printf("OUT\n");
// 	// if (!args)
// 	// {
// 	// 	ms_free_arg_array_re(args);
// 	// 	return (ERROR);
// 	// }
// 	// ms_free_arg_array_re(args);
// 	return (EXIT_SUCCESS);
// }
