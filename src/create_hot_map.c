#include "filler.h"

void catch_next(t_init *initial, int i, int j, int n, char board[][n], FILE *fptr)
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
			// if (board[temp_j][temp_i] == 'X' || board[temp_j][temp_i] == 'x')
			if ((board[temp_j][temp_i] == initial->enemy_figure) ||
				(board[temp_j][temp_i] == initial->enemy_figure - 32))
			{
				// fprintf(stderr, "\ninto!!!\n");
				// fflush(fptr);
				initial->opp_x_next = temp_j;
				initial->opp_y_next = temp_i;
				// fprintf(stderr, "x:%d, y:%d | x_next:%d, y_next:%d\n",temp_j, temp_i, initial->opp_x_next, initial->opp_y_next);
				// fflush(fptr);
				initial->is_one_piece = -1;
				break;
			}
			temp_j++;
		}
		if (initial->is_one_piece == -1)
			break ;
		temp_i++;
	}

	// fprintf(stderr, "here_BEFORE: curr_x:%d curr_y:%d | is_one = %d\n", initial->opp_x_curr, initial->opp_y_curr, initial->is_one_piece);
	// fflush(fptr);
	if (initial->is_one_piece == -1)
	{
		initial->i_was++;
		
	}
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
		// fprintf(fptr, "pre X:[%d]; pre Y: [%d]\n",initial->preliminary_x, initial->preliminary_y);
		// fflush(fptr);
	}
	else
	{
		// fprintf(fptr, "opp_y_curr====== %d\n", initial->opp_y_curr);
		// fflush(fptr);
		delta_x = count_delta_x(initial, delta_x, j);
		// fprintf(fptr, "del_x====== %d\n", delta_x);
		// fflush(fptr);
		
		// fprintf(fptr, "opp_x_curr====== %d\n", initial->opp_x_curr);
		// fflush(fptr);
		delta_y = count_delta_y(initial, delta_y, i);
		// fprintf(fptr, "del_y====== %d\n", delta_y);
		// fflush(fptr);

		prelim_delta_x = count_delta_x(initial, prelim_delta_x, initial->preliminary_x);
		prelim_delta_y = count_delta_y(initial, prelim_delta_y, initial->preliminary_y);

		if ((delta_x + delta_y) <= (prelim_delta_x + prelim_delta_y))
		{
			initial->preliminary_x = j;
			initial->preliminary_y = i;
		}	
	}				
}

