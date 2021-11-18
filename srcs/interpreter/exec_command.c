/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:55:22 by twagner           #+#    #+#             */
/*   Updated: 2021/11/12 14:52:53 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "parser.h"

typedef struct s_cmds
{
	char			**cmds;
	char			*redi;
	int				type;
}	t_cmds;

static int	ms_args_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (i);
}

static void	ms_free_arg_array_re(char **args)
{
	if (args)
	{
		while (*args)
		{
			free(*args);
			++args;
		}
	}
}

t_cmds	*ms_init_arg_array_re(void)
{

	t_cmds	*args;
	char	**array;
	char	*redi;

	args = malloc(sizeof(t_cmds));
	if (!args)
		return (NULL);
	array = (char **)malloc(sizeof(*array));
	if (!array)
		return (NULL);
	*array = NULL;
	redi = NULL;
	args->cmds = array;
	args->redi = redi;
	args->type = 0;
	return (args);
}

int	check_get_next_line(char *content, char *keyword)
{
	int	len;

	len = 0;
	while (content[len] && content[len] != '\n')
		len++;
	if (ft_strncmp(content, keyword, (int)ft_strlen(keyword)))
	{
		content = content + len + 1;
		if (*content)
		{
			if (check_get_next_line(content, keyword) == 1)
				return 1;
			return (0);
		}
		else
			return (0);
	}
	else
		return (1);
}

char	*ft_strjoin_gnl(char **s1, char *s2)
{
	char	*arr;
	size_t	i;
	size_t	j;

	if (!(*s1) || !s2)
		return (0);
	arr = (char *)malloc((ft_strlen(*s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!arr)
		return (0);
	i = 0;
	while ((*s1)[i])
	{
		arr[i] = (*s1)[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		arr[i + j] = s2[j];
		j++;
	}
	arr[i + j] = '\0';
	free(*s1);
	(*s1) = NULL;
	return (arr);
}

int	get_next_line(char **content, char *keyword)
{
	char	buffer[2];
	int		ret;
	char	*newkeyword;

	ret = 1;
	if (!keyword)
	{
		printf("no KEYWORD\n");
		exit(1);
	}
	newkeyword = ft_strjoin(keyword, "\n");
	while (ret > 0)
	{
		ret = read(0, buffer, 1);
		buffer[1] = '\0';
		if (ret < 0 )
			break ;
		else if (ret == 0)
			return (0);
		if ((*content) == 0)
		{
			(*content) = malloc(sizeof(char) * 2);
			if (!(*content))
				return (-1);
			(*content)[0] = buffer[0];
			(*content)[1] = '\0';
		}
		else
			(*content) = ft_strjoin_gnl(content, buffer);
		if (buffer[0] == '\n')
		{
			if (check_get_next_line(*content, newkeyword) == 1)
			{
				free(newkeyword);
				return (0);			
			}
		}
	}
	return (-1);
}

// static int	ms_command_launcher(char **args, char **envp)
// {
// 	(void)envp;
// 	if (ms_getbin_path(&args[0]) == ERROR)
// 		return (ERROR);
// 	if (execve(args[0], args, NULL) == ERROR)
// 		perror("Minishell");
// 	return (EXIT_SUCCESS);
// }

// int	ms_execute(char **args, char **envp)
// {
// 	pid_t	pid;
// 	pid_t	wpid;
// 	int		status;

// 	pid = fork();
// 	if (pid == ERROR)
// 	{
// 		perror("Minishell");
// 		return (0);
// 	}
// 	if (pid == 0)
// 	{
// 		if (ms_command_launcher(args, envp) == ERROR)
// 			return (EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		wpid = waitpid(pid, &status, 0);
// 		if (wpid == ERROR)
// 		{
// 			perror("Minishell");
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	return (EXIT_SUCCESS);
// }

t_cmds *ms_add_arg_back_cmd(t_cmds *args, char *data)
{
	int		i;
	int		ac;
	char	**new;

	if (!args)
		return (NULL);
	ac = ms_args_len(args->cmds);
	new = (char **)malloc(sizeof(*new) * (ac + 2));
	if (!new)
	{
		ms_free_arg_array_re(args->cmds);
		return (NULL);
	}
	new[ac + 1] = NULL;
	i = -1;
	while (args->cmds[++i])
		new[i] = ft_strdup(args->cmds[i]);
	new[i] = ft_strdup(data);
	ms_free_arg_array_re(args->cmds);
	args->cmds = new;
	return (args);
}

t_cmds *ms_add_arg_front_cmd(t_cmds *args, char *cmd)
{
	int		i;
	int		ac;
	char	**new;

	if (!args)
		return (NULL);
	ac = ms_args_len(args->cmds);
	new = (char **)malloc(sizeof(*new) * (ac + 2));
	if (!new)
	{
		ms_free_arg_array_re(args->cmds);
		return (NULL);
	}
	new[ac + 1] = NULL;
	new[0] = ft_strdup(cmd);
	i = -1;
	while (args->cmds[++i])
		new[i + 1] = ft_strdup(args->cmds[i]);
	ms_free_arg_array_re(args->cmds);
	args->cmds = new;
	return (args);
}

t_cmds *ms_add_arg(t_cmds *args, char *data)
{
	char	*new;

	new = ft_strdup(data);
	args->redi = new;
	return (args);
}

void rediction_execut(t_cmds *args)
{
	int		file;
	static char	*content = NULL;

	if (args->type == A_RED_FROM)
	{
		file = open(args->redi, O_RDONLY);
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
		close(file);
	}
	else if (args->type == A_RED_TO)
	{
		file = open(args->redi, O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
		close(file);
	}
	else if (args->type == A_DGREAT)
	{
		file = open(args->redi, O_WRONLY | O_CREAT | O_APPEND, 0777);
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
		close(file);
	}
	else
	{
		file = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (file < 0)
		{
			perror("open:");
			exit(1);
		}
		if (get_next_line(&content, args->redi) < 0)
		{
			close(file);
			if (*content)
				free(content);
			perror("gnl");
			exit(1);
		}
		write(0, content, ft_strlen(content) - ft_strlen(args->redi) - 1);
		write(file, content, ft_strlen(content) - ft_strlen(args->redi) - 1);
		close(file);
		if (*content)
			free(content);
		if (!access(".temp", F_OK))
        	unlink(".temp");
	}
}
static t_cmds *ms_visit(t_node *node, t_cmds *args, char **envp)
{
	if (!node)
		return (args);
	//printf("node be:%s,%d\n", node->data, node->type);
	args = ms_visit(node->left, args, envp);
	args = ms_visit(node->right, args, envp);
	//printf("node:%s\n", node->data);
	if (node->type == A_PARAM)
		args = ms_add_arg_back_cmd(args, node->data);
	else if (node->type == A_CMD)
	{
		args = ms_add_arg_front_cmd(args, node->data);
		printf("cmd:%s\n", args->cmds[0]);
		printf("redi:%s\n", args->redi);
		if (!args)
			return (NULL);
		if (args->type != 0)
			rediction_execut(args);
		if (ms_is_builtin(args->cmds[0]))
			ms_execute_builtin(args->cmds, envp);
		else
			ms_execute(args->cmds, envp);
		ms_free_arg_array_re(args->cmds);
		args = ms_init_arg_array_re();
	}
	else if (node->type == A_FILE || node->type == A_LIMITER)
	{
		args = ms_add_arg(args, node->data);
		printf("args:%s\n", args->redi);
	}
	else if (node->type == 5 || node->type == 6 || 
				node->type == 8 || node->type == 9)
	{
		args->type = node->type;
	}
	printf("node:%s\n", node->data);
	return (args);
}

int	ms_exec_command(t_node *ast, char **envp)
{
	t_cmds	*args;

	args = ms_init_arg_array_re();
	args = ms_visit(ast, args, envp);
	printf("OUT\n");
	// if (!args)
	// {
	// 	ms_free_arg_array_re(args);
	// 	return (ERROR);
	// }
	// ms_free_arg_array_re(args);
	return (EXIT_SUCCESS);
}
