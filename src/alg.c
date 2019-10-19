/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:49:58 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/15 20:55:52 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	placement_alg_density(t_init *initial, int *points)
{
	int	avg_x;
	int	avg_y;
	int	mid_x;
	int	mid_y;

	/* Check the average x and y and gravitate */
	/* towards the area with least x/y density. */
	avg_x = initial->player_points_x / initial->player_points_nm;
	avg_y = initial->player_points_y / initial->player_points_nm;
	mid_x = initial->x_plateau / 2;
	mid_y = initial->y_plateau / 2;
	/* Right field - want to move to the left field. */
	if (avg_x >= mid_x)
		*points -= (initial->x_plateau - initial->temp_x_2) * 2;
	else if (avg_x < mid_x)
		*points -= initial->temp_x_2 * GRAV_FACTOR_X;
	if (avg_y >= mid_y)
		*points -= (initial->y_plateau - initial->temp_y_2) * 2;
	else if (avg_y < mid_y)
		*points -= initial->temp_y_2 * GRAV_FACTOR_Y;
}

int		placement_alg_heatmap_handle(t_init *initial, int *nm_player,
		int *points)
{
	/* Player */
	if (initial->board[initial->temp_x_2 + initial->temp_y_5]
		[initial->temp_y_2 + initial->temp_x_5] == -99)
	{
		(*nm_player) += 1;
		if ((*nm_player) > 1)
			return (0);
	}
	/* Enemy */
	else if (initial->board[initial->temp_x_2 + initial->temp_y_5]
		[initial->temp_y_2 + initial->temp_x_5] == 99)
		return (0);
	else
		(*points) += initial->board[initial->temp_x_2 + initial->temp_y_5]
		[initial->temp_y_2 + initial->temp_x_5];
	return (1);
}

int		check_nm_player(int nm_player, int points)
{
	if (nm_player != 1)
		return (POINTS_INF);
	return (points);
}

int		placement_alg_heatmap(t_init *initial, char **piece, int points)
{
	int	i;
	int	j;
	int	nm_player;

	nm_player = 0;
	i = -1;
	while (++i < initial->y_piece)
	{
		j = -1;
		while (++j < initial->x_piece)
		{
			if (piece[i][j] == '*')
			{
				initial->temp_x_5 = i;
				initial->temp_y_5 = j;
				if (!placement_alg_heatmap_handle(initial, &nm_player,
							&points))
					return (POINTS_INF);
			}
		}
	}
	return (check_nm_player(nm_player, points));
}

int		placement_alg(t_init *initial, char **piece)
{
	int	points;

	/* Check the border limits. */
	if ((initial->temp_x_2 + initial->x_piece > initial->x_plateau) ||
		(initial->temp_y_2 + initial->y_piece > initial->y_plateau))
		return (POINTS_INF);
	points = 0;
	placement_alg_density(initial, &points);
	points = placement_alg_heatmap(initial, piece, points);
	return (points);
}
