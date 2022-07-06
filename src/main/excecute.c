#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int	ft_execsys(char **cmd_words, t_minishell *minishell)
{
	pid_t	p;
	int		status;

	sig_in_process(cmd_words[0]);
	p = fork();
	if (p < 0)
		error_handle("fork");
	if (!p)
	{
		cmd_words = add_path(cmd_words, minishell->env);
		execve(cmd_words[0], cmd_words, minishell->env);
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd_words[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	waitpid(p, &status, 0);
	if (status == SIGINT)
		return (130);
	return (WEXITSTATUS(status));
}

int	search_builtin(char **cmd_words, t_minishell *minishell)
{
	int	status;

	status = 0;
	if (!(ft_strncmp(cmd_words[0], "exit", 5)))
		status = ft_exit(cmd_words + 1, minishell->pipex.am_cmds);
	else if (!(ft_strncmp(cmd_words[0], "echo", 5)))
		status = ft_echo(cmd_words + 1);
	else if (!(ft_strncmp(cmd_words[0], "pwd", 4)) || \
		!(ft_strncmp(cmd_words[0], "PWD", 4)))
		status = ft_pwd(minishell);
	else if (!(ft_strncmp(cmd_words[0], "env", 4)))
		status = ft_env(minishell);
	else if (!(ft_strncmp(cmd_words[0], "cd", 3)))
		status = ft_cd(cmd_words[1], minishell);
	else if (!(ft_strncmp(cmd_words[0], "export", 7)))
		status = ft_export(cmd_words, minishell);
	else if (!(ft_strncmp(cmd_words[0], "unset", 6)))
		status = ft_unset(cmd_words, minishell);
	else
		status = ft_execsys(cmd_words, minishell);
	return (status);
}
