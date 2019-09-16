#include "filler.h"

char get_player_nb(void)
{
	char *str;
	// int pn = 0;
	char figure;
	int ret;

	if (!(ret = get_next_line(0, &str)))
	{
		perror("Error with reading the line (gnl): ");
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
	free(str);
	return (figure);
}

int main(void)
{
	char	*str;
	int ret = 0;
	char figure;
	int i = 0;

	FILE *fptr = fopen("TRUSTEE.txt", "w");
	figure = get_player_nb();
	fprintf(fptr, "character is: %c\n", figure);
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