#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	i;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n / 10)
			ft_putnbr_fd(n / 10, fd);
		else if (n < 0)
			write(fd, "-", 1);
		if (n < 0)
			n *= -1;
		i = n % 10 + '0';
		write(fd, &i, 1);
	}
}
