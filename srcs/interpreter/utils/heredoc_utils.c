/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 09:16:08 by twagner           #+#    #+#             */
/*   Updated: 2022/01/11 16:14:11 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

/*
** CREATE LIMITER
** Create two strings : limiter\n and \nlimiter\n for search
*/

char	*ms_create_limiter_to_search(char *limiter, int type)
{
	int		len;
	char	*result;

	len = ft_strlen(limiter) + type;
	result = (char *)malloc(sizeof(*result) * (len + 1));
	if (result)
	{
		if (type == 1)
		{
			ft_strcpy(result, limiter);
			result[len - 1] = '\n';
			result[len] = '\0';
		}
		else if (type == 2)
		{
			result[0] = '\n';
			ft_strcpy(result + 1, limiter);
			result[len - 1] = '\n';
			result[len] = '\0';
		}
		return (result);
	}
	return (NULL);
}

/*
** SEARCH LIMITER
** Search limiter\n at the beginning of the buffer or \nlimiter\n inside.
** Returns a pointer to the first char of the limiter or NULL.
*/

char	*ms_search_limiter(char *buffer, char *limiter)
{
	char	*limiter_start;
	char	*limiter_in;
	char	*p_limiter;

	limiter_start = ms_create_limiter_to_search(limiter, 1);
	limiter_in = ms_create_limiter_to_search(limiter, 2);
	p_limiter = ft_strnstr(buffer, limiter_start, ft_strlen(buffer));
	if (p_limiter != buffer)
	{
		p_limiter = ft_strnstr(buffer, limiter_in, ft_strlen(buffer));
		if (p_limiter)
		{
			free(limiter_start);
			free(limiter_in);
			return (p_limiter);
		}
		else
			return (NULL);
	}
	free(limiter_start);
	free(limiter_in);
	return (p_limiter);
}

/*
** CREATE HEREDOC
** Get content from keep_buffer and returns it.
** Update the buffer with what has been read after the limiter.
*/

char	*ms_create_heredoc(char **buffer, char *p_limiter)
{
	int		l_limiter;
	char	*result;
	char	*tmp;

	l_limiter = 0;
	if (p_limiter == NULL)
		p_limiter = ft_strchr(*buffer, 0);
	else
		l_limiter = (ft_strchr(p_limiter, '\n') - p_limiter) + 1;
	if (p_limiter[0] == '\n')
		l_limiter = (ft_strchr(p_limiter + 1, '\n') - p_limiter) + 2;
	if (*buffer)
	{
		result = ft_substr(*buffer, 0, (p_limiter - *buffer) + 1);
		if (result)
		{
			tmp = *buffer;
			*buffer = ft_substr(*buffer, (p_limiter + l_limiter) - *buffer, \
				ft_strchr(*buffer, 0) - (p_limiter + l_limiter));
			free(tmp);
			return (result);
		}
	}
	free(*buffer);
	return (NULL);
}

/*
** GET NEXT HEREDOC
** Search the fd 0 for a limiter then return what has been entered before.
*/

char	*ms_init_keep_buffer(void)
{
	char	*keep_buffer;

	keep_buffer = (char *)malloc(sizeof(*keep_buffer));
	if (!keep_buffer)
		return (NULL);
	keep_buffer[0] = 0;
	return (keep_buffer);
}

char	*ms_get_next_heredoc(char *limiter, int tofree)
{
	static char	*keep_buffer = NULL;
	char		*p_limiter;
	char		*tmp;
	char		buffer[BUFFER_SIZE + 1];
	int			ret;

	if (tofree)
	{
		free(keep_buffer);
		keep_buffer = NULL;
	}
	if (!keep_buffer)
	{
		keep_buffer = ms_init_keep_buffer();
		if (!keep_buffer)
			return (NULL);
	}
	p_limiter = ms_search_limiter(keep_buffer, limiter);
	if (!p_limiter)
	{
		ret = read(0, buffer, BUFFER_SIZE);
		while (ret >= 0)
		{
			buffer[ret] = 0;
			tmp = keep_buffer;
			keep_buffer = ft_strjoin(keep_buffer, buffer);
			free(tmp);
			p_limiter = ms_search_limiter(keep_buffer, limiter);
			if (p_limiter || ret == 0)
				return (ms_create_heredoc(&keep_buffer, p_limiter));
			ret = read(0, buffer, BUFFER_SIZE + 1);
		}
		if (ret == ERROR)
		{
			free(keep_buffer);
			keep_buffer = NULL;
		}
	}
	else
		return (ms_create_heredoc(&keep_buffer, p_limiter));
	return (NULL);
}
