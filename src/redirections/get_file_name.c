#include "minishell.h"
#include "libft.h"

int	name_len(char *s)
{
	int	i;

	i = 0;
	while (*s == ' ')
		s++;
	while (!check_set(*s, " <>") && *s)
	{
		if (*s == '\"' || *s == '\'')
		{
			s = skip_quote(s, &i);
			i -= 2;
		}
		s++;
		i++;
	}
	return (i);
}

void	file_name_cpy(char *name, char *s)
{
	int	check;

	check = 0;
	while (*s == ' ')
		s++;
	while ((!check_set(*s, " <>") || check) && *s)
	{
		if (((*s == '\"' || *s == '\'') && !check) \
		|| check == *s)
		{
			if (!check)
				check = *s;
			else if (check == *s)
				check = 0;
			s++;
		}
		if (!check_set(*s, " <>") || check)
		{
			*name = *s;
			name++;
			s++;
		}
	}
	*name = 0;
}

char	*get_file_name(char *s)
{
	char	*name;
	int		name_l;

	name_l = name_len(s);
	name = ft_calloc(name_l + 1, sizeof(char));
	if (!name)
		error_handle("malloc");
	file_name_cpy(name, s);
	return (name);
}
