#include "minishell.h"
#include "libft.h"

int	len_wtht_quote(char const *s)
{
	int	len;

	len = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			s = skip_quote((char *)s, &len);
			len--;
		}
		s++;
		if (*s && *s != '\'' && *s != '\"')
			len++;
	}
	return (len);
}

void	copy_stripped_s(char *new_s, char *s)
{
	int	len;

	while (*s)
	{
		len = 0;
		if (*s == '\'' || *s == '\"')
		{
			skip_quote((char *)s, &len);
			s++;
			ft_strlcpy(new_s, s, len);
			s += len;
			new_s += len - 1;
		}
		else
		{
			*new_s = *s;
			new_s++;
			s++;
		}
	}
	*new_s = 0;
}

char	*strip_quotes(char *s)
{
	char	*new_s;
	int		len;

	len = len_wtht_quote(s);
	new_s = ft_calloc(len + 1, sizeof(char *));
	if (!new_s)
		error_handle("malloc");
	copy_stripped_s(new_s, s);
	free(s);
	return (new_s);
}
