#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static void	fr_wrds(char **words, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(words[j]);
		j++;
	}
	free(words);
}

static char	*fll_wrd(char *w, char const *s, char c)
{
	int	len;

	len = 0;
	while (*s == c)
		s++;
	while (s[len] != c && s[len])
	{
		if (s[len] == '\'' || s[len] == '\"')
			skip_quote((char *)&(s[len]), &len);
		len++;
	}
	w = ft_calloc(len + 1, sizeof(char));
	if (!w)
		error_handle("malloc");
	ft_strlcpy(w, s, len + 1);
	if (ft_strchr(w, '\'') || ft_strchr(w, '\"'))
		w = strip_quotes(w);
	return (w);
}

static const char	*next_w(char const *s, char c)
{
	while (*s == c)
		s++;
	while (*s != c && *s)
	{
		if (*s == '\'' || *s == '\"')
			s = skip_quote((char *)s, 0);
		s++;
	}
	return (s);
}

static int	wrd_cntr(char const *s, char c)
{
	int		i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\'' || *s == '\"')
			s = skip_quote((char *)s, 0);
		if (*s)
			i++;
		while (*s != c && *s)
		{
			s++;
			if (*s == '\'' || *s == '\"')
				s = skip_quote((char *)s, 0);
		}
	}
	return (i);
}

char	**ft_split_cmd(char const *s, char c)
{
	char	**words;
	int		i;
	int		aw;

	if (!s)
		return (0);
	aw = wrd_cntr(s, c);
	words = ft_calloc((aw + 1), sizeof(char *));
	if (!words)
		error_handle("malloc");
	i = 0;
	while (i < aw)
	{
		words[i] = fll_wrd(words[i], s, c);
		if (!words[i])
		{
			fr_wrds(words, i);
			return (0);
		}
		s = next_w(s, c);
		i++;
	}
	words[i] = NULL;
	return (words);
}
