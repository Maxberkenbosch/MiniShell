#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*ptr;

	ptr = (const char *)s;
	while (n)
	{
		if (*ptr == c)
			return ((void *)ptr);
		n--;
		ptr++;
	}
	return (0);
}
