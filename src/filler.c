#include "filler.h"

#include <stdint.h>
#include <inttypes.h>

static void init_structure(t_init *initial)
{
	initial->x_plateau = 0;
	initial->y_plateau = 0;

	initial->is_one_piece = -1;
	initial->i_was = 0;

	initial->opp_x_next = 0;
	initial->opp_y_next = 0;

	initial->preliminary_x = 0;
	initial->preliminary_y = 0;

	initial->definitive_x = 0;
	initial->definitive_y = 0;
	initial->is_first_iteration = TRUE;
}

void piece_cleaner(t_init *initial, char **piece)
{
	int i;

	i = 0;
	while(i < initial->y_piece && piece[i])
	{
		free (piece[i]);
		i++;
	}
	free(piece);
}

// x and y is here the coordinates where to place the piece.
int piece_calc_points_bis(t_init *initial, char **piece, int n, char board[][n], int x, int y)
{
	int i = -1;
	int j;
	int points = 0;
	int nm_player = 0;

	// Check the border limits.
	if (x + initial->x_piece > initial->x_plateau)
	{
		return POINTS_INF;
	}
	if (y + initial->y_piece > initial->y_plateau)
	{
		return POINTS_INF;
	}


	// Check the average x and y and gravitate
	// towards the area with least x/y density.
	int avg_x = initial->player_points_x / initial->player_points_nm;
	int avg_y = initial->player_points_y / initial->player_points_nm;
	int mid_x = initial->x_plateau / 2;

	// Right field - want to move to the left field.
	if (avg_x >= mid_x)
	{
		points -= (initial->x_plateau - x) * 2; 
	}
	else if (avg_x < mid_x)
	{
		points -= x * GRAV_FACTOR_X;
	}
	int mid_y = initial->y_plateau / 2;
	if (avg_y >= mid_y)
	{
		points -= (initial->y_plateau - y) * 2;
	}
	else if (avg_y < mid_y)
	{
		points -= y * GRAV_FACTOR_Y;
	}


	// HEAT MAP.
	while (++i < initial->y_piece)
	{
		j = -1;
		while (++j < initial->x_piece)
		{
			if (piece[i][j] == '*')
			{
				// Player.
				if (board[x+j][y+i] == -99)
				{
					if (++nm_player > 1)
					{
						return POINTS_INF;
					}
					continue;
				}
				// Enemy.
				else if (board[x+j][y+i] == 99)
				{
					return POINTS_INF;
				}
				else
				{
					points += board[x+j][y+i];
				}
			}
		}
	}
	if (nm_player != 1) {
		return POINTS_INF;
	}

	return points;
}

int piece_calc_points(t_init *initial, char **piece, int n, char board[][n])
{
	// start in the upper left corner and loop down.
	int x;
	int y = initial->temp_y - (initial->y_piece - 1) - 1;

	int x_best;
	int y_best;

	int points_best = POINTS_INF;
	int points_new;

	while (++y <= initial->temp_y)
	{
		if (y < 0)
			continue;
		x = initial->temp_x - (initial->x_piece - 1) - 1;
		while (++x <= initial->temp_x)
		{
			if (x < 0)
				continue;

			points_new = piece_calc_points_bis(initial, piece, n, board,
				x, y);
			if (points_new < points_best)
			{
				points_best = points_new;
				x_best = x;
				y_best = y;
			}
		}
	}
	initial->temp_x = x_best;
	initial->temp_y = y_best;
	return points_best;
}

int piece_get_placement(t_init *initial, char **piece, int n, char board[][n])
{
	int i = -1;
	int j;
	int points_best = POINTS_INF;
	int points_new;

	initial->definitive_x = 0;
	initial->definitive_y = 0;

	while (++i < initial->y_plateau)
	{
		j = -1;
		while (++j < initial->x_plateau)
		{
			// Player point.
			if (board[j][i] == -99)
			{
				initial->temp_x = j;
				initial->temp_y = i;
				points_new = piece_calc_points(initial, piece, n, board);
				if (points_new < points_best)
				{
					points_best = points_new;
					initial->definitive_x = initial->temp_x;
					initial->definitive_y = initial->temp_y;
				}
			}
		}
	}
	return (1);
}

int main(void)
{
	t_init *initial = NULL;
	char **piece = NULL;

	if (!(initial = (t_init *)malloc(sizeof(t_init))))
	{
		perror("Error: ");
		return (0);
	}

	init_structure(initial);

	get_player_nb(initial);
	if (initial->figure == 'o')
		initial->enemy_figure = 'x';
	else if (initial->figure == 'x')
		initial->enemy_figure = 'o';
	get_arr_dim(initial);

	char board[initial->x_plateau][initial->y_plateau];
	while (1)
	{
		if (!read_the_map(initial, initial->y_plateau, board))
		{
			break;
		}
		read_the_piece(&initial, &piece);
		create_hot_board(initial, initial->y_plateau, board);
		if (!piece_get_placement(initial, piece, initial->y_plateau, board))
		{
			fprintf(stdout, "0 0\n");
			fflush(stdout);
			break;
		}

		// Print coordinates to stdout for the filler VM.
		fprintf(stdout, "%d %d\n", initial->definitive_y, initial->definitive_x);
		fflush(stdout);
	}
	if (piece != NULL)
		piece_cleaner(initial, piece);
	free(initial);
	// system("leaks -quiet test_gnl");
	return (0);
}















