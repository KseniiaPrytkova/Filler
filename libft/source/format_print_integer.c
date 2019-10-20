/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_print_integer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 04:40:13 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/20 19:30:45 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MNSIZE			64

static inline void		ft_utoa_base_stack(const size_t value, const int base
	, char r[], t_printf *p)
{
	int					j;
	size_t				b;

	j = 1;
	b = value;
	while (b /= base)
		j++;
	b = value;
	if (!value)
		r[0] = '0';
	while (b)
	{
		r[--j] = (p->fl.is_bigx) ? "0123456789ABCDEF"[b % base]
		: "0123456789abcdef"[b % base];
		b /= base;
	}
}

static inline int		form_str_by_flag(const char r[]
	, const size_t fstr_len, t_printf *p)
{
	if ((p->conv_char == 'd' || p->conv_char == 'i') && p->fl.is_neg)
		add_ch_tobuf(MN, p);
	else if ((p->conv_char == 'd' || p->conv_char == 'i') && p->fl.plus
	&& !p->fl.is_neg)
		add_ch_tobuf(PL, p);
	else if ((p->conv_char == 'd' || p->conv_char == 'i') && p->fl.space)
		add_ch_tobuf(SP, p);
	else if (p->conv_char == 'o' && p->fl.hash &&
	*r && *r != '0' && p->fl.precision <= fstr_len)
		add_ch_tobuf('0', p);
	else if ((p->conv_char == 'x' && p->fl.hash && *r && *r != '0') ||
	p->conv_char == 'p')
	{
		add_ch_tobuf('0', p);
		add_ch_tobuf(p->fl.is_bigx ? 'X' : 'x', p);
	}
	return (0);
}

static inline void		write_fstr_tobuf(
	char r[], const size_t obj_len, const size_t lenm, t_printf *p)
{
	size_t			i;
	const char		minlchr = ((p->fl.zero && !p->fl.is_precision) ? '0' : SP);
	const int		to_print_flags =

	((p->fl.width > lenm && p->fl.zero) ? form_str_by_flag(r, obj_len, p) : 1);
	while (!p->fl.minus && p->fl.width && p->fl.width-- > lenm)
		add_ch_tobuf(minlchr, p);
	to_print_flags ? form_str_by_flag(r, obj_len, p) : 0;
	while (p->fl.precision && p->fl.precision-- > obj_len)
		add_ch_tobuf('0', p);
	i = 0;
	while (r[i])
		add_ch_tobuf(r[i++], p);
	while (p->fl.minus && p->fl.width && p->fl.width-- > lenm)
		add_ch_tobuf(SP, p);
}

static inline int		num_spaces(const char r[], const size_t fstr_len,
	const t_printf *p)
{
	if ((p->conv_char == 'x' && p->fl.hash && r[0] != '0')
	|| p->conv_char == 'p')
		return (2);
	else if (((p->conv_char == 'd' || p->conv_char == 'i') && p->fl.is_neg)
	|| ((p->conv_char == 'd'
	|| p->conv_char == 'i') && p->fl.plus && !p->fl.is_neg)
	|| ((p->conv_char == 'd' || p->conv_char == 'i') && p->fl.space)
	|| (p->conv_char == 'o' && p->fl.hash && r[0] != '0'
	&& p->fl.precision <= fstr_len))
		return (1);
	return (0);
}

void					format_print_integer(const size_t d, t_printf *p)
{
	static char	r[MNSIZE];
	size_t		fstr_len;
	size_t		min_len;

	ft_bzero(&r, sizeof(char) * MNSIZE);
	if (p->conv_char == 'x' || p->conv_char == 'p')
		ft_utoa_base_stack(d, 16, r, p);
	else if (p->conv_char == 'o')
		ft_utoa_base_stack(d, 8, r, p);
	else if (p->conv_char == 'u' || p->conv_char == 'd' || p->conv_char == 'i')
		ft_utoa_base_stack(d, 10, r, p);
	if (d == 0 && p->conv_char == 'o' && p->fl.hash)
		r[0] = '0';
	else if (d == 0 && p->fl.is_precision && p->fl.precision == 0)
		r[0] = 0;
	fstr_len = ft_strlen(r);
	min_len = ((p->fl.precision > fstr_len) ?
	p->fl.precision : fstr_len) + num_spaces(r, fstr_len, p);
	write_fstr_tobuf(r, fstr_len, min_len, p);
}
