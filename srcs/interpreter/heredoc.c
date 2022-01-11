/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:08:54 by twagner           #+#    #+#             */
/*   Updated: 2022/01/11 08:17:39 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

static char *ms_tmp_filename(int num)
{
	char	*tmp;
	char	*name;

	name = ft_itoa(num);
	if (name)
	{
		tmp = name;
		name = ft_strjoin("hd_", name);
		free(tmp);
		if (name)
			return (name);
	}
	return (NULL);
}

static int	ms_save_heredoc(char *limiter, int ret, int *heredoc_fds)
{
	static int	num = -1;
	int			fd;
	char		*file_name;
	char		*file_content;

	if (ret != 0)
		return (ret);
	file_name = ms_tmp_filename(num);
	fd = open(file_name, O_RDWR | O_CREAT, 0666);
	free(file_name);
	if (fd > 0)
	{
		heredoc_fds[++num] = fd;
		limiter = ms_quote_removal(limiter);
		if (limiter)
		{
			file_content = ms_get_next_heredoc(limiter);
			if (file_content)
			{
				write(fd, file_content, ft_strlen(file_content));
				return (0);
			}
		}
	}
	return (ERROR);
}

static int	ms_visit_heredoc(t_node *node, int ret, int *heredoc_fds)
{
	if (!node || ret == ERROR)
		return (ret);
	if (node->type == A_LIMITER)
		ret = ms_save_heredoc(node->data, ret, heredoc_fds);
	ret = ms_visit_heredoc(node->left, ret, heredoc_fds);
	ret = ms_visit_heredoc(node->right, ret, heredoc_fds);
	return (ret);
}

int	ms_clear_heredoc(int *heredoc_fds, int ret)
{
	int	i;

	i = -1;
	while (heredoc_fds[++i] > 0)
		close(heredoc_fds[i]);
	free(heredoc_fds);
	return (ret);
}

int	*ms_do_heredoc(t_node *tree, int nb)
{
	int	*heredoc_fds;

	heredoc_fds = (int *)malloc(sizeof(*heredoc_fds) * (nb + 1));
	if (heredoc_fds)
	{
		heredoc_fds[nb] = -1;
		if (!ms_visit_heredoc(tree, 0, heredoc_fds))
			return (heredoc_fds);
	}
	free(heredoc_fds);	
	return (NULL);
}