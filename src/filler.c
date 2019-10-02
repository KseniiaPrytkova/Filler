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
		fprintf(fptr, "we are pl № 1; USE: %c\n", initial->figure);
	else
		fprintf(fptr, "we are pl № 2; USE: %c\n", initial->figure);
	/* ------- */
	get_arr_dim(initial);
	/* del me */
	fprintf(fptr, "Y = %d; X = %d\n",initial->y_plateau, initial->x_plateau);
	/* ------- */

	char board[initial->x_plateau][initial->y_plateau];

	while (1)
	{
		read_the_map(initial, initial->y_plateau, board, fptr);
		read_the_piece(&initial, &piece, fptr);

		create_hot_board(initial, initial->y_plateau, board, fptr);

		// Temp: find the coordinates of the first 'O'/'o' on the
		// board.
		// i = -1;
		// int coord_x, coord_y;
		// int q = 0;
		// while (++i < initial->y_plateau && !q)
		// {
		// 	int j = -1;
		// 	while (++j < initial->x_plateau && !q)
		// 	{
		// 		if (board[j][i] == 'O' ||
		// 			board[j][i] == 'o') {
		// 			coord_x = j;
		// 			coord_y = i;
		// 			q = 1;
		// 		}
		// 	}
		// }
		// Print coordinates to stdout for the filler VM.
		fprintf(fptr, "------------------------------------!!!PRELIMINARY_X:!!![%d]; !!!PRELIMINARY_Y:!!! [%d]\n\n",initial->preliminary_x, initial->preliminary_y);
		fflush(fptr);

		fprintf(stdout, "%d %d\n", initial->preliminary_y, initial->preliminary_x);
		fflush(stdout);
	}
	fclose(fptr);
	piece_cleaner(initial, piece);
	free(initial);
	// system("leaks -quiet test_gnl");
	return (0);
}















