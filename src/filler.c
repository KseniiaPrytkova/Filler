#include "filler.h"

// TEMP:
// #include <time.h>
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
int piece_calc_points_bis(t_init *initial, char **piece, int n, char board[][n], int x, int y, FILE *fptr)
{
	int i = -1;
	int j;
	int points = 0;
	int nm_player = 0;

	// piece: i = y, j = x
	// board: x = y, y = x

	//if (x + initial->y_piece > initial->x_plateau)
	if (x + initial->x_piece > initial->x_plateau)
	{
		//fprintf(fptr, "  x bound: %d + %d = %d > %d -> return 99\n",
		//	x, initial->y_piece, x + initial->y_piece,
		//	initial->x_plateau);
		//fflush(fptr);
		return 99;
	}
	//if (y + initial->x_piece > initial->y_plateau)
	if (y + initial->y_piece > initial->y_plateau)
	{
		//fprintf(fptr, "  y bound: %d + %d = %d > %d -> return 99\n",
		//	y, initial->x_piece, y + initial->x_piece,
		//	initial->y_plateau);
		//fflush(fptr);
		return 99;
	}

	while (++i < initial->y_piece)
	{
		j = -1;
		while (++j < initial->x_piece)
		{
			//fprintf(fptr, "  piece %d, %d: %d (%c)\n", i, j, piece[i][j], piece[i][j]);
			//fflush(fptr);

			// Player.
			if (board[x+j][y+i] == -99 &&
				piece[i][j] == '*')
			{
				//fprintf(fptr, "  encountered player, piece here: %c\n",
				//	piece[i][j]);
				//fflush(fptr);
				if (++nm_player > 1) {
					//fprintf(fptr, "  return 99 because of >1 player\n");
					//fflush(fptr);
					return 99;
				}
			}
			// Enemy.
			else if (board[x+j][y+i] == 99 &&
				piece[i][j] == '*')
			{
				//fprintf(fptr, "  return 99 because of enemy\n");
				//fflush(fptr);
				return 99;
			}
			else if (board[x+j][y+i] != 99 &&
				board[x+j][y+i] != -99)
			{
				//fprintf(fptr, "  adding %d to points (from board %d, %d)\n", board[x+j][y+i], x+j, y+i);
				//fflush(fptr);
				points += board[x+j][y+i];
			}
		}
	}
	if (nm_player != 1) {
		//fprintf(fptr, "  nm_player=%d -> return 99\n", nm_player);
		//fflush(fptr);
		return 99;
	}

	return points;
}

int piece_calc_points(t_init *initial, char **piece, int n, char board[][n], FILE *fptr)
{
	// start in the upper left corner and loop down.
	int x;
	int y = initial->temp_y - (initial->y_piece - 1) - 1;

	int x_best;
	int y_best;

	int points_best = 99;
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
				x, y, fptr);
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

void piece_get_placement(t_init *initial, char **piece, int n, char board[][n], FILE *fptr)
{
	int i = -1;
	int j;
	int points_best = 99;
	int points_new;

	while (++i < initial->y_plateau)
	{
		j = -1;
		while (++j < initial->x_plateau)
		{
			if ((board[j][i] == -99))
			{
				initial->temp_x = j;
				initial->temp_y = i;
				points_new = piece_calc_points(initial, piece, n, board, fptr);
				if (points_new < points_best)
				{
					points_best = points_new;
					initial->definitive_x = initial->temp_x;
					initial->definitive_y = initial->temp_y;
				}
			}
		}
	}
}

int main(void)
{
	t_init *initial = NULL;
	char **piece = NULL;
	// int i = 0;

	if (!(initial = (t_init *)malloc(sizeof(t_init))))
	{
		perror("Error: ");
		return (0);
	}
	FILE *fptr = fopen("TRUSTEE.txt", "w");

	init_structure(initial);

/* INIT */
	get_player_nb(initial);
	/* del me */
	if (initial->figure == 'o')
	{
		fprintf(fptr, "we are pl № 1; USE: %c\n", initial->figure);
		fprintf(fptr, "or: %c\n", initial->figure - 32 );
		initial->enemy_figure = 'x';
	}
	else if (initial->figure == 'x')
	{
		fprintf(fptr, "we are pl № 2; USE: %c\n", initial->figure);
		fprintf(fptr, "or: %c\n", initial->figure - 32 );
		initial->enemy_figure = 'o';
	}
	/* ------- */
	get_arr_dim(initial);
	/* del me */
	fprintf(fptr, "Y = %d; X = %d\n",initial->y_plateau, initial->x_plateau);
	/* ------- */

	char board[initial->x_plateau][initial->y_plateau];

	while (1)
	{
		if (!read_the_map(initial, initial->y_plateau, board, fptr))
		{
			return (0);
		}
		read_the_piece(&initial, &piece, fptr);

		create_hot_board(initial, initial->y_plateau, board, fptr);

		piece_get_placement(initial, piece, initial->y_plateau, board, fptr);

		// Print coordinates to stdout for the filler VM.
		fprintf(fptr, "------------------------------------!!!PRELIMINARY_X:!!![%d]; !!!PRELIMINARY_Y:!!! [%d]\n\n",initial->definitive_x, initial->definitive_y);
		fflush(fptr);

		//fprintf(stdout, "%d %d\n", initial->preliminary_y, initial->preliminary_x);
		fprintf(stdout, "%d %d\n", initial->definitive_y, initial->definitive_x);
		fflush(stdout);
	}
	fclose(fptr);
	piece_cleaner(initial, piece);
	free(initial);
	// system("leaks -quiet test_gnl");
	return (0);
}















