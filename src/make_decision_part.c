/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_decision_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:49:58 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/15 21:15:57 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	piece_get_placement_handle(t_init *initial, char **piece, int n,
	char board[][n], int *points_best)
{
	int	points_new;

	points_new = piece_calc_points(initial, piece, n, board);
	if (points_new < (*points_best))
	{
		*points_best = points_new;
		initial->definitive_x = initial->temp_x;
		initial->definitive_y = initial->temp_y;
	}
}

void	piece_get_placement(t_init *initial, char **piece, int n, char board[][n])
{
	int	i;
	int	j;
	int	points_best;

	initial->definitive_x = 0;
	initial->definitive_y = 0;
	i = -1;
	points_best = POINTS_INF;
	while (++i < initial->y_plateau)
	{
		j = -1;
		while (++j < initial->x_plateau)
		{
			if (board[j][i] == -99) // Player point
			{
				initial->temp_x = j;
				initial->temp_y = i;
				piece_get_placement_handle(initial, piece, n, board,
					&points_best);
			}
		}
	}
}
