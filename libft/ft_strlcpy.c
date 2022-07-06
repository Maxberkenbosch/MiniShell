#include "libft.h"

int	ft_strlcpy(char *dst, const char *str, unsigned int dsize)
{
	int	l;

	l = ft_strlen(str);
	if (!dsize)
		return (l);
	while (dsize > 1 && *str)
	{
		*dst = *str;
		dst++;
		str++;
		dsize--;
	}
	*dst = '\0';
	return (l);
}
