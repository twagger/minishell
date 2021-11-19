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
	int				times;
}					t_cmd;

// void print_args(char ***argv, int nb)
// {
// 	int x = -1;
// 	int y;

// 	printf("RESULT: %d\n", nb);
// 	while (++x <= nb)
// 	{
// 		y = -1;
// 		while(argv[x][++y])
// 		{
// 			printf("%s\n", argv[x][y]);
// 		}
// 		printf("\n");
// 	}
// 	printf("----------------\n");
// }

static int	ms_args_len_2(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (i);
}

static t_cmd	*ms_init_arg_array_2(int nb_pipe)
{
	t_cmd	*args;
	char	***array;
	int		i;
	char	**arr;
	
	args = malloc(sizeof(t_cmd));
	if (!args)
		return (NULL);
	array = (char ***)malloc(sizeof(**array) * (2 * nb_pipe + 2));
	if (!array)
		return (NULL);
	i = -1;
	while(++i < 2 * nb_pipe + 2)
		array[i] = NULL;
	arr = (char **)malloc(sizeof(*arr));
	if (!array)
		return (NULL);
	*arr = 0;
	args->cmds = array;
	args->index = 0;
	args->times = 0;
	*array = arr;
	return (args);
}

static void	free_path(char **paths)
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

static char	*get_path(char *cmd, char **envp)
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
static void pipe_execte(int *pipex, t_cmd *args, int nb_pipe, char **envp)
{
	int		i;
	char	*path;
	fprintf(stderr, "**BULL:%d, %s\n", args->index, args->cmds[args->index][0]);
	//if not last cmds
    if (args->times != nb_pipe)
	{
		fprintf(stderr,"not last one : %d\n", args->times);
        if (dup2(pipex[2 * (args->times) + 1], STDOUT_FILENO) < 0)
		{
			perror("dup a");
			exit(1);
		}
    }
	//if not first cmd
	if (args->times != 0)
	{
		fprintf(stderr,"not first one : %d\n", args->times);
        if (dup2(pipex[2 * (args->times - 1)], STDIN_FILENO) < 0)
		{
			perror("dup b");
			exit(1);
		}
    }
	i = -1;
	while(++i < nb_pipe * 2)	
		close(pipex[i]);
	fprintf(stderr, "BULL:%d, %s\n", args->index, args->cmds[args->index][0]);
	if (ms_is_builtin(args->cmds[args->index][0]))
		ms_execute_builtin(args->cmds[args->index], envp);
	else
	{
		fprintf(stderr, "INSDIE\n");
		path = get_path(args->cmds[args->index][0], envp);
		//path and cmd not free?
    	if (!path)
		{
			//free_path(cmd);
			perror("no path:");
		}
		if (execve(path, args->cmds[args->index], envp) == -1)
		{
		//free(path);
		//free_path(cmd);
			perror("execve:");
		}
	}
}
static void pipe_fork(int *pipex, t_cmd *args, int nb_pipe, char **envp)
{
	//int		index;
	pid_t	child;
	int		i;

	//if not last cmds
	args->index = 0;
	args->times = -1;
	while(args->index < 2 *nb_pipe + 1)
	{
		if (ft_strncmp(args->cmds[args->index][0], "|", 2))
			args->times = args->times + 1;
		if (ft_strncmp(args->cmds[args->index][0], "|", 2) == 0)
		{
			//printf("pipp\n");
			args->index= args->index + 1;
			continue ;
		}
		child = fork();
		if (child < 0)
		{
			perror("fork:");
			exit(1);
		}
		if (child == 0)
		{
			printf("args->times:%d, args->index:%d\n", args->times, args->index);
			pipe_execte(pipex, args, nb_pipe, envp);
		}
		args->index =  args->index + 1;
		//free
	}
	i = -1;
    while(++i < nb_pipe * 2)	
		close(pipex[i]);
	free(pipex);
	//free();
	while (errno != ECHILD)
		wait(NULL);
}

static t_cmd	*ms_add_arg_back_2(t_cmd *args, char *data)
{
	int		i;
	int 	len2;
	char	**new;

	if (!args)
		return (NULL);
	if (args->times == 0)
		len2 = 0;
	else
		len2 = ms_args_len_2(args->cmds[args->index]);
	//printf("len2 in back :%d, %d\n", args->times, len2);
	new = (char **)malloc(sizeof(*new) * (len2 + 2));
	if (!new)
	{
		//ms_free_arg_array(args);
		return (NULL);
	}
	i = -1;
	while (args->cmds[args->index] != NULL && args->cmds[args->index][++i])
	{
		new[i] = ft_strdup(args->cmds[args->index][i]);
	}
	if (i == -1)
		i = 0;
	new[i] = ft_strdup(data);
	new[i + 1] = NULL;
	args->cmds[args->index] = new;
	args->times = args->times + 1;
	//ms_free_arg_array(args);
	return (args);
}

static t_cmd *ms_add_arg_front_2(t_cmd *args, char *data)
{
	int		i;
	int 	len2;
	char	**new;

	if (!args)
		return (NULL);
	if (args->times == 0)
		len2 = 0;
	else
		len2 = ms_args_len_2(args->cmds[args->index]);
	args->times = 0;
	new = (char **)malloc(sizeof(*new) * (len2 + 2));
	if (!new)
	{
		//ms_free_arg_array_2(args);
		return (NULL);
	}
	new[0] = ft_strdup(data);
	i = -1;
	while (args->cmds[args->index] != NULL && args->cmds[args->index][++i])
	{
		new[i + 1] = ft_strdup(args->cmds[args->index][i]);
	}
	if (i == -1)
		i = 0;
	new[i + 1] = NULL;
	//ms_free_arg_array(args);
	args->cmds[args->index] = new;
	new[len2 + 1] = NULL;
	args->index = args->index + 1;
	// printf("good front\n");
	// if (args->index == 2)
	// 	printf("seconde:%s\n", args->cmds[args->index-1][1]);
	return (args);
}

static t_cmd *ms_visit(t_node *node, t_cmd *args, char **envp, int *pipex, int nb_pipe)
{
	if (!node)
		return (args);
	printf("node: %s,%d\n", node->data, node->type);
	args = ms_visit(node->left, args, envp, pipex, nb_pipe);
	args = ms_visit(node->right, args, envp, pipex ,nb_pipe);
	if (node->type == A_PIPE)
	{
		//printf("HELLOOOOO\n");
		args = ms_add_arg_back_2(args, node->data);
		//print_args(args->cmds, args->index);
		args->times = 0;
		args->index = args->index + 1;
		//printf("index:%d, %d\n", args->index, nb_pipe);
		if (args->index == (2 * nb_pipe + 1))
		{
			//printf("run!\n");
			pipe_fork(pipex, args, nb_pipe, envp);
		}
	}
	if (node->type == A_PARAM)
	{
		//printf("param\n");
		args = ms_add_arg_back_2(args, node->data);
		//printf("index:%d\n", args->index);
	}
	else if (node->type == A_CMD)
	{	
		args = ms_add_arg_front_2(args, node->data);
		//print_args(args->cmds, args->index-1);
	}
	return (args);
}

static int		*pipex_creat(int nb_pipe)
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
	t_cmd	*args;
	int		*pipex;

	(void)node;
	(void)envp;
	pipex = pipex_creat(nb_pipe);
	args = ms_init_arg_array_2(nb_pipe);
	args = ms_visit(node, args, envp, pipex, nb_pipe);
	// if (!args)
	// {
	// 	ms_free_arg_array(args);
	// 	return (ERROR);
	// }
	// ms_free_arg_array(args);
	return (EXIT_SUCCESS);
}
