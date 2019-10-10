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
	int i;
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