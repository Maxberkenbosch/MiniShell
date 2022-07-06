#include "libft.h"

int	check_valid_n(char *cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_n(char **cmd_words)
{
	int	i;

	i = 0;
	while (cmd_words[i])
	{
		if (cmd_words[i][0] == '-' && cmd_words[i][1] == 'n')
		{
			if (!check_valid_n(cmd_words[i]))
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	ft_echo(char **cmd_words)
{
	int	nl;
	int	i;

	nl = 1;
	i = check_n(cmd_words);
	if (i >= 1)
		nl = 0;
	while (cmd_words[i])
	{
		ft_putstr_fd(cmd_words[i], STDOUT_FILENO);
		if (cmd_words[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (nl)
		ft_putendl_fd("", STDOUT_FILENO);
	return (0);
}
