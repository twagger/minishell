/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:57:26 by twagner           #+#    #+#             */
/*   Updated: 2021/10/20 18:10:28 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
# include "../libft/libft.h"
/*
** Basic parser to allow Tom to work on exec
*/
/*
** AST NODE TYPES
*/
typedef enum e_token_types
{
	WORD,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	PIPE,
	RED_TO,
	RED_FROM,
} 	e_token_types;

typedef struct s_token
{
	int				type;
	void			*value;
	struct s_token	*next;
}	t_token;

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

int		check_special_char(char *c, char *line)
{
	int sq;
	int dq;

	sq = 0;
	dq = 0;
	while(*c)
	{
		if (*c == '\\' || *c == ';')
			return (1);
		c++;
	}
	while(*line)
	{
		if (*line == '\'')
			sq++;
		else if (*line == '\"')
			dq++;
		line++;
	}
	if (sq % 2 || dq % 2)
		return (1);
	return (0);
}

e_token_types catego_toketype(char *content)
{
	if (!ft_strcmp(content , "|"))
		return (PIPE);
	else if (!ft_strcmp(content , "&&"))
		return (AND_IF);
	else if (!ft_strcmp(content , "||"))
		return (OR_IF);
	else if (!ft_strcmp(content , "<<"))
		return (DLESS);
	else if (!ft_strcmp(content , ">>"))
		return (DGREAT);
	else if (!ft_strcmp(content , ">"))
		return (RED_TO);
	else if (!ft_strcmp(content , "<"))
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

void printf_out(t_token *all)
{
	while(all->next)
	{
		printf("int :%d\n", all->type);
		printf("value:|%s|\n", all->value);
		all = all->next;
	}
	printf("int :%d\n", all->type);
	printf("value:|%s|\n", all->value);
}

t_token	*ms_tokenizer(char *line)
{
	char	**res;
	int		i;
	t_token *token;
	t_token *current;

	token = 0;
	i = 0;
	res = ft_split_qu(line, ' ');
	while(res[i])
	{
		if(check_special_char(res[i], line))
			return (0);
		current = ft_newtoken(res[i]);
		//res[i] = check_if_envvar(res[i]);
		ft_tokenadd_back(&token, current);
		i++;
	}
	printf_out(token);
	return (token);
}

// char	**ms_parser(char *line)
// {
// 	char	**res;
// 	int		i;

// 	i = -1;
// 	if (!ms_tokenizer(line))
// 		return NULL;
// 	res = ft_split(line, '|');
// 	while(res[++i])
// 	{
// 		if(check_special_char(res[i], line))
// 			return (0);
// 		res[i] = check_if_envvar(res[i]);
// 		printf("res:%s\n", res[i]);
// 	}
// 	return (res);
// }
int main()
{
	// char *input = "echo \"$VSCODE_GIT_ASKPASS_MAIN\" |  echo '$USER' \"$USER '$USER'\"";
	// ms_parser(input);
	ms_tokenizer("echo \' how are you? \' \' \"$USER\"  a\' || && >> file \'$USER\' ");
	// if (!ms_tokenizer("echo      \"hello       how are you?\" ||  p"))
	// {	
	// 	printf("Error occured\n");
	// 	return 1;
	// }
	return 0;
}