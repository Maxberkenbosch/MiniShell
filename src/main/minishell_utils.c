#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

char	*skip_whitespace(char *line)
{
	while (check_set(*line, "\t "))
		line++;
	return (line);
}

char	*ft_strchr_var(const char *s, int c)
{
	while (*s)
	{
		if (*s == '\'')
			s = skip_quote((char *)s, 0);
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (0);
}

char	*skip_quote(char *s, int *i)
{
	char	c;

	c = *s;
	s++;
	if (i)
		*i = *i + 1;
	while (*s != c && *s)
	{
		s++;
		if (i)
			*i = *i + 1;
	}
	return (s);
}

char	*ft_strdup_shell(const char *s1)
{
	int		len;
	void	*dst;

	len = ft_strlen(s1) + 1;
	dst = malloc(len * sizeof(char));
	if (!dst)
		error_handle("malloc");
	return (ft_memcpy(dst, s1, len));
}

char	*ft_strjoin_shell(char const *s1, char const *s2)
{
	char			*dst;
	unsigned int	dsize;

	if (!s1 || !s2)
		return (0);
	dsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = ft_calloc(dsize, sizeof(char));
	if (dst == NULL)
		error_handle("malloc");
	ft_strlcpy(dst, s1, dsize);
	ft_strlcat(dst, s2, dsize);
	return (dst);
}
