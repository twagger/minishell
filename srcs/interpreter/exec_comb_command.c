/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_comb_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:03:09 by wlo               #+#    #+#             */
/*   Updated: 2021/11/19 17:03:13 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "parser.h"

typedef struct s_cmdss
{
	char			***cmds;
	int				index;
	int				nd_cmd;
    char			*file;
	int				re_type;
    int             re_one;

}	t_cmdss;

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

static int	ms_args_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (i);
}

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

static t_cmdss	*ms_init_arg_array_re(int nb_pipe)
{
	t_cmdss	*args;
	char	***array;
	int		i;
	char	**arr;
	
	args = malloc(sizeof(t_cmdss));
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
	*arr = NULL;
	args->cmds = array;
	args->index = 0;
	args->nd_cmd = 0;
    args->file = NULL;
    args->re_type = 0;
    args->re_one = 0;
	*array = arr;
	return (args);
}

static t_cmdss	*ms_add_arg_back_2(t_cmdss *args, char *data)
{
	int		i;
	int 	len2;
	char	**new;

	if (!args)
		return (NULL);
	if (args->nd_cmd == 0)
		len2 = 0;
	else
		len2 = ms_args_len(args->cmds[args->index]);
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
	args->nd_cmd = args->nd_cmd + 1;
	//ms_free_arg_array(args);
	return (args);
}

static t_cmdss *ms_add_arg_front_2(t_cmdss *args, char *data)
{
	int		i;
	int 	len2;
	char	**new;

	if (!args)
		return (NULL);
	if (args->nd_cmd == 0)
		len2 = 0;
	else
		len2 = ms_args_len(args->cmds[args->index]);
	args->nd_cmd = 0;
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
	args->cmds[args->index] = new;
	new[len2 + 1] = NULL;
	args->index = args->index + 1;
	return (args);
}

static t_cmdss *ms_add_arg(t_cmdss *args, char *data)
{
	char	*new;

	new = ft_strdup(data);
	args->file = new;
	return (args);
}

static void	read_line(int fd, char *keyword)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (line)
		{
			if (!ft_strcmp(line, keyword))
			{
				free(line);
				break ;
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		free(line);
	}
}

static void rediction_execut(t_cmdss *args, char **envp)
{
	int		file;
	int		copy;

	file = 0;
	fprintf(stderr,"exute%s, %s, %d\n", args->cmds[args->index][0], args->file, args->re_type);
	if (args->re_type == A_RED_FROM)
	{
		copy = dup(STDIN_FILENO);
		file = open(args->file, O_RDONLY);
		if (file < 0)
		{
			perror("open:");
			exit(1);
		}
		if (dup2(file, STDIN_FILENO) < 0)
		{
			perror("dup2 in open:");
			exit(1);
		}
	}
	else if (args->re_type == A_RED_TO)
	{
		copy = dup(STDOUT_FILENO);
		file = open(args->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (file < 0)
		{
			perror("open:");
			exit(1);
		}
		if (dup2(file, STDOUT_FILENO) < 0)
		{
			perror("dup2 in open:");
			exit(1);
		}
	}
	else if (args->re_type == A_DGREAT)
	{
		copy = dup(STDOUT_FILENO);
		file = open(args->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (file < 0)
		{
			perror("open:");
			exit(1);
		}
		if (dup2(file, STDOUT_FILENO) < 0)
		{
			perror("dup2 in open:");
			exit(1);
		}
	}
	else
	{
		fprintf(stderr,"here_doc\n");
		copy = dup(STDIN_FILENO);
		file = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (file < 0)
		{
			perror("open:");
			exit(1);
		}
		read_line(file, args->file);
		close(file);
		file = open(".temp", O_RDONLY);
		if (dup2(file, STDIN_FILENO) < 0)
		{
			perror("dup2 in open:");
			exit(1);
		}
	}
	if (ms_is_builtin(args->cmds[args->index][0]))
		ms_execute_builtin(args->cmds[args->index], envp);
	else
	{
		ms_execute(args->cmds[args->index], envp);
		fprintf(stderr,"exute??\n");
	}
	if (args->re_type == A_DGREAT ||  args->re_type == A_RED_TO)
	{
		dup2(copy, 1);
	}
	else if (args->re_type == A_RED_FROM || args->re_type == A_DLESS)
	{
		dup2(copy, 0);
	}
	if (file)
		close(file);
	if (!access(".temp", F_OK))
        unlink(".temp");
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

static void pipe_execte(int *pipex, t_cmdss *args, int nb_pipe, char **envp)
{
	int		i;
	char	*path;
	fprintf(stderr, "**BULL:%d, %s\n", args->index, args->cmds[args->index][0]);
	//if not last cmds
    if (args->nd_cmd != nb_pipe)
	{
		//fprintf(stderr,"not last one : %d\n", args->nd_cmd);
        if (dup2(pipex[2 * (args->nd_cmd) + 1], STDOUT_FILENO) < 0)
		{
			perror("dup a");
			exit(1);
		}
    }
	//if not first cmd
	if (args->nd_cmd != 0)
	{
		//fprintf(stderr,"not first one : %d\n", args->nd_cmd);
        if (dup2(pipex[2 * (args->nd_cmd - 1)], STDIN_FILENO) < 0)
		{
			perror("dup b");
			exit(1);
		}
    }
	i = -1;
	while(++i < nb_pipe * 2)	
		close(pipex[i]);
    if (args->re_type != 0 && args->re_one == args->nd_cmd)
			rediction_execut(args, envp);
	//fprintf(stderr, "BULL:%d, %s\n", args->index, args->cmds[args->index][0]);
	else 
    {   
        if (ms_is_builtin(args->cmds[args->index][0]))
		    ms_execute_builtin(args->cmds[args->index], envp);
	    else
	    {
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
}

static void pipe_fork(int *pipex, t_cmdss *args, int nb_pipe, char **envp)
{
	//int		index;
	pid_t	child;
	int		i;

	//if not last cmds
	args->index = 0;
	args->nd_cmd = -1;
	while(args->index < 2 *nb_pipe + 1)
	{
		if (ft_strncmp(args->cmds[args->index][0], "|", 2))
			args->nd_cmd = args->nd_cmd + 1;
		if (ft_strncmp(args->cmds[args->index][0], "|", 2) == 0)
		{
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
			printf("args->times:%d, args->index:%d\n", args->nd_cmd, args->index);
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

static t_cmdss *ms_visit(t_node *node, t_cmdss *args, char **envp, int *pipex, int nb_pipe)
{
	if (!node)
		return (args);
	if (node->type != -1)
		printf("node: %s,%d\n", node->data, node->type);
	args = ms_visit(node->left, args, envp, pipex, nb_pipe);
	args = ms_visit(node->right, args, envp, pipex ,nb_pipe);
	if (node->type == A_PIPE)
	{
		args = ms_add_arg_back_2(args, node->data);
		args->nd_cmd = 0;
		args->index = args->index + 1;
		if (args->index == (2 * nb_pipe + 1))
		{
            if (args-> re_type != 0)
			    rediction_execut(args, envp);
			pipe_fork(pipex, args, nb_pipe, envp);
            //ms_free_arg_array_re(args->cmds);
		}
	}
	if (node->type == A_PARAM)
	{
		args = ms_add_arg_back_2(args, node->data);
	}
	else if (node->type == A_CMD)
	{	
        if (args->re_type != 0)
            args->re_one = args->nd_cmd;
		args = ms_add_arg_front_2(args, node->data);
	}
    else if (node->type == A_FILE || node->type == A_LIMITER)
	{
        //redirection only 1?
		args = ms_add_arg(args, node->data);
	}
	else if (node->type == 5 || node->type == 6 || 
				node->type == 8 || node->type == 9)
	{
		args->re_type = node->type;
	}
	return (args);
}

int	ms_exec_comb_command(t_node *node, char **envp, int nb_pipe)
{
	t_cmdss	*args;
    int		*pipex;

	pipex = pipex_creat(nb_pipe);
	args = ms_init_arg_array_re(nb_pipe);
	args = ms_visit(node, args, envp, pipex, nb_pipe);
	printf("OUT\n");
	// if (!args)
	// {
	// 	ms_free_arg_array_re(args);
	// 	return (ERROR);
	// }
	// ms_free_arg_array_re(args);
	return (EXIT_SUCCESS);
}



