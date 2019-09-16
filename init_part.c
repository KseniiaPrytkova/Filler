#include "filler.h"

void get_player_nb(t_init *initial)
{
	char *str;
	// int pn = 0;
	char figure;
	int ret;

	if (!(ret = get_next_line(0, &str)))
	{
		perror("Error with reading the line [1] (gnl): ");
	}
	// fprintf(fptr, "%c%c\n", str[9], str[10]);
	// if ((str[10] == 1) ? 1 : 2)
	if (str[10] == '1')
		figure = 'o';
	else if (str[10] == '2')
		figure = 'x';
	else
	// if (str[10] != '1' && str[10] != '2')
	{
		perror("Error with reading the player number: ");
		figure = '\0';
	}
	// fprintf(fptr, "character is: and pl_nb is: %c %c\n", figure, str[10]);
	initial->figure = figure;
	free(str);
	// return (figure);
}

static void dim_reader(char *str, int x, int y)
{
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
		if (y == 0)
			y = ft_atoi(buff);
		else
			x = ft_atoi(buff);
		if (!str || *str == ':')
			break;
		str++;
	}
}

void get_arr_dim(t_init *initial)
{
	int ret;
	char *str;
	char buff[MAX_INT_LEN];
	int i = 0;

	initial->x_plateau = 0;
	initial->y_plateau = 0;
	if (!(ret = get_next_line(0, &str)))
	{
		perror("Error with reading the line [2] (gnl): ");
	}
	// str += 8;
	dim_reader((str + 8), x_plateau, y_plateau);
}