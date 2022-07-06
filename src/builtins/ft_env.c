#include "minishell.h"
#include "libft.h"

int	ft_env(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		ft_putendl_fd(minishell->env[i], 2);
		i++;
	}
	return (0);
}
