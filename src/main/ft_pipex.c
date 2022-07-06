#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int	heredoc_pipe_check(char *cmd, t_minishell minishell)
{
	int	check;

	check = 0;
	while (*cmd)
	{
		if (*cmd == '<' && *(cmd + 1) == '<')
		{
			heredoc(cmd + 2, &minishell);
			check = 1;
		}
		cmd++;
	}
	return (check);
}

void	child_exec(char *cmd, t_pipex pipex, t_minishell minishell)
{
	int	i;

	i = 0;
	if (pipex.heredoc && pipex.iter == pipex.am_cmds - 1)
		ft_dupstds(STDIN_FILENO, STDOUT_FILENO);
	else if (!pipex.iter)
		ft_dupstds(STDIN_FILENO, pipex.new_pipe[1]);
	else if (pipex.iter == pipex.am_cmds - 1)
		ft_dupstds(pipex.last_pipe, STDOUT_FILENO);
	else
		ft_dupstds(pipex.last_pipe, pipex.new_pipe[1]);
	if (pipex.iter != 0)
		close(pipex.last_pipe);
	close(pipex.new_pipe[0]);
	close(pipex.new_pipe[1]);
	handle_cmd(cmd, &minishell, 1);
	exit(0);
}

pid_t	fork_child(char *cmd, t_pipex pipex, t_minishell minishell)
{
	pid_t	child;

	if (heredoc_pipe_check(cmd, minishell))
		pipex.heredoc = 1;
	else
		pipex.heredoc = 0;
	child = fork();
	if (child < 0)
		error_handle("Fork");
	if (child == 0)
		child_exec(cmd, pipex, minishell);
	if (pipex.iter > 0)
		close(pipex.last_pipe);
	ft_dupstds(minishell.stdin_fd, minishell.stdout_fd);
	return (child);
}

int	childs_finish(int iter, pid_t *childs)
{
	int	status;

	while (iter)
	{
		waitpid(childs[iter - 1], &status, 0);
		iter--;
	}
	return (status);
}

int	ft_pipex(char **cmds, t_pipex pipex, t_minishell minishell)
{
	pid_t	*childs;
	int		status;

	childs = ft_calloc(pipex.am_cmds, sizeof(*childs));
	if (!childs)
		error_handle("Malloc");
	pipex.iter = 0;
	while (pipex.iter < pipex.am_cmds)
	{
		if (pipe(pipex.new_pipe) < 0)
			error_handle("Pipe");
		childs[pipex.iter] = fork_child(cmds[pipex.iter], pipex, minishell);
		pipex.last_pipe = pipex.new_pipe[0];
		close(pipex.new_pipe[1]);
		pipex.iter++;
	}
	status = childs_finish(pipex.iter, childs);
	free(childs);
	close(pipex.new_pipe[0]);
	if (status == SIGINT)
		return (130);
	return (WEXITSTATUS(status));
}
