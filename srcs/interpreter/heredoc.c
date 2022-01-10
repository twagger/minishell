/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:08:54 by twagner           #+#    #+#             */
/*   Updated: 2022/01/10 14:37:51 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

static void ms_tmp_filename(char **name, int num)
{
	
}

static int	ms_save_heredoc(char *limiter, int ret)
{
	static int	num = 1;
	int			fd;
	char		filename[4];

	if (ret != 0)
		return (ret);
	// create a new file
	ms_tmp_filename((char **)&filename, num);
	fd = open((char *)filename, O_RDWR | O_CREAT, 0666);
	// read on fd 0 until delim > Store in a char *
	// when delim, write in the file fd and close it
	// num ++
	return (0);
}

static int	ms_visit_heredoc(t_node *node, int ret)
{
	if (!node)
		return (ret);
	if (node->type == A_LIMITER)
		ret = ms_save_heredoc(node->data, ret);
	ret = ms_visit_heredoc(node->left, ret);
	ret = ms_visit_heredoc(node->right, ret);
	return (ret);
}

int	ms_do_heredoc(t_node *tree, int nb)
{
	if (!ms_visit_heredoc(tree, 0))
		return (0);
	return (ERROR);
}