/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hot_map_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:49:58 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/19 20:55:08 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	take_care_of_yourself_not_first_iter(t_init *initial, int delta_x,
		int delta_y)
{
	delta_x = count_delta_x(initial, delta_x, initial->temp_y);
	delta_y = count_delta_y(initial, delta_y, initial->temp_x);
	initial->temp_x_2 = count_delta_x(initial, initial->temp_x_2,
		initial->preliminary_x);
	initial->temp_y_2 = count_delta_y(initial, initial->temp_y_2,
		initial->preliminary_y);
	if ((delta_x + delta_y) <= (initial->temp_x_2 + initial->temp_y_2))
	{
		initial->preliminary_x = initial->temp_y;
		initial->preliminary_y = initial->temp_x;
	}
}

void	take_care_of_yourself(t_init *initial, int i, int j)
{
	int	delta_x;
	int	delta_y;

	delta_x = 0;
	delta_y = 0;
	initial->temp_x_2 = 0;
	initial->temp_y_2 = 0;
	if (initial->is_first_iteration == TRUE)
	{
		initial->preliminary_x = j;
		initial->preliminary_y = i;
		initial->is_first_iteration = FALSE;
	}
	else
	{
		initial->temp_x = i;
		initial->temp_y = j;
		take_care_of_yourself_not_first_iter(initial, delta_x, delta_y);
	}
}
