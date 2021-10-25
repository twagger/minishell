/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:57:26 by twagner           #+#    #+#             */
/*   Updated: 2021/10/25 16:30:04 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int			i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] == '\0' || s2[i] == '\0')
		return (s1[i] - s2[i]);
	return (0);
}

t_token_types	catego_toketype(char *content)
{
	if (!ft_strcmp(content, "|"))
		return (PIPE);
	else if (!ft_strcmp(content, "&&"))
		return (AND_IF);
	else if (!ft_strcmp(content, "||"))
		return (OR_IF);
	else if (!ft_strcmp(content, "<<"))
		return (DLESS);
	else if (!ft_strcmp(content, ">>"))
		return (DGREAT);
	else if (!ft_strcmp(content, ">"))
		return (RED_TO);
	else if (!ft_strcmp(content, "<"))
		return (RED_FROM);
	else
		return (WORD);
}

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*current;

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

t_token	*ft_newtoken(void *content)
{
	t_token		*re;

	re = (t_token *)malloc(sizeof(t_token));
	if (!re)
		return (0);
	re->value = content;
	re->type = (int)catego_toketype(content);
	re->next = 0;
	return (re);
}

t_token	*ms_tokenizer(char *line)
{
	char	**res;
	int		i;
	t_token	*token;
	t_token	*current;

	token = 0;
	i = 0;
	res = ft_split_qu(line, ' ');
	while (res[i])
	{
		if (check_special_char(res[i], line))
			return (0);
		current = ft_newtoken(res[i]);
		ft_tokenadd_back(&token, current);
		i++;
	}
	return (token);
}
