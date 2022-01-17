/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:55:10 by twagner           #+#    #+#             */
/*   Updated: 2022/01/17 19:57:02 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "history.h"

/*
** INCREMENT SHLVL
** Increment shlvl variable each time we launch a minishell
*/

int	ms_increment_shlvl(void)
{
	int		ret;
	char	*str_inc_level;
	int		i_level;
	char	*level;

	ret = 0;
	level = ms_getenv("SHLVL");
	if (!level)
		ret = ms_setenv("SHLVL", "2");
	else
	{
		i_level = ft_atoi(level);
		str_inc_level = ft_itoa(++i_level);
		if (!str_inc_level)
			return (ERROR);
		ret = ms_setenv("SHLVL", str_inc_level);
		free(str_inc_level);
	}
	return (ret);
}

/*
** GARBAGE COLLECTOR
** Contains a pointer to what needs to be freed.
** Used when fork to free everything before exit.
*/

t_garbage_coll	*ms_init_garbage_coll(\
	t_history *histo, t_trans **ptable, t_node *tree)
{
	t_garbage_coll	*garcol;

	garcol = (t_garbage_coll *)malloc(sizeof(*garcol));
	if (!garcol)
		return (NULL);
	garcol->envp = NULL;
	garcol->histo = histo;
	garcol->ptable = ptable;
	garcol->tree = tree;
	garcol->heredoc_fds = NULL;
	return (garcol);
}

/*
** EMPTY THE GARBAGE
** Clear everything in the garbage
*/

void	ms_empty_garbage(t_garbage_coll *garcol)
{
	ms_clearenv();
	if (garcol->envp)
		ms_free_str_array(garcol->envp);
	if (garcol->histo)
		ms_histo_clear(garcol->histo);
	if (garcol->ptable)
		ms_free_table(garcol->ptable);
	if (garcol->tree)
		ms_clear_tree(&garcol->tree);
	if (garcol->heredoc_fds)
		free(garcol->heredoc_fds);
	free(garcol);
}
