#include "minishell.h"
#include <stdlib.h>
#include "libft.h"

int	strlen_end(char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == '\"' || *s == '\'')
			s = skip_quote(s, &i);
		if (*s == '<' || *s == '>')
		{
			if (*(s + 1) == *s)
				s++;
			s++;
			s = skip_whitespace(s);
			while (*s != ' ' && *s)
				s++;
		}
		else
		{
			i++;
			s++;
		}
	}
	return (i);
}

void	cpy_no_redir(char *s, char *new_s, char c)
{
	while (*s)
	{
		if (*s == '\"' || *s == '\'')
		{
			if (!c)
				c = *s;
			else if (c == *s)
				c = 0;
		}
		if ((*s == '<' || *s == '>') && !c)
		{
			if (*(s + 1) == *s)
				s++;
			s++;
			s = skip_whitespace(s);
			while (*s != ' ' && *s)
				s++;
		}
		*new_s = *s;
		s++;
		new_s++;
	}
	*new_s = 0;
}

char	*remove_redirections(char *s)
{
	int		len_end;
	char	*new_s;

	len_end = strlen_end(s);
	if (!len_end)
	{
		free(s);
		return (0);
	}
	new_s = ft_calloc(len_end + 1, sizeof(char));
	if (!new_s)
		error_handle("malloc");
	cpy_no_redir(s, new_s, 0);
	free(s);
	if (!*skip_whitespace(new_s))
	{
		free(new_s);
		return (0);
	}
	return (new_s);
}
