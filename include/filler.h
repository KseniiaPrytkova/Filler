#ifndef FILLER_H
# define FILLER_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
// # include "../libft/libft.h"

# define TRUE 1
# define FALSE 0
# define MAX_INT_LEN 10

void perror(char const * s);
typedef struct	s_init
{
	char figure;
	int x_plateau;
	int y_plateau;
	int x_piece;
	int y_piece;
	//char **piece;
} 				t_init;

void get_player_nb(t_init *initial);
void get_arr_dim(t_init *initial);
void read_the_map(t_init *initial, int n, char board[][n], FILE *fptr);
void read_the_piece(t_init **initial, char ***piece, FILE *fptr);

#endif