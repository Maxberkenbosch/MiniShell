int	ft_ptrarlen(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
		i++;
	return (i);
}
