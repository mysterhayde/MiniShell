/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:27:54 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/22 01:50:36 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# ifndef INT_MAX
#  define INT_MAX			2147483647
# endif
# ifndef INT_MIN
#  define INT_MIN 			-2147483648
# endif

//-------------------------------- COLORS --------------------------------------

# define COLOR_RED 			"\x1b[31m"
# define COLOR_RED_ULTRA	"\x1b[31;1m"
# define COLOR_GREEN 		"\x1b[32m"
# define COLOR_GREEN_ULTRA	"\x1b[32;1m"
# define COLOR_YELLOW		"\x1b[33m"
# define COLOR_BLUE			"\x1b[34m"
# define COLOR_PURPLE		"\x1b[35m"
# define COLOR_CYAN			"\x1b[36m"
# define COLOR_RESET		"\x1b[0m"
# define BLUE_LIGHT 		"\033[94m"
# define PURPLE 			"\033[35m"

//-------------------------------- LIBFT ---------------------------------------

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strmincmp(const char *s1, const char *s2, size_t min);

char	*ft_itoa(int n);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim_free(char *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *s, char c);

long	ft_atol(const char *str);

void	free_tab(char **tab);
void	safe_free(void **ptr);
void	ft_bzero(void *s, size_t n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_strtrim_nc(char **s1, char const *set);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

void	*ft_realloc(void *ptr, size_t size);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);

size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_lstsize(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//-------------------------------- PRINTF --------------------------------------

int		putnbr_pf(int n, int *value);
int		putchar_pf(char c, int value);
int		putstr_pf(char *s, int value);
int		ft_printf(const char *format, ...);
int		unsigned_putnbr_pf(unsigned int n, int *value);
int		write_pointer_pf(unsigned long un, int *value);
int		print_hex_pf(unsigned int un, int *value, char param);

//-------------------------------- GetNextLine ---------------------------------

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# define MAXFD 256

char	*get_next_line(int fd);
int		ft_gnl_strchr(char *str);

//---------------------------------- Tables ------------------------------------

size_t	ft_chartable_linecount(char **table);
void	ft_free_chartable(char **table);
int		ft_print_chartable(char **table);

void	*set(void *vtarget, void *target_new);
void	*set2(void **vtarget, void *target_new);

#endif
