#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	free_array(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->env)
	{
		while (minishell->env[i])
		{
			free (minishell->env[i]);
			i++;
		}
		free (minishell->env);
	}
}

char	**make_new_array(t_minishell *minishell, char *new_element)
{
	int		i;
	char	**new_array;

	i = 0;
	while (minishell->env[i])
		i++;
	new_array = ft_calloc ((i + 2), (sizeof(char *)));
	if (!new_array)
		error_handle("malloc");
	i = 0;
	while (minishell->env[i])
	{
		new_array[i] = ft_strdup_shell(minishell->env[i]);
		i++;
	}
	new_array[i] = ft_strdup_shell(new_element);
	free_array(minishell);
	return (new_array);
}

char	**make_env(char **env)
{
	char	**copy_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	copy_env = ft_calloc(i + 1, sizeof(char *));
	if (!copy_env)
		error_handle("malloc");
	i = 0;
	while (env[i])
	{
		copy_env[i] = ft_strdup_shell(env[i]);
		if (!copy_env[i])
			error_handle("malloc");
		i++;
	}
	return (copy_env);
}

int	valid_identifier_unset(char *cmd_word, t_minishell *minishell)
{
	int	i;

	i = 0;
	if ((!ft_isalpha(cmd_word[0]) && cmd_word[0] != '_'))
	{
		minishell->exit_code = 1;
		printf("msh: export: `%s': not a valid identifier\n", cmd_word);
		return (1);
	}
	while (cmd_word[i])
	{
		if ((cmd_word[i] >= '\'' && cmd_word[i] <= '/') || \
		cmd_word[i] == ':' || cmd_word[i] == ';')
		{
			minishell->exit_code = 1;
			printf("msh: export: `%s': not a valid identifier\n", cmd_word);
			return (1);
		}
		i++;
	}
	return (0);
}

int	valid_identifier_export(char *cmd_word, t_minishell *minishell)
{
	int	i;

	i = 0;
	if ((!ft_isalpha(cmd_word[0]) && cmd_word[0] != '_'))
	{
		minishell->exit_code = 1;
		printf("msh: export: `%s': not a valid identifier\n", cmd_word);
		return (1);
	}
	while (cmd_word[i] && cmd_word[i] != '=')
	{
		if ((cmd_word[i] >= '\'' && cmd_word[i] <= '/') || \
		cmd_word[i] == ':' || cmd_word[i] == ';')
		{
			minishell->exit_code = 1;
			printf("msh: export: `%s': not a valid identifier\n", cmd_word);
			return (1);
		}
		i++;
	}
	return (0);
}
