static int	whitespace(const char *s, int c)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

long	ft_atoi(const char *str)
{
	long	tot;
	int		mp;

	tot = 0;
	mp = 0;
	if (!str)
		return (0);
	while (whitespace(" \n\t\v\r\f", *str))
		str++;
	if (*str == '-' || *str == '+')
	{
		mp = *str;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		tot = tot * 10 + (*str - 48);
		str++;
	}
	if (mp == '-')
		return (tot * -1);
	return (tot);
}
