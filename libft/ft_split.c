#include "libft.h"

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
	size_t			len;

	while (*s == c)
		s++;
	len = 0;
	while (s[len] != c && s[len])
		len++;
	w = malloc(sizeof(char) * len + 1);
	if (!w)
		return (0);
	ft_strlcpy(w, s, len + 1);
	return (w);
}

static const char	*next_w(char const *s, char c)
{
	while (*s == c && *s)
		s++;
	while (*s != c && *s)
		s++;
	return (s);
}

static int	wrd_cntr(char const *s, char c)
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
			s++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		i;
	int		aw;

	if (!s)
		return (0);
	aw = wrd_cntr(s, c);
	words = malloc(sizeof(char *) * (aw + 1));
	if (!words)
		return (0);
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
