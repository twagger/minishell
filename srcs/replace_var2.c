#include "../includes/minishell.h"
#include "../libft/libft.h"

int	check_special_char(char *c, char *line)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (*c)
	{
		if (*c == '\\' || *c == ';')
			return (1);
		c++;
	}
	while (*line)
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
	int	i;
	int	count;

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