void create_hot_board(t_init *initial, int n, char board[][n], FILE *fptr)
{
	fprintf(fptr, "i am in hot!!\n\n" );
	fflush(fptr);


	fprintf(fptr, "currX:[%d]; currY: [%d]\n", initial->opp_x_curr, initial->opp_y_curr );
	fflush(fptr);
	int i = 0;
	int j = 0;

	int delta_x = 0;
	int delta_y = 0;

	initial->player_points_nm = 0;
	initial->player_points_x = 0;
	initial->player_points_y = 0;
	initial->enemy_points_nm = 0;
	initial->enemy_points_x = 0;
	initial->enemy_points_y = 0;

	initial->is_one_piece = -1;
	initial->i_was = 0;
	while (i < initial->y_plateau)
	{
		j = 0;
		if (initial->i_was > 0)
		{
			initial->opp_x_curr = initial->opp_x_next;
			initial->opp_y_curr = initial->opp_y_next;
		}
		while (j < initial->x_plateau)
		{
			// if (board[j][i] == 'X' || board[j][i] == 'x')
			// fprintf(fptr, "currX:[%d]; currY: [%d]\n", initial->opp_x_curr, initial->opp_y_curr );
			// fflush(fptr);
			if ( (board[j][i] == initial->enemy_figure) || (board[j][i] == initial->enemy_figure - 32))
			{
				board[j][i] = 99;
				// fprintf(fptr, "							enemy_x:%d enemy_y:%d\n", j, i);
				// fflush(fptr);
				// fprintf(fptr, "1)) ..currX:[%d]; currY: [%d]; is_1_piece == %d\n", initial->opp_x_curr, initial->opp_y_curr, initial->is_one_piece );
				// fflush(fptr);
/* ----------------------------------------*/

				initial->enemy_points_nm++;
				initial->enemy_points_x += j;
				initial->enemy_points_y += i;

				if (j == initial->opp_x_curr && i == initial->opp_y_curr && initial->is_one_piece == -1)
				{
								
					fprintf(fptr, "in if\n");
					fflush(fptr);

					catch_next(initial, i, j, initial->y_plateau, board, fptr);

					fprintf(fptr, "here_AFTER: next_x:%d next_y:%d | is_one = %d\n", initial->opp_x_next, initial->opp_y_next, initial->is_one_piece);
					fflush(fptr);
				}

				if (initial->opp_y_next == initial->opp_y_curr)
				{
					initial->opp_x_curr = initial->opp_x_next;
					initial->opp_y_curr = initial->opp_y_next;
				}
				j++;
			}
			else if ( (board[j][i] == initial->figure) || (board[j][i] == initial->figure - 32))
			{
				board[j][i] = -99;
				take_care_of_yourself(initial, i, j);

				initial->player_points_nm++;
				initial->player_points_x += j;
				initial->player_points_y += i;

				// board[j][i] = -99;
				// if (initial->is_one_piece == -1)
				// {
				// 	initial->preliminary_x = j;
				// 	initial->preliminary_y = i;
					// fprintf(fptr, "pre X_:[%d]; pre Y_: [%d]\n",initial->preliminary_x, initial->preliminary_y);
					// fflush(fptr);
				// }
				// else
				// {
				// 	initial->preliminary_x = j;
				// 	initial->preliminary_y = i;
				// 	if ()
				// }
				j++;
			}
			else
			{
				if ((board[j][i] = (delta_x = count_delta_x(initial, delta_x, j)) + (delta_y = count_delta_y(initial, delta_y, i))) < 1)
					board[j][i] *= -1;

				// if ((delta_x = j - initial->opp_x_curr) < 0)
				// 	delta_x *= -1;
				// if ((delta_y = i - initial->opp_y_curr) < 0)
				// 	delta_y *= -1;
				// if ((board[j][i] = delta_x + delta_y) < 1)
				// 	board[j][i] *= -1;
				// fprintf(fptr, "currX:[%d]; currY: [%d]\n", initial->opp_x_curr, initial->opp_y_curr );
				// fflush(fptr);				
				j++;
			}
			// j++;
		}
		i++;
	}

/* print */


		i = 0;
		while (i < initial->y_plateau)
		{
			if (i <= 9)
			{
				fprintf(fptr, "line:%d ", i);
				fflush(fptr);
			}
			else
			{
				fprintf(fptr, "line:%d", i);
				fflush(fptr);
			}
			j = 0;
			while (j < initial->x_plateau)
			{
				if (board[j][i] >= 0)
				{
					if (board[j][i] == 99)
					{
						fprintf(fptr,"[+%d]", board[j][i]);
						fflush(fptr);
					}
					else if ((board[j][i] <= 9 && board[j][i] >= 0) ||
						(board[j][i] <= 0 && board[j][i] >= -9) )
					{
						fprintf(fptr,"[ +%d]", board[j][i]);
						fflush(fptr);
					}
					else
					{
						fprintf(fptr,"[+%d]", board[j][i]);
						fflush(fptr);
					}
				}
				else
				{
					if (board[j][i] == -99)
					{
						fprintf(fptr,"[%d]", board[j][i]);
						fflush(fptr);
					}
					else if ((board[j][i] <= 9 && board[j][i] >= 0) ||
						(board[j][i] <= 0 && board[j][i] >= -9) )
					{
						fprintf(fptr,"[ %d]", board[j][i]);
						fflush(fptr);
					}
					else
					{
						fflush(fptr);
						fprintf(fptr,"[%d]", board[j][i]);
					}
				}
				j++;
			}
			fprintf(fptr,"\n");
			i++;
		}

/*------*/
}