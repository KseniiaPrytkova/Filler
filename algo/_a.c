# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
#include <fcntl.h>
#include <sys/types.h>

typedef struct	s_init
{
	char figure;
	int x_plateau;
	int y_plateau;
	int x_piece;
	int y_piece;

	int opp_x_curr;
	int opp_y_curr;

	int opp_x_next;
	int opp_y_next;

	int is_one_piece;
	int i_was;
	int heat;
	//char **piece;
} 				t_init;

void count_dim(t_init *initial, int fd1, char *line)
{
		int i = 0;
		char buff[42];
		int ret = 0;
		initial->x_plateau = 0;
		initial->y_plateau = 0;

		ret = get_next_line_fl(fd1, &line);
		line += 8;

		while (line)
		{
			i = 0;
			while (line && *line != ' ' && *line != ':')
			{
				buff[i] = *line;
				i++;
				line++;
			}
			buff[i] = '\0';
			if (initial->y_plateau == 0)
				initial->y_plateau = ft_atoi(buff);
			else
				initial->x_plateau = ft_atoi(buff);
			if (!line || *line == ':')
				break;
			line++;
		}
		printf("Y = %d; X = %d\n",initial->y_plateau, initial->x_plateau);
}

void read_map(t_init *initial, char *str, int n, char board[][n], int fd1)
{
	int i = 0;
	int j = 0;
	int catch = 0;
		// Read board data line by line into
		// board array.
		while (i < initial->y_plateau)
		{
			get_next_line_fl(fd1, &str);
			// char *line = ft_strsplit(str, ' ')[1];
			j = 0;
			while (j < initial->x_plateau)
			{
				board[j][i] = str[j];
				if ((board[j][i] == 'X' || board[j][i] == 'x') && !catch)
				{
					// if (catch == 0)
					// {
					// 	initial->opp_x_min = j;
					// 	initial->opp_y_min = i;
					// 	catch = 1;
					// }
					// else
					// {
					// 	initial->opp_x_max = j;
					// 	initial->opp_y_max = i;
					// }
					initial->opp_x_curr = j;
					initial->opp_y_curr = i;
					catch = 1;

				}
				j++;
			}
			ft_strdel(&str);
			i++;
		}
/* print arr */
	printf("I WILL PRINT YOUR ARRAY\n");
	i = 0;
	while (i < initial->y_plateau)
	{
		j = 0;
		while (j < initial->x_plateau)
			{
				printf("%c", board[j][i]);
				j++;
			}
			printf("\n");
		i++;
	}
	printf("curr OPP COORD: Ymin = %d Xmin = %d\n", initial->opp_y_curr, initial->opp_x_curr);
	// printf("%c\n", board[initial->opp_x_min][initial->opp_y_min]);
}

void pr_arr(t_init *initial, int del_x, int del_y)
{
	char *s1;
	char *s2;
	s1 = ft_itoa(del_x);
	s2 = ft_itoa(del_y);

	if (initial->heat == 100)
	{
		printf("\033[0;31m");

		if (strlen(s1) == 2)
			printf("[%s]",s1);
		if (strlen(s2) == 2)
			printf("[%s]",s2);
		if (strlen(s1) == 1)
			printf("[ %s]",s1);
		if (strlen(s2) == 1)
			printf("[ %s]",s2);

		printf("\033[0m");
		initial->heat = 0;
	}
	else if (initial->heat == 55)
	{
		printf("\033[0;35m");

		if (strlen(s1) == 2)
			printf("[%s]",s1);
		if (strlen(s2) == 2)
			printf("[%s]",s2);
		if (strlen(s1) == 1)
			printf("[ %s]",s1);
		if (strlen(s2) == 1)
			printf("[ %s]",s2);

		printf("\033[0m");
		initial->heat = 0;
	}
	else if (initial->heat == 42)
	{
		printf("\033[0;32m");

		if (strlen(s1) == 2)
			printf("[%s]",s1);
		if (strlen(s2) == 2)
			printf("[%s]",s2);
		if (strlen(s1) == 1)
			printf("[ %s]",s1);
		if (strlen(s2) == 1)
			printf("[ %s]",s2);

		printf("\033[0m");
		initial->heat = 0;
	}
	else
	{
		printf("\033[0;34m");
		if (strlen(s1) == 2)
			printf("[%s]",s1);
		if (strlen(s2) == 2)
			printf("[%s]",s2);
		if (strlen(s1) == 1)
			printf("[ %s]",s1);
		if (strlen(s2) == 1)
			printf("[ %s]",s2);
		printf("\033[0m");
		initial->heat = 0;
	}	
}


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
		fprintf(stderr, "----->>>>t_x = [%d]; t_y = [%d]\n", temp_j, temp_i);
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

