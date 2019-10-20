/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 04:32:02 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/20 19:24:23 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <limits.h>
# define MAXNSIZE		(sizeof(size_t) * 8)
# define BUFFER_SIZE	2048
# define SP				' '
# define HS				'#'
# define PL				'+'
# define MN				'-'

# define BUFF_SIZE 17
# define MAX_FILES 4864

typedef struct		s_flags
{
	size_t			zero : 1;
	size_t			space : 1;
	size_t			hash : 1;
	size_t			plus : 1;
	size_t			minus : 1;
	size_t			l : 1;
	size_t			ll : 1;
	size_t			h : 1;
	size_t			hh : 1;
	size_t			j : 1;
	size_t			z : 1;
	size_t			is_bigx : 1;
	size_t			is_neg : 1;
	size_t			is_precision : 1;
	size_t			is_width : 1;
	size_t			precision;
	size_t			width;

}					t_flags;

typedef struct		s_printf
{
	va_list			ap;
	t_flags			fl;
	char			conv_char;
	int				i;
	char			*buf;
	int				to_out;
	int				outfd;

}					t_printf;

void				add_ch_tobuf(const int c, t_printf *p);
size_t				parse_conv_string(const char *s, size_t i, t_printf *p);
size_t				fill_flags(const char *s, size_t i, t_printf *p);
void				get_arg(const char conv, t_printf *p);
char				count_onebits(const int c);
void				print_bit(size_t b);
unsigned char		count_act_bytes(const int c);
size_t				get_unsigned_arg(t_printf *p);
size_t				get_signed_arg(t_printf *p);

void				format_print_integer(const size_t d, t_printf *p);
void				format_print_char(const int c, t_printf *p);
void				format_print_string(const char *s, t_printf *p);
void				format_print_unistring(const wchar_t *s, t_printf *p);

int					ft_printf(const char *convstr, ...);
int					ft_dprintf(int fd, const char *convstr, ...);

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(const char *s);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int					ft_isalpha(int c);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(char *s);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				ft_strclr(char *s);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
size_t				ft_wordcount(char const *s, char c);
char				*ft_itoa(int n);
int					ft_atoi(char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_substrcmp(const char *s1, const char *s2, size_t n);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					get_next_line_fl(const int fd, char **line);

#endif
