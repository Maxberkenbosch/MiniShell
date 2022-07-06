#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void	file_error(char *file_name, t_minishell *minishell)
{
	ft_putstr_fd("msh: ", 2);
	perror(file_name);
	minishell->exit_code = 1;
}

char	*redir_append(char *s, t_minishell *minishell)
{
	int		fd;
	char	*file_name;

	file_name = get_file_name(s);
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 00664);
	if (fd < 0)
	{
		file_error(file_name, minishell);
		free(file_name);
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		error_handle("dup2");
	close(fd);
	free(file_name);
	return (s);
}

char	*redir_out(char *s, t_minishell *minishell)
{
	int		fd;
	char	*file_name;

	file_name = get_file_name(s);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 00664);
	if (fd < 0)
	{
		file_error(file_name, minishell);
		free(file_name);
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		error_handle("dup2");
	close(fd);
	free(file_name);
	return (s);
}

char	*redir_in(char *s, t_minishell *minishell)
{
	int		fd;
	char	*file_name;

	file_name = get_file_name(s);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		file_error(file_name, minishell);
		free(file_name);
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		error_handle("dup2");
	close(fd);
	free(file_name);
	return (s);
}
