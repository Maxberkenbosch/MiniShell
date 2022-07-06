#include "minishell.h"
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	error_handle(char const *s)
{
	ft_putstr_fd("msh: ", 2);
	perror(s);
	exit(EXIT_FAILURE);
}

char	*path_str(char *s, char *s2)
{
	char	*new_s;
	int		len_s;
	int		len_s2;

	len_s = ft_strlen(s);
	len_s2 = ft_strlen(s2);
	new_s = ft_calloc(len_s + len_s2 + 2, sizeof(char));
	if (!new_s)
		error_handle("malloc");
	ft_strlcpy(new_s, s, len_s + 1);
	new_s[len_s] = '/';
	ft_strlcpy(new_s + len_s + 1, s2, len_s2 + 1);
	return (new_s);
}

char	**get_path(char **env)
{
	int		x;
	int		y;
	char	*prefix;

	x = 0;
	prefix = "PATH=";
	while (env[x])
	{
		y = 0;
		while (env[x][y] && y < 5)
		{
			if (env[x][y] != prefix[y])
				y = 6;
			y++;
			if (y == 5)
				return (ft_split_cmd(env[x] + y, ':'));
		}
		x++;
	}
	return (0);
}

char	**add_path(char **cmd, char **env)
{
	char	**paths;
	int		i;
	char	*new_path;

	paths = get_path(env);
	if (!paths)
		return (cmd);
	i = 0;
	while (paths[i])
	{
		new_path = path_str(paths[i], cmd[0]);
		if (access(new_path, F_OK) == 0)
		{
			free_ptrarray(paths);
			free(cmd[0]);
			cmd[0] = new_path;
			return (cmd);
		}
		free(new_path);
		i++;
	}
	free_ptrarray(paths);
	return (cmd);
}
