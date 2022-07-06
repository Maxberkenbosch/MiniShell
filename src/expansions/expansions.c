#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int	var_counter(char *s)
{
	int	i;

	s = ft_strchr_var(s, '$') + 1;
	i = 1;
	while (ft_strchr_var(s, '$'))
	{
		s = ft_strchr_var(s, '$') + 1;
		i++;
	}
	return (i);
}

char	*get_var(char *s)
{
	int		i;
	char	*var;

	i = 1;
	if (s[i] == '?' || ft_isdigit(s[i]))
		i++;
	else
	{
		while ((ft_isalnum(s[i]) || s[i] == '_') && s[i])
			i++;
	}
	var = ft_calloc((i + 1), sizeof(char));
	if (!var)
		error_handle("malloc");
	ft_strlcpy(var, s, i + 1);
	return (var);
}

char	**make_vars(char *s)
{
	char	**vars;
	int		am_vars;
	int		i;

	am_vars = var_counter(s);
	vars = ft_calloc((am_vars + 1), sizeof(char *));
	if (!vars)
		error_handle("malloc");
	i = 0;
	while (i < am_vars)
	{
		vars[i] = get_var(ft_strchr_var(s, '$'));
		s = ft_strchr_var(s, '$') + 1;
		i++;
	}
	vars[i] = NULL;
	return (vars);
}

char	*expansions(char *s, t_minishell *minishell)
{
	char	**vars;
	char	*new_s;
	int		var_len;

	if (ft_strchr_var(s, '$') == 0)
		return (s);
	vars = make_vars(s);
	var_len = conv_vars(vars, minishell);
	new_s = ft_calloc((ft_strlen(s) + var_len + 1), sizeof(char));
	if (!new_s)
		error_handle("malloc");
	sub_vars(new_s, s, vars);
	free(vars);
	free(s);
	return (new_s);
}
