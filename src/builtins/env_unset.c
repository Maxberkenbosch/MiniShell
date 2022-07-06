#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	var_not_legal(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			printf("msh: unset: `%s': not a valid identifier\n", var);
			return (1);
		}
		i++;
	}
	return (0);
}

int	var_in_env(char *var, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		if (!ft_strncmp(minishell->env[i], var, ft_strlen(var)))
			return (1);
		i++;
	}
	return (0);
}

void	del_item_array(t_minishell *minishell, int i)
{
	int	count;

	count = 0;
	free(minishell->env[i]);
	while (minishell->env[count])
		count++;
	while (i < count)
	{
		minishell->env[i] = minishell->env[i + 1];
		i++;
	}
	free(minishell->env[count - 1]);
}

int	ft_unset(char **cmd_words, t_minishell *minishell)
{
	int		i;
	int		j;
	char	*new_var;

	i = 1;
	while (cmd_words[i])
	{
		if (valid_identifier_unset(cmd_words[i], minishell) == 0)
		{
			j = 0;
			if (var_not_legal(cmd_words[i]))
				return (1);
			new_var = ft_strjoin_shell(cmd_words[i], "=");
			if (var_in_env(new_var, minishell) == 1 && minishell->env[j])
			{
				while (ft_strncmp(minishell->env[j], \
				new_var, ft_strlen(new_var)))
					j++;
				del_item_array(minishell, j);
			}
			free (new_var);
		}
		i++;
	}
	return (0);
}
