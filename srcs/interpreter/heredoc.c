/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:08:54 by twagner           #+#    #+#             */
/*   Updated: 2022/01/17 19:14:25 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

static char	*ms_tmp_filename(int num)
{
	char	*tmp;
	char	*name;

	name = ft_itoa(num);
	if (name)
	{
		tmp = name;
		name = ft_strjoin("tmp/hd_", name);
		free(tmp);
		if (name)
			return (name);
	}
	return (NULL);
}

static int	ms_save_heredoc(t_node *node, int ret, int *heredoc_fds, int *num)
{
	int			fd;
	char		*file_name;
	char		*file_content;

	if (ret != 0)
		return (ret);
	file_name = ms_tmp_filename(++(*num));
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd > 0)
	{
		if (node->data)
		{
			if (*num == 0)
				file_content = ms_get_next_heredoc(node->data, 1);
			else
				file_content = ms_get_next_heredoc(node->data, 0);
			if (file_content && !ms_param_expansion(&file_content, node->qt_rm)
				&& ms_write_hd(fd, &file_content, ft_strlen(file_content)) >= 0
				&& !ms_reopen_heredoc_fds(fd, file_name, heredoc_fds, *num))
				return (0);
		}
	}
	free(file_name);
	return (ERROR);
}

static int	ms_visit_heredoc(t_node *node, int ret, int *heredoc_fds, int *num)
{
	if (!node || ret == ERROR)
		return (ret);
	if (node->type == A_LIMITER)
		ret = ms_save_heredoc(node, ret, heredoc_fds, num);
	ret = ms_visit_heredoc(node->left, ret, heredoc_fds, num);
	ret = ms_visit_heredoc(node->right, ret, heredoc_fds, num);
	return (ret);
}

int	ms_clear_heredoc(int *heredoc_fds, int ret)
{
	int	i;

	if (heredoc_fds)
	{
		i = -1;
		while (heredoc_fds[++i] > 0)
			close(heredoc_fds[i]);
		free(heredoc_fds);
	}
	return (ret);
}

int	*ms_do_heredoc(t_node *tree, int nb, int *interrupt)
{
	int	*heredoc_fds;
	int	num;

	num = -1;
	heredoc_fds = (int *)malloc(sizeof(*heredoc_fds) * (nb + 1));
	if (heredoc_fds)
	{
		heredoc_fds[nb] = dup(STDIN_FILENO);
		if (!ms_visit_heredoc(tree, 0, heredoc_fds, &num))
			return (heredoc_fds);
	}
	*interrupt = 1;
	return (heredoc_fds);
}
