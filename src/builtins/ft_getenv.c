#include "minishell.h"
#include "libft.h"

char	*ft_getenv(char *var, t_minishell *minishell)
{
	int		i;
	char	*pointer;
	size_t	var_len;

	i = 0;
	if (!ft_strncmp(var, "?", 2))
		return (ft_itoa(minishell->exit_code));
	if (*var == '$')
		return (ft_strdup_shell("$"));
	var_len = ft_strlen(var);
	pointer = NULL;
	while (!pointer)
	{
		if (!minishell->env[i])
			break ;
		pointer = (ft_strnstr(minishell->env[i], var, var_len));
		i++;
	}
	if (!pointer)
		return (ft_strdup_shell("\0"));
	pointer = ft_substr(pointer, var_len, ft_strlen(pointer + var_len));
	return (pointer);
}
