/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 04:32:45 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/20 19:30:41 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline size_t		parse_width(const char *s, size_t i, t_printf *p)
{
	const int				init_pos = i;

	p->fl.is_width = 1;
	while (ft_isdigit(s[i]))
		p->fl.width = p->fl.width * 10 + (s[i++] - '0');
	return (i - init_pos);
}

static inline size_t		parse_prec(const char *s, size_t i, t_printf *p)
{
	const int				init_pos = i;

	p->fl.is_precision = 1;
	if (ft_isdigit(s[i + 1]))
		i++;
	else if (!(p->fl.precision = 0))
		return (1);
	while (ft_isdigit(s[i]))
		p->fl.precision = p->fl.precision * 10 + (s[i++] - '0');
	return (i - init_pos);
}

static inline size_t		get_width_prec(const char *s, size_t i, t_printf *p)
{
	const size_t			init_pos = i;

	if (s[i] == '0' && !ft_isdigit(s[i - 1]))
	{
		p->fl.zero = 1;
		while (s[i] && s[i] == '0')
			i++;
		return (i - init_pos);
	}
	else if (s[i] == '.')
		return (parse_prec(s, i, p));
	else if (ft_isdigit(s[i]))
		return (parse_width(s, i, p));
	return (1);
}

void						get_arg(const char conv, t_printf *p)
{
	if (p->conv_char == 'i' || p->conv_char == 'd')
		format_print_integer(get_signed_arg(p), p);
	else if (p->conv_char == 'u' || p->conv_char == 'o' || p->conv_char == 'x')
		format_print_integer(get_unsigned_arg(p), p);
	else if (p->conv_char == 's')
		(p->fl.l || p->fl.ll) ?
		format_print_unistring(va_arg(p->ap, wchar_t*), p) :
		format_print_string(va_arg(p->ap, char*), p);
	else if (p->conv_char == 'p')
		format_print_integer(va_arg(p->ap, size_t), p);
	else if (p->conv_char == 'c')
		format_print_char((p->fl.l || p->fl.ll) ?
		va_arg(p->ap, int) : (char)va_arg(p->ap, int), p);
	else
		format_print_char(conv, p);
}

size_t						fill_flags(const char *s, size_t i, t_printf *p)
{
	if (s[i] == 'l' && s[i + 1] && s[i + 1] == 'l')
		p->fl.ll = 1;
	else if (s[i] == 'h' && s[i + 1] && s[i + 1] == 'h')
		p->fl.hh = 1;
	else if (s[i] == SP)
		p->fl.space = 1;
	else if (s[i] == HS)
		p->fl.hash = 1;
	else if (s[i] == PL)
		p->fl.plus = 1;
	else if (s[i] == MN)
		p->fl.minus = 1;
	else if (s[i] == 'j')
		p->fl.j = 1;
	else if (s[i] == 'z')
		p->fl.z = 1;
	else if (s[i] == 'l')
		p->fl.l = 1;
	else if (s[i] == 'h')
		p->fl.h = 1;
	else
		return (get_width_prec(s, i, p));
	return (1);
}