/* -------------------------------------------------------------------------- */
int main(int argc, char *argv[])
{
	t_init *initial = NULL;
	int	fd1;
	char	*file_name;
	char	*line;
	int	ret;

	int i = 0;
	int j = 0;

	int del_x = 0;
	int del_y = 0;

	if (!(initial = (t_init *)malloc(sizeof(t_init))))
	{
		printf("_bad_malloc(structure)\n");
		return (-1);
	}
	initial->is_one_piece = -1;
	initial->i_was = 0;
	// int first = 0;

	initial->opp_x_curr = 0;
	initial->opp_y_curr = 0;

	initial->opp_x_next = 0;
	initial->opp_y_next = 0;
	fd1 = open(argv[1], O_RDONLY);
	if (argc > 1)
	{
		file_name = NULL;
		file_name = argv[1];
		
		count_dim(initial, fd1, line);
		char board[initial->x_plateau][initial->y_plateau];
		read_map(initial, line, initial->y_plateau, board, fd1);
		/* algo */
		while (i < initial->y_plateau)
		{
			if (i <= 9)
				printf("line:%d ", i);
			else
				printf("line:%d", i);
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
					printf("\033[0;33m");
					printf("[ %c]", board[j][i]);
					printf("[ %c]", board[j][i]);
					printf("\033[0m");
					board[j][i] = 99;
/* ----------------------------------------*/
					// catch_next();
					
					if (j == initial->opp_x_curr && i == initial->opp_y_curr && initial->is_one_piece == -1)
					{
						// if (initial->is_one_piece == -1 )
						// {
								
						fprintf(stderr, "in if\n");
						catch_next(initial, i, j, initial->y_plateau, board);
						fprintf(stderr, "here_AFTER: next_x:%d next_y:%d | is_one = %d\n", initial->opp_x_next, initial->opp_y_next, initial->is_one_piece);
						// }
					
					}
					if (initial->opp_y_next == initial->opp_y_curr)
					{
						initial->opp_x_curr = initial->opp_x_next;
						initial->opp_y_curr = initial->opp_y_next;
					}
					j++;
					printf(" ");
				}
				if ( board[j][i] == 'O' || board[j][i] == 'o')
				{
					printf("\033[0;33m");
					printf("[ %c]", board[j][i]);
					printf("[ %c]", board[j][i]);
					printf("\033[0m");
					board[j][i] = -99;
					j++;
					printf(" ");
				}
				else
				{
					// if ((j <= initial->opp_x_min && i <= initial->opp_y_min) || 
					// 	(initial->opp_x_max == 0 && initial->opp_y_max == 0))
					// {
						if ((del_x = j - initial->opp_x_curr) < 0)
							del_x *= -1;
						if ((del_y = i - initial->opp_y_curr) < 0)
							del_y *= -1;
						// del_x = j - initial->opp_x_min ;
						// del_y = i - initial->opp_y_min ;
					// }
					// else
					// {
					// 	initial->opp_x_min +=1;
					// 	if ((del_x = j - initial->opp_x_max) < 0)
					// 			del_x *= -1;
					// 	if ((del_y = i - initial->opp_y_max) < 0)
					// 			del_y *= -1;
					// 	// del_x = j - initial->opp_x_max ;
					// 	// del_y = i - initial->opp_y_max ;
					// }
					
					// if ((del_x = j - initial->opp_x_min) < 0)
					// 	del_x *= -1;
					// if ((del_y = i - initial->opp_y_min) < 0)
					// 	del_y *= -1;

					if ((board[j][i] = del_x + del_y) < 1)
						board[j][i] *= -1;
					// board[j][i] = (del_x + del_y);

					// if ((board[j][i] <= initial->opp_x_max - initial->opp_x_min) &&
					// 	((board[j][i] <= initial->opp_y_max - initial->opp_y_min)))
					// {
					// 	initial->heat = 100;
					// 	pr_arr(initial, del_x, del_y);
					// }
					// else if (board[j][i] == 2 || board[j][i] == 3)
					// {
					// 	initial->heat = 55;
					// 	pr_arr(initial, del_x, del_y);
					// }
					// else if (board[j][i] == 4 || board[j][i] == 5)
					// {
					// 	initial->heat = 42;
					// 	pr_arr(initial, del_x, del_y);
					// }
					// else
						pr_arr(initial, del_x, del_y);

					
					fprintf(stderr, "currX:[%d]; currY: [%d]\n", initial->opp_x_curr, initial->opp_y_curr );
					j++;
					printf(" ");
				}
			}
			printf("\n\n");
			i++;
		}
/* prrrrrriiiiiiiinnnnnnttt */
		printf("\nI WILL PRINT YOUR ARRAY\n");
		i = 0;
		while (i < initial->y_plateau)
		{
			if (i <= 9)
				printf("line:%d ", i);
			else
				printf("line:%d", i);
			j = 0;
			while (j < initial->x_plateau)
			{
				if (board[j][i] >= 0)
				{
					if (board[j][i] == 99)
					{
						printf("\033[0;33m");
						printf("[+%d]", board[j][i]);
						printf("\033[0m");
					}
					else if ((board[j][i] <= 9 && board[j][i] >= 0) ||
						(board[j][i] <= 0 && board[j][i] >= -9) )
						printf("[ +%d]", board[j][i]);
					else
						printf("[+%d]", board[j][i]);
				}
				else
				{
					if (board[j][i] == -99)
					{
						printf("\033[0;33m");
						printf("[%d]", board[j][i]);
						printf("\033[0m");
					}
					else if ((board[j][i] <= 9 && board[j][i] >= 0) ||
						(board[j][i] <= 0 && board[j][i] >= -9) )
						printf("[ %d]", board[j][i]);
					else
						printf("[%d]", board[j][i]);
				}
				j++;
			}
			printf("\n");
			i++;
		}

		/* ---- */
		close(fd1);
	}
	
	return (0);
}

// gcc _a.c -I../libft/ -L../libft/ -lft

// ./a.out _map 2>mylogfile