#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <limits.h>

void	change_env_oldpwd(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (ft_strncmp("OLDPWD=", minishell->env[i], 6) != 0)
		i++;
	minishell->env[i] = ft_strdup_shell("OLDPWD=");
}

void	pwd_is_accesable(t_minishell *minishell, int i, char *oldpwd)
{
	char	buf[PATH_MAX];

	free(minishell->env[i]);
	minishell->env[i] = ft_strjoin_shell("PWD=", getcwd(buf, PATH_MAX));
	i = 0;
	while (ft_strncmp("OLDPWD=", minishell->env[i], 6) != 0)
		i++;
	free(minishell->env[i]);
	minishell->env[i] = ft_strjoin_shell("OLDPWD=", oldpwd);
}

void	change_env(t_minishell *minishell, char *oldpwd)
{
	int		i;
	int		pwd_accesable;

	i = 0;
	pwd_accesable = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp("PWD=", minishell->env[i], 4) == 0)
		{
			pwd_accesable = 1;
			break ;
		}
		i++;
	}
	if (pwd_accesable)
		pwd_is_accesable(minishell, i, oldpwd);
	else
		change_env_oldpwd(minishell);
}

int	ft_cd(char *path, t_minishell *minishell)
{
	char	*oldpwd;
	char	*home;
	char	buf[PATH_MAX];

	oldpwd = getcwd(buf, PATH_MAX);
	home = ft_getenv("HOME=", minishell);
	if (!path)
	{
		if (chdir(home) < 0)
		{
			printf("msh: cd: HOME not set\n");
			free(home);
			return (1);
		}
	}
	else if (chdir(path) < 0)
	{
		ft_putstr_fd("msh: cd: ", 2);
		perror(path);
		free(home);
		return (1);
	}
	free(home);
	change_env(minishell, oldpwd);
	return (0);
}
