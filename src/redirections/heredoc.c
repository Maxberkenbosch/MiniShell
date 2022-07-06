#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>

int	g_global = 0;

void	sigint_handler_heredoc(int sig)
{
	int	end[2];

	g_global = sig;
	if (pipe(end) < 0)
		error_handle("pipe");
	ft_putendl_fd("", 1);
	close(end[1]);
	ft_dupstds(end[0], STDIN_FILENO);
	close(end[0]);
}

void	heredoc_end(t_heredoc here)
{
	free(here.line);
	free(here.delimiter);
	close(here.end[1]);
	ft_dupstds(here.end[0], here.old_out);
	close(here.end[0]);
}

void	heredoc_init(char *s, t_minishell *minishell, t_heredoc *here)
{
	signal(SIGINT, sigint_handler_heredoc);
	here->old_out = dup(STDOUT_FILENO);
	if (here->old_out < 0)
		error_handle("dup");
	ft_dupstds(minishell->stdin_fd, minishell->stdout_fd);
	here->delimiter = get_file_name(s);
	if (pipe(here->end) < 0)
		error_handle("pipe");
}

void	heredoc_nonl(t_minishell *minishell)
{
	ft_putstr_fd("\033[F> ", 2);
	minishell->sig = 0;
}

char	*heredoc(char *s, t_minishell *minishell)
{
	t_heredoc	here;

	heredoc_init(s, minishell, &here);
	if (minishell->sig == EOF)
		heredoc_nonl(minishell);
	here.line = readline("> ");
	while (here.line && \
	ft_strncmp(here.delimiter, here.line, (ft_strlen(here.delimiter) + 1)))
	{
		if (g_global == 2)
			break ;
		here.line = expansions(here.line, minishell);
		write(here.end[1], here.line, ft_strlen(here.line));
		ft_putendl_fd("", here.end[1]);
		free(here.line);
		here.line = readline("> ");
	}
	if (!g_global && !here.line)
		minishell->sig = EOF;
	else
		minishell->sig = g_global;
	heredoc_end(here);
	return (s);
}
