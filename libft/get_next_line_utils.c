#include "libft.h"

void	clean_buff(char *tmp, int index)
{
	while (index >= 0)
	{
		tmp[index] = 0;
		index--;
	}
}

void	ft_strncpy(char *dst, char *str, int len)
{
	int	i;

	i = 0;
	if (dst && str)
	{
		while (i < len)
		{
			dst[i] = str[i];
			i++;
		}
		if (dst[i - 1])
			dst[i] = 0;
	}
}

int	shift_buff(char *tmp, int index)
{
	if (tmp[index] == '\n')
	{
		ft_strncpy(tmp, tmp + index + 1, ft_strlen(&tmp[index + 1]) + 1);
		return (1);
	}
	return (0);
}

int	newl_end_search(char *tmp)
{
	int	i;

	i = 0;
	if (!tmp)
		return (-1);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	return (i);
}
