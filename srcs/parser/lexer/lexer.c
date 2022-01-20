/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:34:58 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/01/20 17:31:31 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ms_free_tokens(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
}

t_token_types	catego_toketype(char *content, int c)
{
	if (!content)
		return (T_END);
	if (!ft_strcmp(content, "|") && !c)
		return (T_PIPE);
	else if (!ft_strcmp(content, "<<") && !c)
		return (T_DLESS);
	else if (!ft_strcmp(content, ">>") && !c)
		return (T_DGREAT);
	else if (!ft_strcmp(content, ">") && !c)
		return (T_RED_TO);
	else if (!ft_strcmp(content, "<") && !c)
		return (T_RED_FROM);
	else
		return (T_WORD);
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

t_token	*ft_newtoken(void *content, int c)
{
	t_token		*re;

	re = (t_token *)malloc(sizeof(t_token));
	if (!re)
		return (0);
	re->value = content;
	re->type = (int)catego_toketype(content, c);
	re->qt_rm = c;
	re->next = 0;
	return (re);
}

t_token	*ms_tokenizer(char *line, int exit_code)
{
	t_token	*all;
	t_token	*current;
	int		len;
	char	*exit;

	all = 0;
	exit = ft_itoa(exit_code);
	while (*line)
	{
		while (*line == ' ' && *line)
			line++;
		len = count_len(line);
		if (!len)
			break ;
		current = check_each(len, line, exit);
		ft_tokenadd_back(&all, current);
		line = line + len;
	}
	ft_tokenadd_back(&all, ft_newtoken(NULL, 0));
	if (exit)
		free(exit);
	return (all);
}
