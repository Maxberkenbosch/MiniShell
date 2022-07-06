#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	l;

	l = ft_strlen(s);
	while (l + 1)
	{
		if (*(s + l) == c)
			return ((char *)(s + l));
		l--;
	}
	return (0);
}
