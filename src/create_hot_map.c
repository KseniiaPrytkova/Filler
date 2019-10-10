#include "filler.h"


void catch_next(t_init *initial, int i, int j, int n, char board[][n])
{
	int temp_i = i;
	int temp_j = j;
	int first = 0;

	temp_j +=1;
	initial->is_one_piece = FALSE;
	while (temp_i < initial->y_plateau)
	{
		if (first)
			temp_j = 0;
		while(temp_j < initial->x_plateau)
		{ 
			first = 1;
			if ((board[temp_j][temp_i] == initial->enemy_figure) ||
				(board[temp_j][temp_i] == initial->enemy_figure - 32))
			{
				initial->opp_x_next = temp_j;
				initial->opp_y_next = temp_i;
				initial->is_one_piece = -1;
				break;
			}
			temp_j++;
		}
		if (initial->is_one_piece == -1)
			break ;
		temp_i++;
	}

	if (initial->is_one_piece == -1)
		initial->i_was++;
	else
		initial->is_one_piece = TRUE;
}

static int count_delta_x(t_init *initial, int delta_x, int j)
{
	if ((delta_x = j - initial->opp_x_curr) < 0)
		delta_x *= -1;

	return (delta_x);
}

static int count_delta_y(t_init *initial, int delta_y, int i)
{
	if ((delta_y = i - initial->opp_y_curr) < 0)
		delta_y *= -1;

	return (delta_y);
}

static void take_care_of_yourself(t_init *initial, int i, int j)
{
	int delta_x = 0;
	int delta_y = 0;

	int prelim_delta_x = 0;
	int prelim_delta_y = 0;
	
	if (initial->is_first_iteration == TRUE)
	{
		initial->preliminary_x = j;
		initial->preliminary_y = i;
		initial->is_first_iteration = FALSE;
	}
	else
	{
		delta_x = count_delta_x(initial, delta_x, j);
		delta_y = count_delta_y(initial, delta_y, i);

		prelim_delta_x = count_delta_x(initial, prelim_delta_x, initial->preliminary_x);
		prelim_delta_y = count_delta_y(initial, prelim_delta_y, initial->preliminary_y);

		if ((delta_x + delta_y) <= (prelim_delta_x + prelim_delta_y))
		{
			initial->preliminary_x = j;
			initial->preliminary_y = i;
		}	
	}				
}

void create_hot_board(t_init *initial, int n, char board[][n])
{
	int i;
	int j;
	int delta_x = 0;
	int delta_y = 0;

	initial->player_points_nm = 0;
	initial->player_points_x = 0;
	initial->player_points_y = 0;

	initial->is_one_piece = -1;
	initial->i_was = 0;
	i = -1;
	while (++i < initial->y_plateau)
	{
		if (initial->i_was > 0)
		{
			initial->opp_x_curr = initial->opp_x_next;
			initial->opp_y_curr = initial->opp_y_next;
		}
		j = -1;
		while (++j < initial->x_plateau)
		{
			if ( (board[j][i] == initial->enemy_figure) || (board[j][i] == initial->enemy_figure - 32))
			{
				board[j][i] = 99;

				if (j == initial->opp_x_curr && i == initial->opp_y_curr && initial->is_one_piece == -1)
				{
					catch_next(initial, i, j, initial->y_plateau, board);
				}

				if (initial->opp_y_next == initial->opp_y_curr)
				{
					initial->opp_x_curr = initial->opp_x_next;
					initial->opp_y_curr = initial->opp_y_next;
				}
			}
			else if ( (board[j][i] == initial->figure) || (board[j][i] == initial->figure - 32))
			{
				board[j][i] = -99;
				take_care_of_yourself(initial, i, j);

				initial->player_points_nm++;
				initial->player_points_x += j;
				initial->player_points_y += i;
			}
			else
			{
				if ((board[j][i] = (delta_x = count_delta_x(initial, delta_x, j)) + (delta_y = count_delta_y(initial, delta_y, i))) < 1)
					board[j][i] *= -1;
			}
		}
	}
}