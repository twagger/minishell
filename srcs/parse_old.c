/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_old.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:57:26 by twagner           #+#    #+#             */
/*   Updated: 2021/10/19 17:10:22 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
# include "../libft/libft.h"
/*
** Basic parser to allow Tom to work on exec
*/

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

int	ft_strnchr(const char *s, char c, int index)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i <= index)
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	env_len(char *c)
{
	int len;

	len = 0;
	while(c[len])
	{
		if(ft_isalnum(c[len]) || c[len] == '_')
			len++;
		else 
			return (0);
	}
	return (len);
}
int ft_strchr_index(char *s, char c)
{
	int len;

	len= -1;
	while (s[++len])
	{
		if (s[len] == c)
			return (len);
	}
	return (0);
}
char *replcace_var_2(char *cmd, char *var, char *newvar, int index)
{
	char *newcmd;
	int len;
	int i;
	int y;

	len = ft_strlen(cmd) - ft_strlen(var) - 1 + ft_strlen(newvar);
	newcmd =  malloc((len + 1) * sizeof(char));
	if (!newcmd)
		return (0);
	i = 0;
	y = 0;
	while(y < index)
	{
		if(cmd[y] == '"' || cmd[y] == '\'')
		{
			y++;
			continue ;
		}
		newcmd[i] = cmd[y];
		i++;
		y++;
	}
	while(*newvar)
	{
		newcmd[i] = *newvar;
		newvar++;
		i++;
	}
	newcmd[i] = '\0';
	//free(cmd);
	return newcmd;
}

char	*replace_var(char *c, char *cmd, int index)
{
	int		len;
	char	*var;
	char	*newvar;
	int		i;

	len = env_len(c);
	if (!len)
		return (0);
	var = malloc((len + 1) * sizeof(char));
	if (!var)
		return (0);
	i = -1;
	while(++i < len)
	{
		var[i] = c[i];
	}
	var[i] = '\0';
	newvar = getenv(var);
	cmd = replcace_var_2(cmd, var, newvar, index);
	// free(newvar);
	// free(var);
	return cmd;
}
char *check_if_envvar(char *cmd)
{
	int i;
	char *new;

	i = -1;
	while(cmd[++i])
	{
		if(cmd[i] == '$')
		{
			if((ft_strnchr(cmd, '\'', i+1) % 2))
				continue ;
			else
			{
				if (cmd[i+1])
					new = replace_var(&cmd[i+1], cmd, i);
			}
		}
	}
	if (new)
		return(new);
	return cmd;
}
char	**ms_parser(char *line)
{
	char	**res;
	int		i;

	i = -1;
	res = ft_split(line, '|');
	while(res[++i])
	{
		if(check_special_char(res[i], line))
			return (0);
		res[i] = check_if_envvar(res[i]);
		printf("res:%s\n", res[i]);
	}
	return (res);
}
int main()
{
	char *input = "echo \"$VSCODE_GIT_ASKPASS_MAIN\" |  echo '$USER' \"$USER '$USER'\"";
	ms_parser(input);
	return 0;
}