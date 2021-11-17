/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:55:34 by twagner           #+#    #+#             */
/*   Updated: 2021/11/16 15:05:42 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "parser.h"

typedef struct s_cmd
{
	char			***cmds;
	int				index;
}					t_cmd;

void print_args(char ***argv)
{
	int x = -1;
	int y = -1;

	printf("RESULT:\n");
	while (argv[++x])
	{
		while(argv[x][++y])
		{
			printf("%s\n", argv[x][y]);
		}
		printf("\n");
	}
	printf("----------------\n");
}

static int	ms_cmd_len_2(char ***args)
{
	int	i;

	i = 0;
	// printf("11111\n");
	if (!args)
		return (0);
	// printf("2222222x\n");
	while (args[i])
		++i;
	return (i);
}

static int	ms_args_len_2(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (i);
}

char	***ms_init_arg_array_2(void)
{
	char	***array;
	//char	**arr;
	
	array = (char ***)malloc(sizeof(**array));
	if (!array)
		return (NULL);
	*array = NULL;
	// arr = (char **)malloc(sizeof(*arr));
	// if (!arr)
	// 	return (NULL);
	// // *array = arr;
	// *arr = NULL;
	// *array = arr;
	// arr[nb_pipe + 1] =  NULL;
	// (*arr) = NULL;
	return (array);
}

void	free_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free_path(paths);
			return (path);
		}
		free(path);
		i++;
	}
	if (paths)
		free_path(paths);
	return (0);
}

void print_arg(char ***argv, int nb_cmd)
{
	int i = 0;
	int nb = 0;

	while (nb < nb_cmd)
	{
		while(argv[nb][i])
		{
			printf("%s\n", argv[nb][i]);
			i++;
		}
		printf("\\\\\\n");
		nb++;
	}
}

// void pipe_execte(int *pipex, t_cmds *args, int nb_pipe, char **envp)
// {
// 	int		i;
// 	char	*path;
// 	//if not last cmds
// 	printf("inside:%d\n", args->i);
//     if (args->i !=nb_pipe)
// 	{
//         if (dup2(pipex[2 * args->i + 1], STDOUT_FILENO) < 0)
// 		{
// 			perror("dup a");
// 			exit(1);
// 		}
//     }
// 	//if not first cmd
// 	if (args->i != 0)
// 	{
//         if (dup2(pipex[2 * (args->i-1)], STDIN_FILENO) < 0)
// 		{
// 			perror("dup b");
// 			exit(1);
// 		}
//     }
// 	i = -1;
//     while(++i < nb_pipe * 2)	
// 		close(pipex[i]);
// 	printf("getpath:%s\n", args->cmds[0]);
// 	path = get_path(args->cmds[0], envp);
//     if (!path)
// 	{
// 		perror("path");
// 		exit(1);
// 	}
// 	if (execve(path, args->cmds, envp) == -1)
// 	{
// 		perror("execve");
// 		exit(1);
// 	}

// }
char	***ms_add_arg_back_2(char ***args, char *data)
{
	int		i;
	int		len1;
	int 	len2;
	char	***cmd;
	char	**new;

	if (!args)
		return (NULL);
	len1 = ms_cmd_len_2(args);
	printf("len in back :%d\n", len1);
	cmd = (char ***)malloc(sizeof(**cmd) * (len1 + 2));
	if (!cmd)
	{
		//ms_free_arg_array(args);
		return (NULL);
	}
	cmd[len1 + 1] = NULL;
	if (len1 == 0)
		len2 = 0;
	else
		len2 = ms_args_len_2(args[len1 - 1]);
	printf("len2 in back :%d\n", len2);
	new = (char **)malloc(sizeof(*new) * (len2 + 2));
	if (!new)
	{
		//ms_free_arg_array(args);
		return (NULL);
	}
	i = -1;
	printf("so far so good\n");
	while (args[++i])
	{
		printf("inside\n");
		new[i] = ft_strdup(args[len1][i]);
	}
	new[i] = ft_strdup(data);
	cmd[len1] = new;
	new[i + 1] = NULL;
	printf("good!!\n");
	printf("new len :%d\n", ms_args_len_2(cmd[len1]));
	//ms_free_arg_array(args);
	return (cmd);
}

char	***ms_add_arg_front_2(char ***args, char *data)
{
	int		i;
	int		len1;
	int 	len2;
	char	***cmd;
	char	**new;

	if (!args)
		return (NULL);
	len1 = ms_cmd_len_2(args);
	printf("len in front :%d\n", len1);
	cmd = (char ***)malloc(sizeof(**cmd) * (len1 + 2));
	if (!cmd)
	{
		//ms_free_arg_array(args);
		return (NULL);
	}
	cmd[len1 + 1] = NULL;
	if (len1 == 0)
		len2 = 0;
	else
		len2 = ms_args_len_2(args[len1 - 1]);
	printf("len2 in front :%d\n", len2);
	new = (char **)malloc(sizeof(*new) * (len2 + 1));
	if (!new)
	{
		//ms_free_arg_array_2(args);
		return (NULL);
	}
	new[len2 + 1] = NULL;
	new[0] = ft_strdup(data);
	i = -1;
	while (args[++i])
		new[i + 1] = ft_strdup(args[len1][i]);
	//ms_free_arg_array(args);
	printf("good front\n");
	return (cmd);
}

static char ***ms_visit(t_node *node, char ***args, char **envp, int *pipex, int nb_pipe)
{
	// pid_t		child;
	// int			i;

	if (!node)
		return (args);
	printf("here:%s\n", node->data);
	args = ms_visit(node->left, args, envp, pipex, nb_pipe);
	args = ms_visit(node->right, args, envp, pipex ,nb_pipe);
	if (node->type == A_PIPE)
	{
		printf("HELLOOOOO\n");
		// if last pipe > launch pipex
		// if not > Connect cmd 1 output to cmd 2 input
	}
	if (node->type == A_PARAM)
	{
		args = ms_add_arg_back_2(args, node->data);
		printf("param\n");
		print_args(args);
	}
	else if (node->type == A_CMD)
	{	
		args = ms_add_arg_front_2(args, node->data);
		printf("cmd\n");
		print_args(args);
		// Save the args tab in an array
		// if (args->cmds)
		// 	printf("cmds:%s\n", args->cmds[0]);
		// if (!args)
		// 	return (NULL);
		// child = fork();
		// if (child < 0)
		// {
		// 	perror("fork");
		// 	exit(1);
		// }
		// if (child == 0)
		// {
		// 	printf("childe\n");
		// 	printf("----\n");
		// 	printf("----\n");
		// 	//pipe_execte(pipex, args, nb_pipe, envp);
		// }
		// //parent
		// //args = ms_init_arg_array_2();
		// //args->i = (args->i) + 1;
		// i = -1;
		// while(++i < nb_pipe * 2)
		// 	close(pipex[i]);
		// while (errno != ECHILD)
		// 	wait(NULL);
	}
	return (args);
}

int		*pipex_creat(int nb_pipe)
{
	int		*pipex;
	int		i;

	pipex = malloc(nb_pipe * 2 * sizeof(int));
	if (!pipex)
	{
		perror("pipe");
		exit(1);
	}
	i = -1;
	while(++i < nb_pipe)
	{
		if (pipe(&pipex[2 * i]) < 0)
		{
			perror("pipe");
			exit(1);
		}
	}
	return pipex;
}


int	ms_exec_pipeline(t_node *node, char **envp, int nb_pipe)
{
	char	***args;
	int		*pipex;
	char	***ex;
	char 	**content;

	(void)node;
	(void)envp;
	pipex = pipex_creat(nb_pipe);
	args = ms_init_arg_array_2();
	printf("secodne\n");
	args = ms_visit(node, args, envp, pipex, nb_pipe);
	print_args(args);
	ex = (char ***)malloc(sizeof(**ex)*2);
	if (!ex)
		return 1;
	ex[1]=NULL;
	content = (char **)malloc(sizeof(*content) * 3);
	if (!content)
		return 1;
	content[2]=NULL;
	content[0] = ft_strdup("HELLO");
	content[1] = ft_strdup("YOU!!!");
	ex[0] = content;
	print_args(ex);
	// if (!args)
	// {
	// 	ms_free_arg_array(args);
	// 	return (ERROR);
	// }
	// ms_free_arg_array(args);
	return (EXIT_SUCCESS);
}
