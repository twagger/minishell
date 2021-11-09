/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:31 by twagner           #+#    #+#             */
/*   Updated: 2021/11/09 16:49:12 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env 	*next;
}		t_env;

static t_env *g_my_envp = 0;
/*
** Check if the param is like this : name=[value]
** I don't handle yet '+=' operator
** param in the cmds
*/
int	if_str_in_str(char *a, char *b)
{
	int x1;
	int	x2;

	x1 = 0;
	x2 = 0;
	if (!a || !b)
		return (1);
	while(a[x1] && b[x2])
	{
		if (a[x1] == b[x2])
		{
			while(b[x2] && a[x1 + x2])
			{
				if(b[x2] != a[x1 + x2])
					return (1);
				x2++;
			}
			return (0);
		}
		x1++;
	}
	return (1);
}

static int	ms_is_param_ok(char	*param)
{
	if (strlen(param) < 2)
		return (0);
	if (!ft_strchr(param, '='))
		return (0);
	//printf("ft_strncmp:%s, %d\n", ft_strncmp(param, "+=", 2));
	if	(!if_str_in_str(param, "+="))
	{
		while (*param)
		{
			if (*param == '+')
				break ;
			if (!ft_isalnum(*param) && *param != '_')
				return (0);
			++param;
		}
	}
	else
	{
		while (*param)
		{
			if (*param == '=')
				break ;
			if (!ft_isalnum(*param) && *param != '_')
				return (0);
			++param;
		}
	}
	return (1);
}

/*
** Check if the param already exists in envp
*/

static int	ms_is_param_new(char *param, t_env *envp)
{
	size_t	pos_equal;

	if (ft_strchr(param, '+'))
		pos_equal = ft_strchr(param, '+') - param;
	else
		pos_equal = ft_strchr(param, '=') - param;
	while (envp)
	{
		if (ft_strncmp(param, envp->name, ft_strlen(envp->name)) == 0)
		{
			if (pos_equal != ft_strlen(envp->name))
				return (1);
			return (0);
		}
		envp = envp->next;
	}
	return (1);
}

/*
** Count the number of new params to add to the current envp
*/
int	total_params(t_env *envp)
{
	int total;

	total = 0;
	while (envp)
	{
		total++;
		envp = envp->next;
	}
	return (total);
}

// static int	ms_nb_new_params(char *cmd, t_env *envp)
// {
// 	int i;
// 	int	res;
// 	int total;

// 	res = 0;
// 	i = 0;
// 	total = total_params(envp);
// 	while (++i < total)
// 	{
// 		if (ms_is_param_ok(cmd) && ms_is_param_new(cmd, envp))
// 			++res;
// 	}
// 	return (res);
// }

/*
** This function clean a malloc'ed envp in case one malloc fails
*/

// static	void	ms_clean_envp(t_env *envp)
// {
// 	while (envp)
// 	{
// 		free(envp->name);
// 		free(envp->content);
// 		envp =  envp->next;
// 	}
// }

void	ft_envadd(t_env **lst, t_env *new)
{
	t_env	*current;

	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	current = (*lst);
	while (current->next != 0)
	{
		current = current->next;
	}
	current->next = new;
}

t_env	*ft_envnew(char *envp)
{
	t_env		*re;
	char		**sep;

	re = (t_env *)malloc(sizeof(t_env));
	if (!re)
		return (0);
	sep = ft_split(envp, '=');
	if (!sep)
		return (0);
	re->name = sep[0];
	re->content = sep[1];
	re->next = 0;
	return (re);
}

void	printf_out(t_env *list)
{
	while(list)
	{
		printf("Export : \n");
		printf("%s=%s\n", list->name, list->content);
		list = list->next;
	}
}

t_env *init_env(char **envp)
{
	t_env	*new;
	t_env	*list;

	list = NULL;
	while (*envp)
	{
		new = ft_envnew(*envp);
		if(!new)
			return (0);
		ft_envadd(&list, new);
		envp++;
	}
	return (list);
}

/*
** Malloc a new envp list of strings with every new exported param in it
*/

