# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define MAX_INT_LEN 10

typedef struct	s_init
{
	char figure;
	int x;
	int y;
} 				t_init;

void get_arr_dim(t_init *initial, char *str)
{
	char buff[MAX_INT_LEN];
	int i = 0;


	initial->x = 0;
	initial->y = 0;
	printf("str = %s\n",str );
	printf("len1 = %lu\n", strlen(str) );
	// if (!(ret = get_next_line(0, &str)))
	// {
	// 	perror("Error with reading the line [2] (gnl): ");
	// }
	str += 8;
	printf("->%s\n", str);
	printf("len2 = %lu\n", strlen(str) );
	while (str)
	{
		printf("--%s\n", str );
		i = 0;
		while (str && *str != ' ' && *str != ':')
		{
			printf("it %d: %s\n", i, str );
			buff[i] = *str;
			i++;
			str++;
		}
		buff[i] = '\0';
		printf("buff ====== %s\n", buff );
		if (initial->x == 0)
			initial->x = atoi(buff);
		else
			initial->y = atoi(buff);
		if (!str || *str == ':')
			break;
		str++;
	}
}

int main(void)
{
	t_init *initial = NULL;
	char *str = "Plateau 15 17:";

	if (!(initial = (t_init *)malloc(sizeof(t_init))))
	{
		perror("Error: ");
		return (0);
	}
	get_arr_dim(initial, str);
	printf("[x] = %d\n", initial->x);
	printf("[y] = %d\n", initial->y);
	return (0);
}