#include "libft.h"

static char	*line_fill(char *s, char *tmp, int index)
{
	int		size;
	int		c_size;
	char	*new_s;

	c_size = ft_strlen(s);
	size = c_size + index + 1;
	if (tmp[index] == '\n')
		size++;
	new_s = malloc(size * sizeof(char));
	if (!new_s)
	{
		free(s);
		return (0);
	}
	if (s)
	{
		ft_strncpy(new_s, s, c_size);
		free(s);
	}
	ft_strncpy(new_s + c_size, tmp, index + 1);
	return (new_s);
}

static int	fill_buff(int fd, char *tmp)
{
	int	i;

	i = read(fd, tmp, BUFFER_SIZE);
	tmp[i] = 0;
	return (i);
}

char	*fill_loop(int fd, char *s, char *tmp, int index)
{
	while (index == BUFFER_SIZE)
	{
		s = line_fill(s, tmp, index);
		if (!s)
			return (s);
		fill_buff(fd, tmp);
		index = newl_end_search(tmp);
	}
	s = line_fill(s, tmp, index);
	if (!s)
		return (s);
	if (tmp[index] == '\n')
	{
		shift_buff(tmp, index);
		return (s);
	}
	clean_buff(tmp, index);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	tmp[BUFFER_SIZE + 1];
	char		*s;
	int			index;

	s = NULL;
	index = newl_end_search(tmp);
	if (*tmp)
	{
		s = line_fill(s, tmp, index);
		if (!s)
			return (s);
	}
	if (tmp[index] == '\n')
	{
		shift_buff(tmp, index);
		return (s);
	}
	if (fill_buff(fd, tmp) <= 0)
		return (s);
	index = newl_end_search(tmp);
	s = fill_loop(fd, s, tmp, index);
	return (s);
}
