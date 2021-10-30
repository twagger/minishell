/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:53:25 by twagner           #+#    #+#             */
/*   Updated: 2021/10/30 14:37:07 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lr_parser.h"

static int	ms_free_line_args(char *line, char **args, int code)
{
	if (line)
		free(line);
	if (args)
	{
		while (*args)
		{
			free(*args);
			++args;
		}
	}
	return (code);
}

static t_trans	*ms_new_transition(char **args)
{
	t_trans	*new;

	if (!args)
		return (NULL);
	new = (t_trans *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->state = ft_atoi(args[0]);
	new->event = ft_atoi(args[1]);
	new->action = ft_atoi(args[2]);
	new->next = ft_atoi(args[3]);
	new->nb_reduce = ft_atoi(args[4]);
	return (new);
}

void	ms_free_table(t_trans **trans)
{
	if (trans)
	{
		while (*trans)
		{
			free(*trans);
			++trans;
		}
	}
}

int	ms_create_all_transitions(int fd, t_trans **trans)
{
	int		i;
	int		ret;
	char	*line;
	char	**args;

	line = NULL;
	ret = ft_get_next_line(fd, &line, 0);
	i = -1;
	while (ret >= 0)
	{
		args = ft_split(line, 9);
		trans[++i] = ms_new_transition(args);
		if (!trans[i])
			ms_free_line_args(line, args, ERROR);
		ms_free_line_args(line, args, 0);
		line = NULL;
		if (ret == 0)
			break ;
		ret = ft_get_next_line(fd, &line, 0);
	}
	if (ret == ERROR)
		return (ERROR);
	return (EXIT_SUCCESS);
}

t_trans	**ms_init_parsing_table(void)
{
	int		fd;
	t_trans	**trans;

	trans = (t_trans **)malloc(sizeof(*trans) * (NB_TRANS + 1));
	if (!trans)
		return (NULL);
	trans[0] = NULL;
	trans[NB_TRANS] = NULL;
	fd = open(AUTOMATON, O_RDONLY);
	if (fd == ERROR)
	{
		ms_free_table(trans);
		return (NULL);
	}
	if (ms_create_all_transitions(fd, trans) == ERROR)
	{
		ms_free_table(trans);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (trans);
}
