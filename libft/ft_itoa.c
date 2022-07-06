#include "libft.h"

static int	pow_t(int i)
{
	int	n;

	n = 10;
	while (i > 1)
	{
		n *= 10;
		i--;
	}
	return (n);
}

static int	divbt(int n)
{
	int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*wr_i(int n, int powt, int min)
{
	char	*s;
	char	*p;

	s = malloc(powt + 2 + min);
	if (s == NULL)
		return (0);
	p = s;
	if (min)
	{
		*s = '-';
		s++;
	}
	while (powt)
	{
		*s = ((n / pow_t(powt)) % 10) + '0';
		s++;
		powt--;
	}
	*s = n % 10 + '0';
	s++;
	*s = 0;
	return (p);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		powt;
	int		min;

	min = 0;
	if (n == -2147483648)
	{
		s = malloc(sizeof(char) * 12);
		ft_strlcpy(s, "-2147483648", 12);
		return (s);
	}
	if (n < 0)
	{
		n *= -1;
		min = 1;
	}
	powt = divbt(n);
	s = wr_i(n, powt, min);
	return (s);
}
