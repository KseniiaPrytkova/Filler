/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_print_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 04:40:19 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/20 19:30:48 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline void	fprint_str(const char *s, const size_t len, t_printf *p)
{
	size_t			i;

	i = 0;
	if (p->fl.is_precision && p->fl.precision <= len)
	{
		while (i < p->fl.precision)
			add_ch_tobuf(s[i++], p);
	}
	else
		while (s[i])
			add_ch_tobuf(s[i++], p);
}

void				format_print_string(const char *s, t_printf *p)
{
	const size_t	len = ((s) ? ft_strlen(s) : 6);
	const char		width_char = ((p->fl.zero) ? '0' : SP);
	const char		nullstr[] = "(null)";
	size_t			min_len;

	if (!s)
		s = nullstr;
	min_len =
	(p->fl.is_precision && p->fl.precision <= len) ? p->fl.precision : len;
	while (!p->fl.minus && p->fl.width && p->fl.width-- > min_len)
		add_ch_tobuf(width_char, p);
	fprint_str(s, len, p);
	while (p->fl.minus && p->fl.width && p->fl.width-- > min_len)
		add_ch_tobuf(SP, p);
}

static inline int	is_conv_str_char(const char c)
{
	return ((c == SP || c == HS || c == PL || c == MN
	|| ft_isdigit(c) || c == '.' || c == 'l' || c == 'h'
	|| c == 'j' || c == 'z') ? 1 : 0);
}

size_t				parse_conv_string(const char *s, size_t i, t_printf *p)
{
	while (s[i] && is_conv_str_char(s[i]))
		i += fill_flags(s, i, p);
	if (s[i] == 0)
		return (i);
	if (s[i] == 'S' || s[i] == 'C' || s[i] == 'D'
	|| s[i] == 'O' || s[i] == 'U')
		p->fl.l = 1;
	else if (s[i] == 'X')
		p->fl.is_bigx = 1;
	else if (s[i] == 'p')
		p->fl.hash = 1;
	p->conv_char = ft_tolower(s[i]);
	get_arg(s[i], p);
	ft_bzero(&p->fl, sizeof(p->fl));
	return (++i);
}

void				print_bit(size_t b)
{
	char			arr[MAXNSIZE];
	unsigned char	i;

	i = 0;
	while (b && i < MAXNSIZE)
	{
		arr[i++] = b & 1 ? '1' : '0';
		b >>= 1;
	}
	while (i--)
		ft_putchar(arr[i]);
}
