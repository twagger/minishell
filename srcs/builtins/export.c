/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:31 by twagner           #+#    #+#             */
/*   Updated: 2021/10/19 11:02:49 by twagner          ###   ########.fr       */
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

/*
** Check if the param is like this : name=[value]
** I don't handle yet '+=' operator
*/

static int	ms_is_param_ok(char	*param)
{
	if (strlen(param) < 2)
		return (0);
	if (!ft_strchr(param, '='))
		return (0);
	while (*param)
	{
		if (*param == '=')
			break ;
		if (!ft_isalnum(*param) && *param != '_')
			return (0);
		++param;
	}
	return (1);
}

/*
** Check if the param already exists in envp
*/

static int	ms_is_param_new(char *param, char **envp)
{
	int	pos_equal;

	pos_equal = param - ft_strchr(param, '=');
	while (*envp)
	{
		if (ft_strncmp(param, *envp, pos_equal + 1) == 0)
			return (0);
		++envp;
	}
	return (1);
}

/*
** Count the number of new params to add to the current envp
*/

static int	ms_nb_new_params(int ac, char **av, char **envp)
{
	int i;
	int	res;

	res = 0;
	i = 0;
	while (++i < ac)
	{
		if (ms_is_param_ok(av[i]) && ms_is_param_new(av[i], envp))
			++res;
	}
	return (res);
}

/*
** This function clean a malloc'ed envp in case one malloc fails
*/

static	void	ms_clean_envp(char **envp, int ec)
{
	int i;

	if (ec >= 0)
	{
		i = -1;
		while (++i < ec)
			free(envp[i]);
	}
	else if (ec == -1)
	{
		while (*envp)
		{
			free(*envp);
			++envp;
		}
	}
	free(envp);
}

/*
** Malloc a new envp list of strings with every new exported param in it
*/

int	ms_export(int ac, char **av, char **envp)
{
	int		i;
	int		nb_total;
	char	**new_env;

	if (ac == 1)
	{
		ms_env(ac, av, envp);
		return (1);
	}
	nb_total = 0;
	while (envp[nb_total])
		++nb_total;
	nb_total += ms_nb_new_params(ac, av, envp);
	new_env = (char **)malloc(sizeof(*new_env) * (nb_total + 1));
	if (!new_env)
		return (ERROR);
	i = -1;
	while (*envp)
	{
		new_env[++i] = ft_strdup(*envp);
		if (!new_env[i])
		{
			ms_clean_envp(new_env, i);
			if (prm->malloced_env)
				ms_clean_envp(envp, -1);
			return (ERROR);
		}
		++envp;
	}
	while (++i < nb_total)
	{
		if (ms_is_param_ok(av[i]) && ms_is_param_new(av[i], envp))
		{
			new_env[i] = ft_strdup(av[i]);
			if (!new_env[i])
			{
				ms_clean_envp(new_env, i);
				if (prm->malloced_env)
					ms_clean_envp(envp, -1);
				return (ERROR);
			}
		}
	}
	if (prm->malloced_env)
		ms_clean_envp(envp, -1);
	prm->malloced_env = 1;
	*envp = *new_env;
	printf("Test\n");
	return (0);
}

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

int main(int ac, char **av, char **envp)
{
	t_env *my_envp;
	char **cmd;

	my_envp = init_env(envp);
	cmd = ft_split(av[1], ' ');
	if (!cmd[1])
	{
		printf_out(my_envp);
		exit(0);
	}
	else 
	{
		
	}
	printf("There :%s, %s\n", cmd[0], cmd[1]);


	//printf_out(my_envp);
	// while (*envp)
	// {
	// 	printf("|%s|\n", *envp);
	// 	envp++;
	// }
	



	return (0);
}