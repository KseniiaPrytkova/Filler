#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int		main(int argc, char *argv[])
{
	int	fd1;
	int	fd2;
	char	*line;
	int	ret;

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	if (argc == 3)
	{
		while ((ret = get_next_line(fd1, &line)))
		{
			printf("%s\n", line);
			ft_strdel(&line);
			while ((ret = get_next_line(fd2, &line)))
			{
				printf("%s\n", line);
				ft_strdel(&line);
			}
		}
	}
	close(fd1);
	close(fd2);
	system("leaks -quiet test_gnl_1");
	return (0);
}
