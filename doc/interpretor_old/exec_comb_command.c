/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_comb_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:03:09 by wlo               #+#    #+#             */
/*   Updated: 2021/11/26 20:22:58 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "parser.h"

typedef struct s_red
{
	int				type;
	char			*file;
	struct s_red	*next;
}	t_red;

typedef struct s_cmds
{
	char			**cmds;
	struct s_red	*rediction;
	struct s_cmds	*next;
}	t_cmds;

void printf_out_cmd(t_cmds *args)
{
	t_cmds *new;
	t_red	*hello;

	new = args;
	int i;
	printf("cmd:\n");
	while(new)
	{
		
		i = 0;
		while (new->cmds&& new->cmds[i])
		{
			printf("|%s| ", new->cmds[i]);
			i++;
		}
		printf("\n");
		hello = new->rediction;
		while(hello)
		{
			printf("red->type:%d\n", hello->type);
			printf("red->file:%s\n", hello->file);
			hello = hello->next;
		}
		printf("next\n");
		new = new->next;
	}
}

// static void	free_path(char **paths)
// {
// 	int	i;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		free(paths[i]);
// 		i++;
// 	}
// 	free(paths);
// }

// static char	*get_path(char *cmd, char **envp)
// {
// 	char	**paths;
// 	char	*path;
// 	int		i;
// 	char	*part_path;

// 	i = 0;
// 	while (ft_strnstr(envp[i], "PATH", 4) == 0)
// 		i++;
// 	paths = ft_split(envp[i] + 5, ':');
// 	i = 0;
// 	while (paths[i])
// 	{
// 		part_path = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(part_path, cmd);
// 		free(part_path);
// 		if (access(path, F_OK) == 0)
// 		{
// 			free_path(paths);
// 			return (path);
// 		}
// 		free(path);
// 		i++;
// 	}
// 	if (paths)
// 		free_path(paths);
// 	return (0);
// }

static int	ms_args_len(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		++i;
	return (i);
}

static t_cmds	*ms_init_arg_com(t_cmds	*head)
{
	t_cmds	*args;
	t_red	*red;
	t_cmds	*temp;
	
	temp = head;
	while(temp)
		temp = temp->next;
	red = (t_red *)malloc(sizeof(*red));
	if (!red)
		return (NULL);
	red->type = 0;
	red->file = NULL;
	red->next = NULL;
	args = (t_cmds *)malloc(sizeof(*args));
	if (!args)
		return (NULL);
	args->cmds = NULL;
	args->next = NULL;
	args->rediction = red;
	if (!head)
		head = args;
	temp = args;
	return (head);
}

static t_cmds *ms_add_red_type(t_cmds *args, int type)
{
	t_red 	*red;
	t_red	*temp;
	t_cmds 	*replace;

	replace = args;
	red = (t_red *)malloc(sizeof(*red));
	if (!red)
		return (NULL);
	red->type = 0;
	red->file = NULL;
	red->next = NULL;
	while (replace->next)
		replace = replace->next;
	if (!replace->rediction->type)
	{
		replace->rediction->type = type;
		replace->rediction->next = red;
		return (args);
	}
	temp = replace->rediction;
	while (temp->type)
		temp = temp->next;
	temp->next = red;
	return (args);
}

static t_cmds *ms_add_red_arg(t_cmds *args, char *file)
{
	char	*new;
	t_red	*temp;
	t_cmds 	*replace;

	replace = args;
	new = ft_strdup(file);
	while (replace->next)
		replace = replace->next;
	temp = replace->rediction;
	while (temp->next)
		temp = temp->next;
	temp->file = new;
	return (args);
}

t_cmds	*ms_add_arg_com(t_cmds *args, char *data)
{
	int		i;
	int		ac;
	char	**new;
	t_cmds 	*head;

	head = args;
	while(args->next)
		args = args->next;
	ac = ms_args_len(args->cmds);
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
	//ms_free_arg_array(args->cmds);
	args->cmds = new;
	return (head);
}

t_cmds	*ms_add_cmd_com(t_cmds *args, char *data)
{
	char	**new;
	t_cmds 	*head;

	new = (char **)malloc(sizeof(*new) * 2);
	if (!new)
	{
		ms_free_arg_array(args->cmds);
		return (NULL);
	}
	new[1] = NULL;
	new[0] = ft_strdup(data);
	head = args;
	while(args->next)
		args = args->next;
	args->cmds = new;
	return (head);
}

// static void	read_line(int fd, char *keyword)
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

// static void rediction_execut(t_red *args)
// {
// 	int		file;
// 	int		copy;

// 	file = 0;
// 	fprintf(stderr,"redirection: %s, %d\n", args->file, args->type);
// 	if (args->type == A_RED_FROM)
// 	{
// 		fprintf(stderr,"A_RED_FROM\n");
// 		copy = dup(STDIN_FILENO);
// 		file = open(args->file, O_RDONLY);
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
// 		file = open(args->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
// 		file = open(args->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
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
// 		read_line(file, args->file);
// 		close(file);
// 		file = open(".temp", O_RDONLY);
// 		if (dup2(file, STDIN_FILENO) < 0)
// 		{
// 			perror("dup2 in open:");
// 			exit(1);
// 		}
// 	}
// 	//return (t_file){file, copy};
// 	// if (args->type == A_DGREAT ||  args->type == A_RED_TO)
// 	// {
// 	// 	dup2(copy, 1);
// 	// }
// 	// else if (args->type == A_RED_FROM || args->type == A_DLESS)
// 	// {
// 	// 	dup2(copy, 0);
// 	// }
// 	// if (file)
// 	// 	close(file);
// 	// if (!access(".temp", F_OK))
//     //     unlink(".temp");
// }

// static void pipe_execte(int *pipex, t_cmds *args, int index, char **envp, int nb_pipe)
// {
// 	int		i;
// 	char	*path;
// 	//fprintf(stderr, "**BULL:%d, %s\n", args->index, args->cmds[args->index][0]);
// 	//if not last cmds
//     if (index != nb_pipe)
// 	{
// 		//fprintf(stderr,"not last one : %d\n", args->nd_cmd);
//         if (dup2(pipex[2 * index + 1], STDOUT_FILENO) < 0)
// 		{
// 			perror("dup a");
// 			exit(1);
// 		}
//     }
// 	//if not first cmd
// 	if (index != 0)
// 	{
// 		//fprintf(stderr,"not first one : %d\n", args->nd_cmd);
//         if (dup2(pipex[2 * (index - 1)], STDIN_FILENO) < 0)
// 		{
// 			perror("dup b");
// 			exit(1);
// 		}
//     }
// 	while (args->rediction)
// 	{
// 		rediction_execut(args->rediction);
// 		args->rediction = args->rediction->next;
// 	}
// 	i = -1;
// 	while(++i < nb_pipe * 2)	
// 		close(pipex[i]);
// 	if (ms_is_builtin(args->cmds[0]))
// 		ms_execute_builtin(args->cmds, envp);
// 	else
// 	{
// 		path = get_path(args->cmds[0], envp);
// 		//path and cmd not free?
//     	if (!path)
// 		{
// 		//free_path(cmd);
// 			perror("no path:");
// 		}
// 		if (execve(path, args->cmds, envp) == -1)
// 		{
// 		//free(path);
// 		//free_path(cmd);
// 			perror("execve:");
// 	    }
//     }
// }

// static void pipe_fork(int *pipex, t_cmds *args, char **envp, int nb_pipe)
// {
// 	pid_t	child;
// 	int		index;
// 	int		i;

// 	//if not last cmds
// 	index = 0;
// 	while(args)
// 	{
// 		child = fork();
// 		if (child < 0)
// 		{
// 			perror("fork:");
// 			exit(1);
// 		}
// 		if (child == 0)
// 		{
// 			fprintf(stderr,"child :%d\n", index);
// 			pipe_execte(pipex, args, index, envp, nb_pipe);
// 		}
// 		args = args->next;
// 		index++;
// 		//free
// 	}
// 	printf("readu out?\n");
// 	i = -1;
//     while(++i < nb_pipe * 2)	
// 		close(pipex[i]);
// 	free(pipex);
// 	//free();
// 	while (errno != ECHILD)
// 		wait(NULL);
// 	printf("ready out?\n");
// }

static t_cmds *ms_visit(t_node *node, t_cmds *args, char **envp)
{
	if (!node)
		return (args);
	args = ms_visit(node->left, args, envp);
	args = ms_visit(node->right, args, envp);
	printf("NODE:|%s|, |%d|\n", (char *)node->data, node->type);
	if (node->type == A_PIPE)
	{
		args = ms_init_arg_com(args);
	}
	else if (node->type == A_PARAM)
	{
		args = ms_add_arg_com(args, node->data);
	}
	else if (node->type == A_CMD)
	{	
		args = ms_add_cmd_com(args, node->data);
	}
    else if (node->type == A_FILE || node->type == A_LIMITER)
	{
		args = ms_add_red_arg(args, node->data);
	}
	else if (node->type == A_RED_TO || node->type == A_RED_FROM || 
				node->type == A_DLESS || node->type == A_DGREAT)
	{
		args = ms_add_red_type(args, node->type);
	}
	return (args);
}

// static int		*pipex_creat(int nb_pipe)
// {
// 	int		*pipex;
// 	int		i;

// 	pipex = malloc(nb_pipe * 2 * sizeof(int));
// 	if (!pipex)
// 	{
// 		perror("pipe");
// 		exit(1);
// 	}
// 	i = -1;
// 	while(++i < nb_pipe)
// 	{
// 		if (pipe(&pipex[2 * i]) < 0)
// 		{
// 			perror("pipe");
// 			exit(1);
// 		}
// 	}
// 	return pipex;
// }

int	ms_exec_comb_command(t_node *node, char **envp, int nb_pipe)
{
	t_cmds	*args;
    //int		*pipex;

	args = NULL;
	(void)nb_pipe;
	//pipex = pipex_creat(nb_pipe);
	args = ms_init_arg_com(args);
	if (!args)
	{
		perror("initial arg : ");
		exit(1);
	}
	args = ms_visit(node, args, envp);
	printf("out\n");
	printf_out_cmd(args);
	//pipe_fork(pipex, args, envp , nb_pipe);
	// if (!args)
	// {
	// 	ms_free_arg_array_re(args);
	// 	return (ERROR);
	// }
	// ms_free_arg_array_re(args);
	return (EXIT_SUCCESS);
}



