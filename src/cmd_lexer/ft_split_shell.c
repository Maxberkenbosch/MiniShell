#include "minishell.h"
#include "libft.h"

static char	*fll_wrd(char *w, char *s, char c)
{
	int	len;

	while (*s == c)
		s++;
	len = 0;
	while (s[len] != c && s[len])
	{
		if (s[len] == '\"' || s[len] == '\'')
			skip_quote(&s[len], &len);
		if (s[len] != c)
			len++;
	}
	w = ft_calloc(len + 1, sizeof(char));
	if (!w)
		error_handle("malloc");
	ft_strlcpy(w, s, len + 1);
	return (w);
}

static char	*next_w(char *s, char c)
{
	while (*s == c && *s)
		s++;
	while (*s != c && *s)
	{
		if (*s == '\"' || *s == '\'')
			s = skip_quote(s, 0);
		if (*s != c)
			s++;
	}
	return (s);
}

static int	wrd_cntr(char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s != c && *s)
		{
			if (*s == '\"' || *s == '\'')
				s = skip_quote(s, 0);
			if (*s != c)
				s++;
		}
	}
	return (i);
}

char	**ft_split_shell(char *s, char c)
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
			free_ptrarray(words);
			return (0);
		}
		s = next_w(s, c);
		i++;
	}
	words[i] = NULL;
	return (words);
}
