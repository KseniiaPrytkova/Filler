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
		piece_get_placement(initial, piece, initial->y_plateau, board);

		// Print coordinates to stdout for the filler VM.
		fprintf(stdout, "%d %d\n", initial->definitive_y, initial->definitive_x);
		fflush(stdout);
	}
	if (piece != NULL)
		piece_cleaner(initial, piece);
	free(initial);
	return (0);
}