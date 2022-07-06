#include "libft.h"

int	check_set(unsigned char s1, char const *set)
{
	while (*set)
	{
		if (s1 == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	strt_nd(char const *s1, char const *set, int i)
{
	int	up;

	if (!i)
		up = 1;
	else
		up = 0;
	while (check_set(s1[i], set))
	{
		if (up)
			i++;
		else
			i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*dest;
	size_t	len;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	start = strt_nd(s1, set, 0);
	if (start == (int)len)
		return (ft_strdup("\0"));
	end = strt_nd(s1, set, len - 1);
	dest = ft_substr(s1, start, end + 1 - start);
	return (dest);
}
