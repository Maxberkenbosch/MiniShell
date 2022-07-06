#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	char			*dst;
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup("\0"));
	if ((unsigned)ft_strlen(s + start) < len)
		dst = malloc(sizeof(char) * (ft_strlen(s + start) + 1));
	else
		dst = malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (0);
	while (i < len && (s + start)[i])
	{
		dst[i] = (s + start)[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}
