#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	valid_var(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (!ft_strncmp(&var[i], "=", 1))
			return (i);
		i++;
	}
	return (0);
}

int	check_double(char *var, t_minishell *minishell, int i)
{
	int	j;

	j = 0;
	while (minishell->env[j])
	{
		if (!ft_strncmp(minishell->env[j], var, ft_strlen(var)))
			return (1);
		j++;
	}
	j = 0;
	while (minishell->env[j])
	{
		if (!ft_strncmp(minishell->env[j], var, i + 1))
			return (2);
		j++;
	}
	return (0);
}

void	change_var(char *var, t_minishell *minishell, int i)
{
	int	j;

	j = 0;
	while (minishell->env[j])
	{
		if (!ft_strncmp(minishell->env[j], var, i))
			break ;
		j++;
	}
	free(minishell->env[j]);
	minishell->env[j] = ft_strdup_shell(var);
}

void	declare_export(t_minishell *minishell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (minishell->env[i])
	{
		printf("declare -x ");
		while (minishell->env[i][j])
		{
			if (minishell->env[i][j - 1] == '=')
				printf("\"");
			printf("%c", minishell->env[i][j]);
			j++;
		}
		printf("\"\n");
		i++;
		j = 0;
	}
}

int	ft_export(char **cmd_words, t_minishell *minishell)
{
	int	i;
	int	iter;

	iter = 1;
	if (!cmd_words[1])
	{
		declare_export(minishell);
		return (1);
	}
	while (cmd_words[iter])
	{
		if (valid_identifier_export(cmd_words[iter], minishell) == 0)
		{
			i = valid_var(cmd_words[iter]);
			if (!i || check_double(cmd_words[iter], minishell, i) == 1)
				return (1);
			if (check_double(cmd_words[iter], minishell, i) == 2)
				change_var(cmd_words[iter], minishell, i);
			else
				minishell->env = make_new_array(minishell, cmd_words[iter]);
		}
		iter++;
	}
	return (0);
}
