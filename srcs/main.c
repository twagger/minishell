/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:14:41 by twagner           #+#    #+#             */
/*   Updated: 2021/10/25 16:29:54 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printf_out(t_token *all)
{
	while (all->next)
	{
		printf("int :%d\n", all->type);
		printf("value:|%s|\n", (char *)all->value);
		all = all->next;
	}
	printf("int :%d\n", all->type);
	printf("value:|%s|\n", (char *)all->value);
}

int	ms_loop(void)
{
	char	*line;
	t_token	*token;
	int		status;

	status = 1;
	token = NULL;
	while (status)
	{
		line = readline("\x1B[32mMinishell> \e[0m");
		printf("line:%s\n", line);
		if (line)
		{
			token = ms_tokenizer(line);
			if (token)
				printf_out(token);
			// if (token)
			// 	return (ft_cleaner(line, NULL, ERROR));
			//status = ms_execute(args);
		}
		else
			printf("\n");
		//ft_cleaner(line, args, 0);
	}
	return (0);
}


int	main(void)
{
	if (ms_loop() == ERROR)
		return (1);
	return (0);
}
