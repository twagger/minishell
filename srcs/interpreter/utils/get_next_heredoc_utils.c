/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_heredoc_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:46:19 by twagner           #+#    #+#             */
/*   Updated: 2022/01/14 16:49:09 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

int	ms_gnh_keep_buffer_management(int tofree, char **keep_buffer)
{
	if (tofree)
	{
		free(*keep_buffer);
		*keep_buffer = NULL;
	}
	if (!*keep_buffer)
	{
		*keep_buffer = ms_init_keep_buffer();
		if (!*keep_buffer)
			return (ERROR);
	}
	return (0);
}

char	*ms_join_and_check_bufs(char **keep_buffer, char *buffer, char *limiter)
{
	char	*tmp;

	tmp = *keep_buffer;
	*keep_buffer = ft_strjoin(*keep_buffer, buffer);
	free(tmp);
	return (ms_search_limiter(*keep_buffer, limiter));
}

void	ms_reinit_keep_buffer(char **keep_buffer)
{
	free(*keep_buffer);
	*keep_buffer = NULL;
}

int	ms_write_hd(int fd, char *file_content, int len)
{
	int	ret;

	ret = write(fd, file_content, len);
	free(file_content);
	return (ret);
}

int	ms_dollar_expansion(char **str)
{
	int		i;
	char	*limiters;

	i = -1;
	limiters = "\"'\n\0";
	while ((*str)[++i])
	{
		if ((*str)[i] == '$')
		{
			// search until next " or ' or \n or \0
			// ms_get_env sur le mot resultant
				// si null > enlever le $MOT de la chaine
				// si pas null > replacer le $MOT dans la chaine
		}
	}
	return (0);
}
