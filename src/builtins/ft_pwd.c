#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int	ft_pwd(t_minishell *minishell)
{
	int		i;
	char	*pwd;
	int		check;
	char	buf[PATH_MAX];

	check = 0;
	i = 0;
	while (minishell->env[i])
	{
		if (!ft_strncmp(minishell->env[i], "PWD=", 4))
		{
			check = 1;
			break ;
		}
		i++;
	}
	if (check == 0)
		printf("%s\n", getcwd(buf, PATH_MAX));
	pwd = ft_substr(minishell->env[i], 4, ft_strlen(minishell->env[i]));
	ft_putendl_fd(pwd, 2);
	free (pwd);
	return (0);
}
