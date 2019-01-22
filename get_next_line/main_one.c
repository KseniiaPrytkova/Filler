#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int		main(int argc, char *argv[])
{
	int	fd1;
	// char	*file_name;
	char	*line;
	int	ret;

	fd1 = open(argv[1], O_RDONLY);
	// file_name = NULL;
	if (argc > 1)
	{
		// file_name = argv[1];
		while ((ret = get_next_line(fd1, &line)))
		{
			printf("%s\n", line);
			ft_strdel(&line);
		}
		close(fd1);
	}
	system("leaks -quiet test_gnl");
	return (0);
}
