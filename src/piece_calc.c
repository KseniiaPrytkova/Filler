#include "filler.h"



void piece_calc_points_handle(t_init *initial, char **piece, int n,
	char board[][n], int *points_best)
{
	int points_new;

	points_new = placement_alg(initial, piece, n, board);
	if (points_new < (*points_best))
	{
		*points_best = points_new;
		initial->temp_x_3 = initial->temp_x_2;
		initial->temp_y_3 = initial->temp_y_2;
	}
}

int piece_calc_points(t_init *initial, char **piece, int n, char board[][n])
{
	int x;
	int y;
	int points_best;

    points_best = POINTS_INF;
    y = initial->temp_y - (initial->y_piece - 1) - 1;
	while (++y <= initial->temp_y)
	{
		if (y < 0) continue;
		x = initial->temp_x - (initial->x_piece - 1) - 1;
		while (++x <= initial->temp_x)
		{
			if (x < 0) continue;
			initial->temp_x_2 = x;
			initial->temp_y_2 = y;
			piece_calc_points_handle(initial, piece, n, board, &points_best);
		}
	}
	initial->temp_x = initial->temp_x_3;
	initial->temp_y = initial->temp_y_3;
	return points_best;
}