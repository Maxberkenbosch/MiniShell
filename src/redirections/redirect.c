#include "minishell.h"

static int	check_in(char *s, t_minishell *minishell, int piped)
{
	while (*s)
	{
		if (*s == '\"' || *s == '\'')
			s = skip_quote(s, 0);
		if (*s == '<')
		{
			if (*(s + 1) == '<' && !piped)
				s = heredoc(s + 2, minishell);
			else if (*(s + 1) != '<')
				s = redir_in(s + 1, minishell);
			else
				s += 2;
		}
		if (!s || minishell->sig == 2)
			return (0);
		s++;
	}
	return (1);
}

static int	check_out(char *s, t_minishell *minishell)
{
	while (*s)
	{
		if (*s == '\"' || *s == '\'')
			s = skip_quote(s, 0);
		if (*s == '>')
		{
			if (*(s + 1) == '>')
				s = redir_append(s + 2, minishell);
			else
				s = redir_out(s + 1, minishell);
		}
		if (!s)
			return (0);
		s++;
	}
	return (1);
}

int	redirections(char *s, t_minishell *minishell, int piped)
{
	if (!check_in(s, minishell, piped))
		return (0);
	if (!check_out(s, minishell))
		return (0);
	return (1);
}
