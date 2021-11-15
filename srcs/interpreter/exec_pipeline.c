/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:55:34 by twagner           #+#    #+#             */
/*   Updated: 2021/11/12 18:15:47 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "parser.h"

typedef struct s_cmds
{
	char **cmds;
	int	i;
}	t_cmds;

int g_index;

static int	ms_args_len_2(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (i);
}

t_cmds	*ms_init_arg_array_2(void)
{
	t_cmds	*cmds;
	char	**array;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	array = (char **)malloc(sizeof(*array));
	if (!array)
		return (NULL);
	*array = NULL;
	cmds->cmds = array;
	return (cmds);
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

void print_arg(char **argv)
{
	int i = 0;

	while(argv[i])
	{
		printf("%s\n", argv[i]);
		i++;
	}
}
void pipe_execte(int *pipex, t_cmds *args, int nb_pipe, char **envp)
{
	int		i;
	char	*path;
	//if not last cmds
	printf("inside:%d\n", args->i);
    if (args->i !=nb_pipe)
	{
        if (dup2(pipex[2 * args->i + 1], STDOUT_FILENO) < 0)
		{
			perror("dup a");
			exit(1);
		}
    }
	//if not first cmd
	if (args->i != 0)
	{
        if (dup2(pipex[2 * (args->i-1)], STDIN_FILENO) < 0)
		{
			perror("dup b");
			exit(1);
		}
    }
	i = -1;
    while(++i < nb_pipe * 2)	
		close(pipex[i]);
	printf("getpath:%s\n", args->cmds[0]);
	path = get_path(args->cmds[0], envp);
    if (!path)
	{
		perror("path");
		exit(1);
	}
	if (execve(path, args->cmds, envp) == -1)
	{
		perror("execve");
		exit(1);
	}

}
t_cmds *ms_add_arg_back_2(t_cmds *args, char *data)
{
	int		i;
	int		ac;
	char	**new;

	if (!args)
		return (NULL);
	ac = ms_args_len_2(args->cmds);
	printf("len:%d\n", ac);
	new = (char **)malloc(sizeof(*new) * (ac + 2));
	if (!new)
	{
		ms_free_arg_array(args->cmds);
		return (NULL);
	}
	new[ac + 1] = NULL;
	i = -1;
	while (args->cmds[++i])
		new[i] = ft_strdup(args->cmds[i]);
	new[i] = ft_strdup(data);
	printf("data:%s\n", data);
	printf("new:, %d, %s\n",i, new[i]);
	ms_free_arg_array(args->cmds);
	args->cmds = new;
	return (args);
}

t_cmds *ms_add_arg_front_2(t_cmds *args, char *cmd)
{
	int		i;
	int		ac;
	char	**new;

	if (!args)
		return (NULL);
	ac = ms_args_len_2(args->cmds);
	new = (char **)malloc(sizeof(*new) * (ac + 2));
	if (!new)
	{
		ms_free_arg_array(args->cmds);
		return (NULL);
	}
	new[ac + 1] = NULL;
	new[0] = ft_strdup(cmd);
	i = -1;
	while (args->cmds[++i])
		new[i + 1] = ft_strdup(args->cmds[i]);
	ms_free_arg_array(args->cmds);
	args->cmds = new;
	return (args);
}

static t_cmds *ms_visit(t_node *node, t_cmds *args, char **envp, int *pipex, int nb_pipe)
{
	//static int	index = 0;
	pid_t		child;
	int			i;

	if (!node)
		return (args);
	printf("begin:%d\n", args->i);
	args = ms_visit(node->left, args, envp, pipex, nb_pipe);
	args = ms_visit(node->right, args, envp, pipex ,nb_pipe);
	if (node->type == A_PARAM)
	{
		args = ms_add_arg_back_2(args, node->data);
	}
	else if (node->type == A_CMD)
	{	
		args = ms_add_arg_front_2(args, node->data);
		printf("args :%s, index:%d\n", args->cmds[0], args->i);
		// if (args->cmds)
		// 	printf("cmds:%s\n", args->cmds[0]);
		if (!args)
			return (NULL);
		child = fork();
		if (child < 0)
		{
			perror("fork");
			exit(1);
		}
		if (child == 0)
		{
			printf("childe\n");
			printf("index:%d\n", args->i);
			printf("----\n");
			print_arg(args->cmds);
			printf("----\n");
			pipe_execte(pipex, args, nb_pipe, envp);
		}
		//parent
		args = ms_init_arg_array_2();
		args->i = (args->i) + 1;
		i = -1;
		while(++i < nb_pipe * 2)
			close(pipex[i]);
		while (errno != ECHILD)
			wait(NULL);
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
	t_cmds	*args;
	int		*pipex;

	//g_index = 0;
	printf("np_pipe:%d\n", nb_pipe);
	pipex = pipex_creat(nb_pipe);
	printf("first\n");
	args = ms_init_arg_array_2();
	printf("secodne\n");
	args->i = 0;
	printf("outside :%d\n",args->i );
	args = ms_visit(node, args, envp, pipex, nb_pipe);
	// if (!args)
	// {
	// 	ms_free_arg_array(args);
	// 	return (ERROR);
	// }
	// ms_free_arg_array(args);
	return (EXIT_SUCCESS);
}
