#include "filler.h"


void placement_alg_density(t_init *initial, int *points)
{
	int avg_x;
	int avg_y;
	int mid_x;
	int mid_y;

	// Check the average x and y and gravitate
	// towards the area with least x/y density.
	avg_x = initial->player_points_x / initial->player_points_nm;
	avg_y = initial->player_points_y / initial->player_points_nm;
	mid_x = initial->x_plateau / 2;
	mid_y = initial->y_plateau / 2;

	// Right field - want to move to the left field.
	if (avg_x >= mid_x)
		*points -= (initial->x_plateau - initial->temp_x_2) * 2; 
	else if (avg_x < mid_x)
		*points -= initial->temp_x_2 * GRAV_FACTOR_X;
	if (avg_y >= mid_y)
		*points -= (initial->y_plateau - initial->temp_y_2) * 2;
	else if (avg_y < mid_y)
		*points -= initial->temp_y_2 * GRAV_FACTOR_Y;
}

int placement_alg_heatmap(t_init *initial, char **piece, int n,
	char board[][n], int points)
{
	int i;
	int j;
	int nm_player;

	nm_player = 0;
	i = -1;
	while (++i < initial->y_piece)
	{
		j = -1;
		while (++j < initial->x_piece)
		{
			if (piece[i][j] == '*')
			{
				// Player
				if (board[initial->temp_x_2+j][initial->temp_y_2+i] == -99)
				{
					if (++nm_player > 1)
						return POINTS_INF;
					continue;
				}
				// Enemy
				else if (board[initial->temp_x_2+j][initial->temp_y_2+i] == 99)
					return POINTS_INF;
				else
					points += board[initial->temp_x_2+j][initial->temp_y_2+i];
			}
		}
	}
	if (nm_player != 1)
		return POINTS_INF;
	return points;
}

int placement_alg(t_init *initial, char **piece, int n,
	char board[][n])
{
	int points;

	// Check the border limits.
	if ((initial->temp_x_2 + initial->x_piece > initial->x_plateau) ||
		(initial->temp_y_2 + initial->y_piece > initial->y_plateau))
		return POINTS_INF;

    points = 0;
	placement_alg_density(initial, &points);
	points = placement_alg_heatmap(initial, piece, n, board, points);

	return points;
}