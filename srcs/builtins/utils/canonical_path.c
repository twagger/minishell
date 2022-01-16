/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonical_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:04:46 by twagner           #+#    #+#             */
/*   Updated: 2022/01/15 10:28:55 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ms_canonical_cleaner(t_list **stack, char **component, char *path)
{
	if (stack)
		ft_lstclear(stack, free);
	if (component)
		ms_free_str_array(component);
	if (path)
		free(path);
	return (NULL);
}

static void	ms_pop_stack(t_list **stack)
{
	t_list	*begin;

	if (!(*stack))
		return ;
	else if (!(*stack)->next)
	{
		ft_lstdelone(*stack, free);
		*stack = NULL;
	}
	else
	{
		begin = *stack;
		while ((*stack)->next->next)
			*stack = (*stack)->next;
		ft_lstdelone((*stack)->next, free);
		(*stack)->next = NULL;
		*stack = begin;
	}
}

static int	ms_add_stack(t_list **stack, char *component)
{
	t_list	*new;
	char	*content;

	content = ft_strdup(component);
	if (!content)
		return (ERROR);
	new = ft_lstnew((void *)content);
	if (!new)
	{	
		free(content);
		return (ERROR);
	}
	ft_lstadd_back(stack, new);
	return (0);
}

static char	*ms_stack_to_canonical_path(t_list *stack)
{
	char	*canonical;
	char	*tmp;
	int		first;
	t_list	*begin;

	first = 2;
	canonical = NULL;
	begin = stack;
	while (stack)
	{
		if (--first > 0)
			canonical = ft_strdup(stack->content);
		else
		{
			tmp = canonical;
			canonical = ms_join_with_slash(canonical, stack->content);
			free(tmp);
		}
		if (!canonical)
			return (ms_canonical_cleaner(&begin, NULL, NULL));
		stack = stack->next;
	}
	ms_canonical_cleaner(&begin, NULL, NULL);
	return (canonical);
}

/*
** CONVERT CANONICAL
** This function converts a path to a canonical form, clearing all 
** unnecessary . and .. and //// to keep a simple path form.
** For example : /a/./b/../../c/ -> /c
*/

char	*ms_convert_canonical(char *path)
{
	char	**components;
	t_list	*stack;
	int		i;

	stack = NULL;
	if (!path)
		return (NULL);
	components = ft_split(path, '/');
	if (!components)
		return (ms_canonical_cleaner(NULL, NULL, path));
	i = -1;
	while (components[++i])
	{
		if (!ft_strcmp("..", components[i]))
			ms_pop_stack(&stack);
		else if (ft_strcmp(".", components[i]))
		{
			if (ms_add_stack(&stack, components[i]) == ERROR)
				return (ms_canonical_cleaner(&stack, components, path));
		}
	}
	ms_canonical_cleaner(NULL, components, path);
	return (ms_stack_to_canonical_path(stack));
}
