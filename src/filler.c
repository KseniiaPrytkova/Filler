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
	str += 8;
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
		if (initial->y_plateau == 0)
			initial->y_plateau = ft_atoi(buff);
		else
			initial->x_plateau = ft_atoi(buff);
		if (!str || *str == ':')
			break;
		str++;
	}
}

int main(void)
{
	t_init *initial = NULL;
	char	*str;
	int ret = 0;
	int i = 0;

	if (!(initial = (t_init *)malloc(sizeof(t_init))))
	{
		perror("Error: ");
		return (0);
	}
	FILE *fptr = fopen("TRUSTEE.txt", "w");

/* INIT */
	get_player_nb(initial);
	fprintf(fptr, "character is: %c\n", initial->figure);

	get_arr_dim(initial);
	fprintf(fptr, "[y (lines)] = %d\n", initial->y_plateau);
	fprintf(fptr, "[x (rows)] = %d\n", initial->x_plateau);
/* LOOP */
	while ((ret = get_next_line(0, &str)))
	{
		fprintf(fptr, "line%d:  %s \n", i, str);
		i++;
		ft_strdel(&str);
	}

	fprintf(fptr, "fffqqq\n");
	fclose(fptr);
	// system("leaks -quiet test_gnl");
	return (0);
}