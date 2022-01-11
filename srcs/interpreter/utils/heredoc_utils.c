/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 09:16:08 by twagner           #+#    #+#             */
/*   Updated: 2022/01/09 12:14:40 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

/*
** CLEAR GET NEXT HEREDOC
** Free the temporary allocations
*/

void	ms_clear_gnh(char *limiter_start, char *limiter_in, int ret)
{
	free(limiter_start);
	free(limiter_in);
	return (ret);
}

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
			ms_clear_gnh(limiter_start, limiter_in, 0);
			return (p_limiter);
		}
		else
			return (NULL);
	}
	ms_clear_gnh(limiter_start, limiter_in, 0);
	return (p_limiter);
}

/*
** CREATE HEREDOC
** Get content from keep_buffer and/or current buffer and returns it.
** Update the keep_buffer with what has been read after the limiter.
*/

char	*ms_create_heredoc(char **keep_buffer, char **buffer, char *p_limiter)
{
	int		l_limiter;
	char	*result;
	char	*buf;
	char	*tmp;

	l_limiter = (ft_strchr(p_limiter, '\n') - p_limiter) + 1;
	if (p_limiter[0] == '\n')
		l_limiter = (ft_strchr(p_limiter + 1, '\n') - p_limiter) + 2;
	buf = *keep_buffer;
	if (buffer && *keep_buffer)
		buf = ft_strjoin(keep_buffer, buffer);
	else if (buffer)
		buf = buffer;
	if (buf)
	{
		result = ft_substr(buf, 0, p_limiter - buf);
		if (result)
		{
			// mise à jour du keep buffer
			tmp = *keep_buffer;
			*keep_buffer = ft_substr(buf, )
			// free (buffer)
			return (result);
		}
	}
	free(*keep_buffer);
	free(buffer);
	return (NULL);
}

/*
** GET NEXT HEREDOC
** Search the fd 0 for a limiter then return what has been entered before.
*/

char	*ms_get_next_heredoc(char *limiter)
{
	static char	*keep_buffer = NULL;
	char		*p_limiter;
	char		*result;
	char		*tmp;

	// 0 - Regarder si la chaine \nlimiter\n ou <debut>limiter\n existe dans le keep_buffer
	p_limiter = ms_search_limiter(keep_buffer, limiter);
	if (!p_limiter)
	{
		// 0.2 - Sinon : Etape 1

		// 1 - Lire un certain nombre de caractères sur le fd 0

		// 2 - Regarder, si dans ce que j'ai lu, j'ai :
		//		- <début>limiter\n
		//		- \nlimiter\n

		// 3 - Si j'ai pas : etape 1

		// 4 - Si j'ai : etape 5
	}
	else
		return (ms_create_heredoc(&keep_buffer, NULL, p_limiter));
}
