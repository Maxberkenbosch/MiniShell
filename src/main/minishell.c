#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>

static void	minishell_init(t_minishell *minishell, char **env)
{
	rl_catch_signals = 0;
	minishell->env = make_env(env);
	minishell->stdin_fd = dup(STDIN_FILENO);
	minishell->stdout_fd = dup(STDOUT_FILENO);
	minishell->exit_code = 0;
	if (minishell->stdin_fd < 0 || \
		minishell->stdout_fd < 0)
		error_handle("dup");
	minishell->sig = 0;
}

static void	minishell_reset(t_minishell *minishell)
{
	ft_dupstds(minishell->stdin_fd, minishell->stdout_fd);
	minishell->sig = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	minishell_init(&minishell, env);
	while (1)
	{
		signals();
		minishell.line = readline(PROMPT);
		if (!minishell.line)
		{
			ft_putendl_fd("exit", 2);
			exit (1);
		}
		if (ft_strlen(minishell.line))
		{
			add_history(minishell.line);
			parse(&minishell);
		}
		minishell_reset(&minishell);
		free(minishell.line);
	}
}
