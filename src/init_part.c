#include "filler.h"


void get_player_nb(t_init *initial)
{
	char *str;
	char figure;
	int ret;

	if (!(ret = get_next_line_fl(0, &str)))
	{
		perror("Error with reading the line [1] (gnl): ");
	}
	if (str[10] == '1')
		figure = 'o';
	else if (str[10] == '2')
		figure = 'x';
	else
	{
		perror("Error with reading the player number: ");
		figure = '\0';
	}
	initial->figure = figure;
	ft_strdel(&str);
}

static void dim_reader(char *str, int *x, int *y)
{
	int i = 0;
	char buff[MAX_INT_LEN];

	while (str)
	{
		i = 0;
		while (str && *str != ' ' && *str != ':')
		{
			buff[i] = *str;
			i++;
			str++;
		}
		buff[i] = '\0';
		if (*y == 0)
			*y = ft_atoi(buff);
		else
			*x = ft_atoi(buff);
		if (!str || *str == ':')
			break;
		str++;
	}
}

void get_arr_dim(t_init *initial)
{
	int ret;
	char *str;

	if (!(ret = get_next_line_fl(0, &str)))
	{
		perror("Error with reading the line [2] (gnl): ");
	}

	str += 8;
	dim_reader(str, &initial->x_plateau, &initial->y_plateau);
}

int read_the_map(t_init *initial, int n, char board[][n], FILE *fptr)
{
	int i;
	int j;
	int catch;
	char *str = NULL;

	i = 0;
	j = 0;
	catch = 0;

		get_next_line_fl(0, &str);
		if (str == NULL)
		{
			// a null string from the filter vm
			// ends the game.
			return (0);
		}
		else if (str[0] == 'P' && str[1] == 'l')
		{
			// If line is "Plateau ..." here.
			ft_strdel(&str);
			get_next_line_fl(0, &str);
		}
		else if (str[0] == ' ' && str[1] == ' ' && str[2] == ' ')
		{
			
		}
		else
		{
			return (0);
		}
		ft_strdel(&str);
		// Read board data line by line into
		// board array.
		while (i < initial->y_plateau)
		{
			get_next_line_fl(0, &str);
			char *line = ft_strsplit(str, ' ')[1];
			int j = 0;
			while (j < initial->x_plateau)
			{
				board[j][i] = line[j];
				if (((board[j][i] == initial->enemy_figure) || (board[j][i] == initial->enemy_figure - 32)) && !catch)
				// if ((board[j][i] == 'X' || board[j][i] == 'x') && !catch)
				{
					initial->opp_x_curr = j;
					initial->opp_y_curr = i;
					catch = 1;
				}
				j++;
			}
			ft_strdel(&str);
			i++;
		}

	return (1);
}

void read_the_piece(t_init **initial, char ***piece, FILE *fptr)
{
	int i;
	int j;
	char *str = NULL;

	// Read piece dimensions.
	get_next_line_fl(0, &str);
	(*initial)->y_piece = ft_atoi(ft_strsplit(str, ' ')[1]);
	(*initial)->x_piece = ft_atoi(ft_strsplit(str, ' ')[2]);
	ft_strdel(&str);

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