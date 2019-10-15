#include "filler.h"


int catch_next_handle(t_init *initial, int n, char board[][n], int i, int *j)
{
    if ((board[*j][i] == initial->enemy_figure) ||
        (board[*j][i] == initial->enemy_figure - 32))
    {
        initial->opp_x_next = *j;
        initial->opp_y_next = i;
        initial->is_one_piece = -1;
        return (0);
    }
    (*j)++;
    return (1);
}

void catch_next_final(t_init *initial)
{
	if (initial->is_one_piece == -1)
		initial->i_was++;
	else
		initial->is_one_piece = TRUE;
}

void catch_next(t_init *initial, int i, int j, int n, char board[][n])
{
	int temp_i;
	int temp_j;
	int first;

	temp_i = i;
	temp_j = j + 1;
	first = 0;
	initial->is_one_piece = FALSE;
	while (temp_i < initial->y_plateau)
	{
		if (first)
			temp_j = 0;
		while(temp_j < initial->x_plateau)
		{ 
			first = 1;
			if (!catch_next_handle(initial, n, board, temp_i, &temp_j)) break;
		}
		if (initial->is_one_piece == -1)
			break;
		temp_i++;
	}
	catch_next_final(initial);
}
