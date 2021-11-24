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

typedef struct s_red
{
	int				type;
	char			*file;
	struct s_red	*next;
}	t_red;

typedef struct s_cmds
{
	char			**cmds;
	t_red			*rediction;
	struct s_cmds	*next;
}	t_cmds;

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
	while (args[i])
		++i;
	return (i);
}

static t_cmds	*ms_init_arg_com()
{
	t_cmds	*args;
	
	args = (t_cmds *)malloc(sizeof(*args));
	if (!args)
		return (NULL);
	args->cmds = NULL;
	args->next = NULL;
	args->rediction = NULL;
	return (args);
}

static t_cmds *ms_add_red_type(t_cmds *args, int type)
{
	t_red 	*red;
	t_red	*red_head;
	t_cmds 	*head;

	head = args;
	printf("head   in type ---------------------- :%s\n", head->cmds[0]);
	red = malloc(sizeof(t_red));
	if (!red)
		return (NULL);
	red->type = type;
	red->file = NULL;
	red->next = NULL;
	while (args->next)
		args = args->next;
	if (!args->rediction)
	{
		args->rediction = red;
		return (head);
	}
	red_head = args->rediction;
	while (args->rediction)
		args->rediction = args->rediction->next;
	args->rediction = red;
	args->rediction = red_head;
	return (head);
}

static t_cmds *ms_add_red_arg(t_cmds *args, char *file)
{
	char	*new;
	t_cmds 	*head;
	t_red	*red_head;
	
	head = args;
	printf("head   in file ---------------------- :%s\n", head->cmds[0]);
	new = ft_strdup(file);
	while (args->next)
		args = args->next;
	red_head = args->rediction;
	while (args->rediction->file)
		args->rediction = args->rediction->next;
	args->rediction->file = new;
	args->rediction = red_head;
	return (head);
}

