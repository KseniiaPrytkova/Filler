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

	int opp_x_min;
	int opp_y_min;
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
				if (board[j][i] == 'X' || board[j][i] == 'x')
				{
					initial->opp_x_min = j;
					initial->opp_y_min = i;
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
	printf("MIN OPP COORD: Ymin = %d Xmin = %d\n", initial->opp_y_min, initial->opp_x_min);
	// printf("%c\n", board[initial->opp_x_min][initial->opp_y_min]);
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
	initial->opp_x_min = 0;
	initial->opp_y_min = 0;
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
			while (j < initial->x_plateau)
			{
				if (board[j][i] == 'X' || board[j][i] == 'x')
				{
					printf("\033[1;31m");
					printf("[ %c ]", board[j][i]);
					printf("[ %c ]", board[j][i]);
					printf("\033[0m");
					board[j][i] = 99;
					j++;
				}
				if ( board[j][i] == 'O' || board[j][i] == 'o')
				{
					printf("\033[1;31m");
					printf("[ %c ]", board[j][i]);
					printf("[ %c ]", board[j][i]);
					printf("\033[0m");
					board[j][i] = -99;
					j++;
				}
				else
				{
					del_x = j - initial->opp_x_min;
					del_y = i - initial->opp_y_min;
					board[j][i] = (del_x + del_y);
					char *s1;
					char *s2;
					s1 = ft_itoa(del_x);
					s2 = ft_itoa(del_y);

					if (strlen(s1) == 2)
						printf("[ %s]",s1);
					if (strlen(s2) == 2)
						printf("[ %s]",s2);
					if (strlen(s1) == 1)
						printf("[  %s]",s1);
					if (strlen(s2) == 1)
						printf("[  %s]",s2);
				
					if (strlen(s1) == 3)
						printf("[%s]",s1);
					if (strlen(s2) == 3)
						printf("[%s]",s2);
					
					j++;
				}
			}
			printf("\n\n\n");
			i++;
		}
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
						printf("\033[1;31m");
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
						printf("\033[1;31m");
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