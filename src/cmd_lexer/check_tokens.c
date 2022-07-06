#include "minishell.h"
#include "libft.h"
#include <unistd.h>

int	end_check(char *line)
{
	while (*line == ' ')
		line++;
	if (!*line)
		return (1);
	return (0);
}

void	unexpected_token(char *c, t_minishell *minishell, int nl)
{
	write(2, "msh: syntax error near unexpected token `", 41);
	if (nl)
		ft_putstr_fd(c, 2);
	else
		write(2, c, 1);
	write(2, "\'\n", 2);
	minishell->exit_code = 258;
}

int	special_char_check(char *line, t_minishell *minishell)
{
	char	token;
	int		token_count;

	token = *line;
	token_count = 0;
	while (*line == token)
	{
		token_count++;
		if ((token == '|' && token_count == 2) \
		|| token_count == 3 || (*line != token && check_set(*line, "|<>")))
		{
			unexpected_token(line, minishell, 0);
			return (0);
		}
		if (end_check(line + 1))
		{
			unexpected_token("newline", minishell, 1);
			return (0);
		}
		line++;
	}
	return (1);
}

int	name_check(char *line, t_minishell *minishell)
{
	char	token;

	token = *line;
	if (*(line + 1) == token)
		line += 2;
	else
		line++;
	line = skip_whitespace(line);
	if ((check_set(token, "<>") && check_set(*line, "|<>")) \
		|| (token == '|' && *line == '|'))
	{
		unexpected_token(line, minishell, 0);
		return (0);
	}
	return (1);
}

int	check_tokens(char *line, t_minishell *minishell)
{
	line = skip_whitespace(line);
	if (*line == '|')
	{
		unexpected_token(line, minishell, 0);
		return (0);
	}
	while (*line)
	{
		if (*line == '\"' || *line == '\'')
			line = skip_quote(line, 0);
		if (check_set(*line, "|<>"))
		{
			if (!special_char_check(line, minishell))
				return (0);
			if (!name_check(line, minishell))
				return (0);
		}
		line++;
	}
	return (1);
}