// int	ms_export(int ac, char **av, char **envp)
// {
// 	int		i;
// 	int		nb_total;
// 	char	**new_env;

// 	if (ac == 1)
// 	{
// 		ms_env(ac, av, envp);
// 		return (1);
// 	}
// 	nb_total = 0;
// 	while (envp[nb_total])
// 		++nb_total;
// 	nb_total += ms_nb_new_params(ac, av, envp);
// 	new_env = (char **)malloc(sizeof(*new_env) * (nb_total + 1));
// 	if (!new_env)
// 		return (ERROR);
// 	i = -1;
// 	while (*envp)
// 	{
// 		new_env[++i] = ft_strdup(*envp);
// 		if (!new_env[i])
// 		{
// 			ms_clean_envp(new_env, i);
// 			if (prm->malloced_env)
// 				ms_clean_envp(envp, -1);
// 			return (ERROR);
// 		}
// 		++envp;
// 	}
// 	while (++i < nb_total)
// 	{
// 		if (ms_is_param_ok(av[i]) && ms_is_param_new(av[i], envp))
// 		{
// 			new_env[i] = ft_strdup(av[i]);
// 			if (!new_env[i])
// 			{
// 				ms_clean_envp(new_env, i);
// 				if (prm->malloced_env)
// 					ms_clean_envp(envp, -1);
// 				return (ERROR);
// 			}
// 		}
// 	}
// 	if (prm->malloced_env)
// 		ms_clean_envp(envp, -1);
// 	prm->malloced_env = 1;
// 	*envp = *new_env;
// 	printf("Test\n");
// 	return (0);
// }
int	add_newenvp(char *cmd, t_env **envp)
{
	t_env *new;

	new = ft_envnew(cmd);
	if (!new)
		return (1);
	ft_envadd(envp, new);
	return (0);
}

char	*ft_strduplen(char *s, size_t len)
{
	size_t	i;
	char	*arr;

	arr = (char *)malloc((len + 1) * sizeof(char));
	if (!arr)
		return (0);
	i = 0;
	while (i < len)
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

int	realloc_var_2(char *cmd, t_env **envp)
{
	char		*content;

	if (ft_strchr(cmd, '+'))
	{
		content = ft_strjoin((*envp)->content, ft_strchr(cmd, '=')+1);
		if (!content)
			return (1);
		free((*envp)->content);
		(*envp)->content = content;
	}
	else
	{
		content = ft_strdup(ft_strchr(cmd, '='));
		if (!content)
			return (1);
		free((*envp)->content);
		(*envp)->content = content;
	}
	return (0);
}

int	realloc_var(char *cmd, t_env *envp)
{
	size_t	len;
	char *name;

	len = 0;
	len = ft_strchr(cmd, '+') - cmd;
	if (!len)
		len = ft_strchr(cmd, '=') - cmd;
	name = ft_strduplen(cmd, len);
	if (!name)
		return (1);
	while (envp)
	{
		if (ft_strncmp(name, envp->name, len) == 0)
			realloc_var_2(cmd, &envp);
		envp = envp->next;
	}
	return (0);
}

int	ms_export(int ac, char **av, char **envp)
{
	char **cmd;
	int		i;

	(void)ac;
	g_my_envp = init_env(envp);
	if (g_my_envp == NULL)
		exit(1);
	cmd = ft_split(av[1], ' ');
	if (!cmd[1])
	{
		printf_out(g_my_envp);
		exit(0);
	}
	i = 0;
	while(cmd[++i])
	{
		if (!ms_is_param_ok(cmd[i]))
		{
			//free now?
			printf("not a valid identifier\n");
			continue ;
			//exit(1);
		}
		if (ms_is_param_new(cmd[i], g_my_envp))
		{
			if (add_newenvp(cmd[i], &g_my_envp))
			{
				printf("Error happened while exporting var\n");
				continue ;
			}
		}
		else
		{
			if (realloc_var(cmd[i], g_my_envp))
			{
				printf("Error happened while realloc var\n");
				continue ;
			}
		}

	}
	printf_out(g_my_envp);
	return (0);
}