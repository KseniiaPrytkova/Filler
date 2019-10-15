/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_delta.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:49:58 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/15 20:58:02 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	count_delta_x(t_init *initial, int delta_x, int j)
{
	if ((delta_x = j - initial->opp_x_curr) < 0)
		delta_x *= -1;
	return (delta_x);
}

int	count_delta_y(t_init *initial, int delta_y, int i)
{
	if ((delta_y = i - initial->opp_y_curr) < 0)
		delta_y *= -1;
	return (delta_y);
}
