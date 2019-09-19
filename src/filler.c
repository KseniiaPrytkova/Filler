#include "filler.h"

// TEMP:
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

int main(void)
{
	t_init *initial = NULL;
	char	*str;
	//int ret = 0;
	int i = 0;

	if (!(initial = (t_init *)malloc(sizeof(t_init))))
	{
		perror("Error: ");
		return (0);
	}
	FILE *fptr = fopen("TRUSTEE.txt", "w");

/* INIT */
	get_player_nb(initial);
	get_arr_dim(initial);

	char board[initial->x_plateau][initial->y_plateau];

	while (1)
	{
		get_next_line_fl(0, &str);
		if (str[0] == 'P' && str[1] == 'l') {
			// Ugly hack. If line is "Plateau ..." here.
			ft_strdel(&str);
			get_next_line_fl(0, &str);
		}
		ft_strdel(&str);

		// Read board data line by line into
		// board array.
		i = 0;
		while (i < initial->y_plateau)
		{
			get_next_line_fl(0, &str);

			char *line = ft_strsplit(str, ' ')[1];
			int j = 0;
			while (j < initial->x_plateau)
			{
				board[j][i] = line[j];
				j++;
			}

			ft_strdel(&str);
			i++;
		}

		// Read piece dimensions.
		get_next_line_fl(0, &str);
		int piece_y = ft_atoi(ft_strsplit(str, ' ')[1]);
		int piece_x = ft_atoi(ft_strsplit(str, ' ')[2]);
		initial->x_piece = piece_x;
		initial->y_piece = piece_y;
		ft_strdel(&str);
		fprintf(fptr, "piece y=%d, x=%d\n", piece_y, piece_x);
		fflush(fptr);

		char piece[initial->x_piece][initial->y_piece];

		// Read the piece.
		i = -1;
		while (++i < initial->y_piece)
		{
			get_next_line_fl(0, &str);
			int j = -1;
			while (++j < initial->x_piece)
			{
				piece[j][i] = str[j];
			}
			ft_strdel(&str);
		}

		// Temp: find the coordinates of the first 'O'/'o' on the
		// board.
		i = -1;
		int coord_x, coord_y;
		int q = 0;
		while (++i < initial->y_plateau && !q)
		{
			int j = -1;
			while (++j < initial->x_plateau && !q)
			{
				if (board[j][i] == 'O' ||
					board[j][i] == 'o') {
					coord_x = j;
					coord_y = i;
					q = 1;
				}
			}
		}

		// Print coordinates to stdout for the filler VM.
		fprintf(stdout, "%d %d\n", coord_y, coord_x);
		fflush(stdout);
	}

	fclose(fptr);
	free(initial);
	// system("leaks -quiet test_gnl");
	return (0);
}















