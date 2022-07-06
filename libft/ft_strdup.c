#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	void	*dst;

	len = ft_strlen(s1) + 1;
	dst = malloc(len);
	if (!dst)
		return (0);
	return (ft_memcpy(dst, s1, len));
}
