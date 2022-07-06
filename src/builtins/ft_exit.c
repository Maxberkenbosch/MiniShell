#include "libft.h"
#include <stdio.h>

void	exit_error(char *s)
{
	ft_putstr_fd("msh: exit: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(255);
}

int	ft_exit(char **cmd_words, int am_cmds)
{
	int		i;
	char	*arg;

	i = 0;
	if (am_cmds < 2)
		ft_putendl_fd("exit", 2);
	arg = *cmd_words;
	if (arg)
	{
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
				exit_error(arg);
			i++;
		}
	}
	if (ft_ptrarlen(cmd_words) > 1)
	{
		ft_putendl_fd("msh: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	exit((unsigned char)ft_atoi(*cmd_words));
}