t_cmds	*ms_add_arg_com(t_cmds *args, char *data)
{
	int		i;
	int		ac;
	char	**new;
	t_cmds 	*head;

	head = args;
	printf("head   in arg ---------------------- :%s\n", head->cmds[0]);
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
	t_cmds	*new_cmd;


	new = (char **)malloc(sizeof(*new) * 2);
	if (!new)
	{
		ms_free_arg_array(args->cmds);
		return (NULL);
	}
	new[1] = NULL;
	new[0] = ft_strdup(data);
	new_cmd = (t_cmds *)malloc(sizeof(*new_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmds = new;
	new_cmd->rediction = NULL;
	new_cmd->next = NULL;
	if (!args->cmds)
	{
		printf("first time????\n");
		return (new_cmd);
	}
	head = args;
	while(args->next)
		args = args->next;
	args->next = new_cmd;
	return (head);
}

// static t_cmds	*ms_add_arg_back_2(t_cmds *args, char *data)
// {
// 	int		i;
// 	int 	len2;
// 	char	**new;

// 	if (!args)
// 		return (NULL);
// 	if (args->nd_cmd == 0)
// 		len2 = 0;
// 	else
// 		len2 = ms_args_len(args->cmds[args->index]);
// 	new = (char **)malloc(sizeof(*new) * (len2 + 2));
// 	if (!new)
// 	{
// 		//ms_free_arg_array(args);
// 		return (NULL);
// 	}
// 	i = -1;
// 	while (args->cmds[args->index] != NULL && args->cmds[args->index][++i])
// 	{
// 		new[i] = ft_strdup(args->cmds[args->index][i]);
// 	}
// 	if (i == -1)
// 		i = 0;
// 	new[i] = ft_strdup(data);
// 	new[i + 1] = NULL;
// 	args->cmds[args->index] = new;
// 	args->nd_cmd = args->nd_cmd + 1;
// 	//ms_free_arg_array(args);
// 	return (args);
// }

// static t_cmds *ms_add_arg_front_2(t_cmds *args, char *data)
// {
// 	int		i;
// 	int 	len2;
// 	char	**new;

// 	if (!args)
// 		return (NULL);
// 	if (args->nd_cmd == 0)
// 		len2 = 0;
// 	else
// 		len2 = ms_args_len(args->cmds[args->index]);
// 	args->nd_cmd = 0;
// 	new = (char **)malloc(sizeof(*new) * (len2 + 2));
// 	if (!new)
// 	{
// 		//ms_free_arg_array_2(args);
// 		return (NULL);
// 	}
// 	new[0] = ft_strdup(data);
// 	i = -1;
// 	while (args->cmds[args->index] != NULL && args->cmds[args->index][++i])
// 	{
// 		new[i + 1] = ft_strdup(args->cmds[args->index][i]);
// 	}
// 	if (i == -1)
// 		i = 0;
// 	new[i + 1] = NULL;
// 	args->cmds[args->index] = new;
// 	new[len2 + 1] = NULL;
// 	args->index = args->index + 1;
// 	return (args);
// }

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

// static void rediction_execut(t_cmds *args, char **envp)
// {
// 	int		file;
// 	int		copy;

// 	file = 0;
// 	fprintf(stderr,"exute%s, %s, %d\n", args->cmds[args->index][0], args->file, args->re_type);
// 	if (args->re_type == A_RED_FROM)
// 	{
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
// 	else if (args->re_type == A_RED_TO)
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
// 	else if (args->re_type == A_DGREAT)
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
// 	if (ms_is_builtin(args->cmds[args->index][0]))
// 		ms_execute_builtin(args->cmds[args->index], envp);
// 	else
// 	{
// 		ms_execute(args->cmds[args->index], envp);
// 		fprintf(stderr,"exute??\n");
// 	}
// 	if (args->re_type == A_DGREAT ||  args->re_type == A_RED_TO)
// 	{
// 		dup2(copy, 1);
// 	}
// 	else if (args->re_type == A_RED_FROM || args->re_type == A_DLESS)
// 	{
// 		dup2(copy, 0);
// 	}
// 	if (file)
// 		close(file);
// 	if (!access(".temp", F_OK))
//         unlink(".temp");
// }

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

// static void pipe_execte(int *pipex, t_cmds *args, int nb_pipe, char **envp)
// {
// 	int		i;
// 	char	*path;
// 	fprintf(stderr, "**BULL:%d, %s\n", args->index, args->cmds[args->index][0]);
// 	//if not last cmds
//     if (args->nd_cmd != nb_pipe)
// 	{
// 		//fprintf(stderr,"not last one : %d\n", args->nd_cmd);
//         if (dup2(pipex[2 * (args->nd_cmd) + 1], STDOUT_FILENO) < 0)
// 		{
// 			perror("dup a");
// 			exit(1);
// 		}
//     }
// 	//if not first cmd
// 	if (args->nd_cmd != 0)
// 	{
// 		//fprintf(stderr,"not first one : %d\n", args->nd_cmd);
//         if (dup2(pipex[2 * (args->nd_cmd - 1)], STDIN_FILENO) < 0)
// 		{
// 			perror("dup b");
// 			exit(1);
// 		}
//     }
// 	i = -1;
// 	while(++i < nb_pipe * 2)	
// 		close(pipex[i]);
//     if (args->re_type != 0 && args->re_one == args->nd_cmd)
// 			rediction_execut(args, envp);
// 	//fprintf(stderr, "BULL:%d, %s\n", args->index, args->cmds[args->index][0]);
// 	else 
//     {   
//         if (ms_is_builtin(args->cmds[args->index][0]))
// 		    ms_execute_builtin(args->cmds[args->index], envp);
// 	    else
// 	    {
// 		    path = get_path(args->cmds[args->index][0], envp);
// 		//path and cmd not free?
//     	    if (!path)
// 		    {
// 			//free_path(cmd);
// 			    perror("no path:");
// 		    }
// 		    if (execve(path, args->cmds[args->index], envp) == -1)
// 		    {
// 		    //free(path);
// 		    //free_path(cmd);
// 			    perror("execve:");
// 	    	}
//         }
// 	}
// }

// static void pipe_fork(int *pipex, t_cmds *args, int nb_pipe, char **envp)
// {
// 	//int		index;
// 	pid_t	child;
// 	int		i;

// 	//if not last cmds
// 	args->index = 0;
// 	args->nd_cmd = -1;
// 	while(args->index < 2 *nb_pipe + 1)
// 	{
// 		if (ft_strncmp(args->cmds[args->index][0], "|", 2))
// 			args->nd_cmd = args->nd_cmd + 1;
// 		if (ft_strncmp(args->cmds[args->index][0], "|", 2) == 0)
// 		{
// 			args->index= args->index + 1;
// 			continue ;
// 		}
// 		child = fork();
// 		if (child < 0)
// 		{
// 			perror("fork:");
// 			exit(1);
// 		}
// 		if (child == 0)
// 		{
// 			printf("args->times:%d, args->index:%d\n", args->nd_cmd, args->index);
// 			pipe_execte(pipex, args, nb_pipe, envp);
// 		}
// 		args->index =  args->index + 1;
// 		//free
// 	}
// 	i = -1;
//     while(++i < nb_pipe * 2)	
// 		close(pipex[i]);
// 	free(pipex);
// 	//free();
// 	while (errno != ECHILD)
// 		wait(NULL);
// }
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
		while (new->cmds[i])
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

static t_cmds *ms_visit(t_node *node, t_cmds *args, char **envp)
{
	if (!node)
		return (args);
	args = ms_visit(node->left, args, envp);
	args = ms_visit(node->right, args, envp);
	if (node->type == A_PARAM)
	{
		args = ms_add_arg_com(args, node->data);
		printf("PARAM\n");
		//printf_out_cmd(args);
	}
	else if (node->type == A_CMD)
	{	
		args = ms_add_cmd_com(args, node->data);
		printf("CMD\n");
		//printf_out_cmd(args);
	}
    else if (node->type == A_FILE || node->type == A_LIMITER)
	{
		printf("file\n");
		args = ms_add_red_arg(args, node->data);
	}
	else if (node->type == 1 || node->type == 2 || 
				node->type == 3 || node->type == 4)
	{
		printf("RED\n");
		args = ms_add_red_type(args, node->type);
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

int	ms_exec_comb_command(t_node *node, char **envp, int nb_pipe)
{
	t_cmds	*args;
    int		*pipex;
	// t_cmds	*try;
	// t_red	*red1;
	// t_red	*red2;
	// char 	**ph;

	args = NULL;
	pipex = pipex_creat(nb_pipe);
	args = ms_init_arg_com();
	// if (!args)
	// {
	// 	perror("initial arg : ");
	// 	exit(1);
	// }
	args = ms_visit(node, args, envp);
	printf("OUT\n");
	printf_out_cmd(args);
	printf_out_cmd(args);
	// printf("fake\n");
	// try = (t_cmds *)malloc(sizeof(*try));
	// ph = (char **)malloc(sizeof(*ph)*3);
	// ph[0] = "grep";
	// ph[1] = "a";
	// ph[2] = NULL;
	// try->cmds = ph;
	// red1 = (t_red *)malloc(sizeof(*red1));
	// red1->type = 100;
	// red1->file = "file1";
	// red2 = (t_red *)malloc(sizeof(*red2));
	// red2->type = 100;
	// red2->file = "file2";
	// red1->next = red2;
	// red2->next = NULL;
	// try->next = 0;
	// try->rediction = red1;
	// printf("check:%s,\n", try->rediction->file);
	// //printf_out_cmd(try);
	// printf("NOW\n");
	// printf("check:%s,\n", try->cmds[0]);
	// printf("check:%s,\n", try->rediction->file);
	// try = ms_add_cmd_com(try, "echo");
	// printf("check:%s,\n", try->rediction->file);
	// printf_out_cmd(try);
	// try = ms_add_arg_com(try, "x");
	// printf_out_cmd(try);
	// try = ms_add_red_type(try, 1000);
	// try = ms_add_red_arg(try, "file333");
	// printf("FINAL\n");
	// printf_out_cmd(try);



	// if (!args)
	// {
	// 	ms_free_arg_array_re(args);
	// 	return (ERROR);
	// }
	// ms_free_arg_array_re(args);
	return (EXIT_SUCCESS);
}



