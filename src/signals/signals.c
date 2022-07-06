#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>

void	sigint_handler_in_process(int sig)
{
	(void) sig;
	ft_putendl_fd("", 1);
}

void	sigint_handler(int sig)
{
	(void)sig;
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler_in_process(int sig)
{
	printf("Quit: %d\n", sig);
}

void	sig_in_process(char *cmd)
{
	if (!strncmp(cmd, "./minishell", 12) || !strncmp(cmd, "bash", 5))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, sigint_handler_in_process);
		signal(SIGQUIT, sigquit_handler_in_process);
	}
}

void	signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
