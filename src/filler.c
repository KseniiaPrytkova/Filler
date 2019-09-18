#include "filler.h"

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
	free(initial);
	fclose(fptr);
	// system("leaks -quiet test_gnl");
	return (0);
}