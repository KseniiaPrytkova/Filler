/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_print_unistring.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 04:40:26 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/20 19:30:51 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char			count_act_bytes(const int c)
{
	const char			charlen = count_onebits(c);

	if (charlen < 8)
		return (1);
	else if (charlen < 12)
		return (2);
	else if (charlen < 17)
		return (3);
	else if (charlen < 33)
		return (4);
	return (0);
}

static inline size_t	ft_unistrlen(const wchar_t *s)
{
	size_t				i;
	size_t				active_bytes_passed;

	if (!s)
		return (6);
	i = 0;
	active_bytes_passed = 0;
	while (s[i])
		active_bytes_passed += count_act_bytes(s[i++]);
	return (active_bytes_passed);
}

static inline size_t	obtain_delim(const wchar_t *s, t_printf *p)
{
	size_t				i;
	size_t				active_bytes_passed;

	i = 0;
	active_bytes_passed = 0;
	while (active_bytes_passed <= p->fl.precision)
		active_bytes_passed += count_act_bytes(s[i++]);
	active_bytes_passed -= count_act_bytes(s[i - 1]);
	return (active_bytes_passed);
}

static inline void		fprint_str(const wchar_t *s, size_t len, t_printf *p)
{
	size_t				i;
	size_t				delimeter;
	size_t				active_bytes_passed;

	i = 0;
	active_bytes_passed = 0;
	if (p->fl.is_precision && p->fl.precision < len)
	{
		delimeter = obtain_delim(s, p);
		while (active_bytes_passed < delimeter)
		{
			format_print_char(s[i], p);
			active_bytes_passed += count_act_bytes(s[i++]);
		}
	}
	else
		while (s[i])
			format_print_char(s[i++], p);
}

void					format_print_unistring(const wchar_t *s, t_printf *p)
{
	const size_t		len = ft_unistrlen(s);
	const char			char_width = ((p->fl.zero) ? '0' : SP);
	const wchar_t		nullstr[] = L"(null)";
	size_t				min_len;

	if (!s)
		s = nullstr;
	min_len =
	(p->fl.is_precision && p->fl.precision < len) ? obtain_delim(s, p) : len;
	while (!p->fl.minus && p->fl.width && p->fl.width-- > min_len)
		add_ch_tobuf(char_width, p);
	fprint_str(s, len, p);
	while (p->fl.minus && p->fl.width && p->fl.width-- > min_len)
		add_ch_tobuf(SP, p);
}
