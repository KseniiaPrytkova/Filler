#include "filler.h"

void catch_next(t_init *initial, int i, int j, int n, char board[][n])
{
	int temp_i = i;
	int temp_j = j;
	int first = 0;

temp_j +=1;
initial->is_one_piece = 0;
	while (temp_i < initial->y_plateau)
	{
		if (first)
			temp_j = 0;
		while(temp_j < initial->x_plateau)
		{ 
			first = 1;
			if (board[temp_j][temp_i] == 'X' || board[temp_j][temp_i] == 'x')
			{
				fprintf(stderr, "\ninto!!!\n");
				initial->opp_x_next = temp_j;
				initial->opp_y_next = temp_i;
				fprintf(stderr, "x:%d, y:%d | x_next:%d, y_next:%d\n",temp_j, temp_i, initial->opp_x_next, initial->opp_y_next);
				initial->is_one_piece = -1;
				break;
			}
			temp_j++;
		}
		if (initial->is_one_piece == -1)
			break ;
		temp_i++;
	}
	// initial->is_one_piece = 1;
	fprintf(stderr, "here_BEFORE: curr_x:%d curr_y:%d | is_one = %d\n", initial->opp_x_curr, initial->opp_y_curr, initial->is_one_piece);
	if (initial->is_one_piece == -1)
	{
		initial->i_was++;
		
	}
	else
		initial->is_one_piece = 1;
}

void create_hot_board(t_init *initial, int n, char board[][n], FILE *fptr)
{
	fprintf(fptr, "i am in hot!!\n\n" );
	fflush(fptr);

	int i = 0;
	int j = 0;

	int delta_x = 0;
	int delta_y = 0;

	
	initial->is_one_piece = -1;
	initial->i_was = 0;

	// initial->opp_x_curr = 0;
	// initial->opp_y_curr = 0;

	initial->opp_x_next = 0;
	initial->opp_y_next = 0;

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
			if (board[j][i] == 'X' || board[j][i] == 'x')
			{
				board[j][i] = 99;
/* ----------------------------------------*/
				if (j == initial->opp_x_curr && i == initial->opp_y_curr && initial->is_one_piece == -1)
				{
								
					fprintf(fptr, "in if\n");
					fflush(fptr);
					catch_next(initial, i, j, initial->y_plateau, board);
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
			if ( board[j][i] == 'O' || board[j][i] == 'o')
			{
				board[j][i] = -99;
				j++;
			}
			else
			{
				if ((delta_x = j - initial->opp_x_curr) < 0)
					delta_x *= -1;
				if ((delta_y = i - initial->opp_y_curr) < 0)
					delta_y *= -1;
				if ((board[j][i] = delta_x + delta_y) < 1)
					board[j][i] *= -1;					
				fprintf(fptr, "currX:[%d]; currY: [%d]\n", initial->opp_x_curr, initial->opp_y_curr );
				fflush(fptr);
				j++;
			}
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