#include "filler.h"
#include <stdio.h>

int main(__attribute__((unused))int argc, __attribute__((unused))char *argv[])
{
	char	*str;
	get_next_line(0, &str);
	if (str) {
		printf("first line: |%s| \n", str);
		printf("0 0");
		free(str);
	}
	return (0);
}