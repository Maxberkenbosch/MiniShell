#include "libft.h"

int	ft_strlcat(char *dst, const char *str, unsigned int dsize)
{
	unsigned int	l;

	l = ft_strlen(dst);
	if (dsize > l)
		ft_strlcpy(dst + l, str, dsize - l);
	else
		return (ft_strlen(str) + dsize);
	l += ft_strlen(str);
	return (l);
}
