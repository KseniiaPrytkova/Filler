/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_print_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 04:32:39 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/20 19:30:43 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define NM4				4034953344
#define NM3				14712960
#define NM2				49280
#define MSN				26
#define MSN1			24
#define RS				29
#define RS1				28
#define RS2				27
#define BS				6
#define BS1				12
#define BS2				16

static inline void		add_twobytech_tobuf(const unsigned int c, t_printf *p)
{
	const unsigned char	o2 = (c << MSN) >> MSN;
	const unsigned char	o1 = ((c >> BS) << RS2) >> RS2;
	const unsigned int	m2 = NM2;

	add_ch_tobuf(((m2 >> (BS + 2)) | o1), p);
	add_ch_tobuf((((m2 << MSN1) >> MSN1) | o2), p);
}

static inline void		add_threebytech_tobuf(const unsigned int c, t_printf *p)
{
	const unsigned char	o3 = (c << MSN) >> MSN;
	const unsigned char	o2 = ((c >> BS) << MSN) >> MSN;
	const unsigned char	o1 = ((c >> BS1) << RS1) >> RS1;
	const unsigned int	m3 = NM3;

	add_ch_tobuf((m3 >> BS2) | o1, p);
	add_ch_tobuf(((m3 << BS2) >> MSN1) | o2, p);
	add_ch_tobuf(((m3 << MSN1) >> MSN1) | o3, p);
}

static inline void		add_fourbytech_tobuf(const unsigned int c, t_printf *p)
{
	const unsigned char	o4 = (c << MSN) >> MSN;
	const unsigned char	o3 = ((c >> BS) << MSN) >> MSN;
	const unsigned char	o2 = ((c >> BS1) << MSN) >> MSN;
	const unsigned char	o1 = ((c >> (BS2 + 2)) << RS) >> RS;
	const unsigned int	m4 = NM4;

	add_ch_tobuf((m4 >> MSN1) | o1, p);
	add_ch_tobuf(((m4 << (BS + 2)) >> MSN1) | o2, p);
	add_ch_tobuf(((m4 << BS2) >> MSN1) | o3, p);
	add_ch_tobuf(((m4 << MSN1) >> MSN1) | o4, p);
}

char					count_onebits(const int c)
{
	unsigned char		i;

	i = 1;
	while (c >> i && i < MAXNSIZE)
		i++;
	return (i == MAXNSIZE ? 0 : i);
}

void					format_print_char(const int c, t_printf *p)
{
	char				mlenchar;
	const unsigned char	active_bytes = count_act_bytes(c);
	const char			charlen = count_onebits(c);

	if (p->conv_char != 's')
	{
		mlenchar = ((p->fl.zero) ? '0' : SP);
		while (!p->fl.minus && p->fl.width && p->fl.width-- > active_bytes)
			add_ch_tobuf(mlenchar, p);
	}
	if (charlen < 8 && MB_CUR_MAX > 0)
		add_ch_tobuf(c, p);
	else if (charlen < 12 && MB_CUR_MAX > 1)
		add_twobytech_tobuf(c, p);
	else if (charlen < 17 && MB_CUR_MAX > 2)
		add_threebytech_tobuf(c, p);
	else if (charlen < 33 && MB_CUR_MAX > 3)
		add_fourbytech_tobuf(c, p);
	if (p->conv_char != 's')
		while (p->fl.minus && p->fl.width && p->fl.width-- > active_bytes)
			add_ch_tobuf(SP, p);
}
