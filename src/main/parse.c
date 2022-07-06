#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

int	handle_cmd(char *cmd, t_minishell *minishell, int piped)
{
	char	**cmd_words;
	int		status;

	if (!redirections(cmd, minishell, piped) || minishell->sig == SIGINT)
	{
		free(cmd);
		return (1);
	}
	if (minishell->sig == EOF)
	{
		ft_putstr_fd("\033[F>  boppp", 2);
		minishell->sig = 0;
	}
	cmd = remove_redirections(cmd);
	if (!cmd)
		return (0);
	cmd = expansions(cmd, minishell);
	cmd_words = ft_split_cmd(cmd, ' ');
	status = search_builtin(cmd_words, minishell);
	free(cmd);
	free_ptrarray(cmd_words);
	return (status);
}

void	parse(t_minishell *minishell)
{
	if (!check_tokens(minishell->line, minishell))
		return ;
	minishell->cmds = ft_split_shell(minishell->line, '|');
	minishell->pipex.am_cmds = ft_ptrarlen(minishell->cmds);
	if (minishell->pipex.am_cmds > 1)
		minishell->exit_code = ft_pipex(minishell->cmds, \
		minishell->pipex, *minishell);
	else
		minishell->exit_code = handle_cmd(*minishell->cmds, minishell, 0);
	free(minishell->cmds);
	return ;
}
