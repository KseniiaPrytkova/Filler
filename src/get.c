#include "filler.h"


void read_the_map_loop_set(t_init *initial, int j, int i, int *catch)
{
	initial->opp_x_curr = j;
	initial->opp_y_curr = i;
	*catch = 1;
}

void read_the_map_loop(t_init *initial, int n, char board[][n])
{
	int i;
	int j;
	int catch;
    char *str;

	i = -1;
	catch = 0;
	str = NULL;
	while (++i < initial->y_plateau)
	{
		get_next_line_fl(0, &str);
		char *line = ft_strsplit(str, ' ')[1];
		j = -1;
		while (++j < initial->x_plateau)
		{
			board[j][i] = line[j];
			if (((board[j][i] == initial->enemy_figure) ||
				(board[j][i] == initial->enemy_figure - 32)) && !catch)
				read_the_map_loop_set(initial, j, i, &catch);
		}
		ft_strdel(&str);
	}
}

int read_the_map(t_init *initial, int n, char board[][n])
{
	char *str;

	str = NULL;
	get_next_line_fl(0, &str);
	if (str == NULL)
		return (0);
	else if (str[0] == 'P' && str[1] == 'l')
	{
		// If line is "Plateau ..." here.
		ft_strdel(&str);
		get_next_line_fl(0, &str);
	}
	else if (str[0] != ' ' && str[1] != ' ' && str[2] != ' ')
		return (0);
	ft_strdel(&str);
	read_the_map_loop(initial, n, board);
	return (1);
}

void read_the_piece_alloc(t_init **initial, char ***piece)
{
	int i;
	int j;
	char *str;

	str = NULL;
	*piece = (char**)malloc((*initial)->y_piece * sizeof(char*));
	i = -1;
	while (++i < (*initial)->y_piece)
	{
		(*piece)[i] = (char*)malloc((*initial)->x_piece * sizeof(char));
	}
	i = -1;
	while (++i < (*initial)->y_piece)
	{
		get_next_line_fl(0, &str);
		j = -1;
		while (++j < (*initial)->x_piece)
		{
			(*piece)[i][j] = str[j];
		}
		ft_strdel(&str);
	}
}

void read_the_piece(t_init **initial, char ***piece)
{
	char *str;

	str = NULL;
	// Read piece dimensions.
	get_next_line_fl(0, &str);
	(*initial)->y_piece = ft_atoi(ft_strsplit(str, ' ')[1]);
	(*initial)->x_piece = ft_atoi(ft_strsplit(str, ' ')[2]);
	ft_strdel(&str);

	read_the_piece_alloc(initial, piece);
}