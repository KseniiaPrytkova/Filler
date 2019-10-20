/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 04:40:33 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/20 19:32:03 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			add_ch_tobuf(const int c, t_printf *p)
{
	if ((p->i + 1) == BUFFER_SIZE)
	{
		p->to_out += write(p->outfd, p->buf, p->i);
		p->i = 0;
	}
	p->buf[p->i++] = c;
}

int				ft_printf(const char *convstr, ...)
{
	size_t				i;
	static t_printf		p;
	static char			buf[BUFFER_SIZE];

	ft_bzero(&p, sizeof(p));
	p.outfd = 1;
	p.buf = buf;
	va_start(p.ap, convstr);
	i = 0;
	while (convstr[i])
	{
		if (convstr[i] == '%')
			i = parse_conv_string(convstr, i + 1, &p);
		else
			add_ch_tobuf(convstr[i++], &p);
	}
	va_end(p.ap);
	if (p.i > 0)
		p.to_out += write(p.outfd, p.buf, p.i);
	return (p.to_out);
}

int				ft_dprintf(int fd, const char *convstr, ...)
{
	size_t				i;
	static t_printf		p;
	static char			buf[BUFFER_SIZE];

	ft_bzero(&p, sizeof(p));
	p.outfd = fd;
	p.buf = buf;
	va_start(p.ap, convstr);
	i = 0;
	while (convstr[i])
	{
		if (convstr[i] == '%')
			i = parse_conv_string(convstr, i, &p);
		else
			add_ch_tobuf(convstr[i++], &p);
	}
	va_end(p.ap);
	if (p.i > 0)
		p.to_out += write(p.outfd, p.buf, p.i);
	return (p.to_out);
}

size_t			get_unsigned_arg(t_printf *p)
{
	if (p->fl.z)
		return (va_arg(p->ap, size_t));
	else if (p->fl.j)
		return (va_arg(p->ap, uintmax_t));
	else if (p->fl.ll)
		return (va_arg(p->ap, unsigned long long));
	else if (p->fl.l)
		return (va_arg(p->ap, unsigned long));
	else if (p->fl.hh)
		return ((unsigned char)va_arg(p->ap, unsigned int));
	else if (p->fl.h)
		return ((unsigned short)va_arg(p->ap, unsigned int));
	else
		return (va_arg(p->ap, unsigned int));
}

size_t			get_signed_arg(t_printf *p)
{
	ssize_t				tmp;
	size_t				utmp;

	if (p->fl.z)
		tmp = va_arg(p->ap, ssize_t);
	else if (p->fl.j)
		tmp = va_arg(p->ap, intmax_t);
	else if (p->fl.ll)
		tmp = va_arg(p->ap, long long);
	else if (p->fl.l)
		tmp = va_arg(p->ap, long);
	else if (p->fl.hh)
		tmp = (char)va_arg(p->ap, int);
	else if (p->fl.h)
		tmp = (short)va_arg(p->ap, int);
	else
		tmp = va_arg(p->ap, int);
	if (tmp < 0)
	{
		p->fl.is_neg = 1;
		utmp = -tmp;
	}
	else
		utmp = tmp;
	return (utmp);
}
