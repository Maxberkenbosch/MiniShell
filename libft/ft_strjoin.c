#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dst;
	unsigned int	dsize;

	if (!s1 || !s2)
		return (0);
	dsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = ft_calloc(dsize, sizeof(char));
	if (dst == NULL)
		return (0);
	ft_strlcpy(dst, s1, dsize);
	ft_strlcat(dst, s2, dsize);
	return (dst);
}
