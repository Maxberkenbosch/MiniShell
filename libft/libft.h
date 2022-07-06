#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFFER_SIZE 1024

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isascii(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *str, int c, unsigned int len);
void	ft_bzero(void *str, size_t n);
void	*ft_memcpy(void *dst, const void *str, size_t len);
void	*ft_memmove(void *dst, const void *str, size_t len);
int		ft_strlcat(char *dst, const char *str, unsigned int dsize);
int		ft_strlcpy(char *dst, const char *str, unsigned int dsize);
long	ft_atoi(const char *str);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, unsigned int len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, unsigned int len);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	clean_buff(char *tmp, int index);
char	*get_next_line(int fd);
int		newl_end_search(char *tmp);
int		shift_buff(char *tmp, int index);
void	ft_strncpy(char *dst, char *str, int len);
int		ft_ptrarlen(char **ar);
void	free_ptrarray(char **cmd);
int		check_set(unsigned char s1, char const *set);

#endif