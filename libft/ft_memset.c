void	*ft_memset(void *str, int c, unsigned int len)
{
	unsigned char	*ptr;

	ptr = str;
	while (len > 0)
	{
		*ptr = c;
		ptr++;
		len--;
	}
	return (str);
}
