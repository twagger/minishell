/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonical_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:04:46 by twagner           #+#    #+#             */
/*   Updated: 2021/12/28 16:05:22 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_clear_components(char **components)
{
	if (components)
	{
		while (*components)
		{
			free(*components);
			++components;
		}
		free (components);
	}
}

static void	ms_pop_stack(t_list **stack)
{
	if (!(*stack))
		return;
	else if (!(*stack)->next)
	{
		ft_lstdelone(*stack, free);
		*stack = NULL;
	}
	else
	{
		while ((*stack)->next->next)
			*stack = (*stack)->next;
		ft_lstdelone((*stack)->next, free);
		(*stack)->next = NULL;
	}
}

static int	ms_add_stack(t_list **stack, char *component)
{
	t_list	*new;

	new = ft_lstnew((void *)*component);
	if (!new)
	{
		ft_lstclear(stack, free);
		return (ERROR);
	}
	ft_lstadd_back(stack, new);
	return (0);
}

static char	*ms_stack_to_canonical_path(t_list *stack, char **components)
{
	char	*canonical;
	char	*step1;
	int		first;

	first = 1;
	canonical = NULL;
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (!first)
		{
			step1 = ft_strjoin("/", stack->content);
			if (!step1)
				return (NULL);
			canonical = ft_strjoin(canonical, step1);
		}
		else
			canonical = ft_strjoin(canonical, step1);
		if (!canonical)
		{
			free(step1);
			return (NULL);
		}
		stack = stack->next;
	}
	// free components
	// free stack
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
		return (NULL);
	i = -1;
	while (components[++i])
	{
		if (!ft_strcmp("..", components[i]))
			ms_pop_stack(&stack);
		else if (!(ft_strlen(components[i]) == 1 && components[i][0] == '.')) 
		{
			if (ms_add_stack(&stack, components[i]) == ERROR)
			{
				ms_clear_components(components);
				return (NULL);
			}
		}
	}
	return (ms_stack_to_canonical_path(stack, components));
}