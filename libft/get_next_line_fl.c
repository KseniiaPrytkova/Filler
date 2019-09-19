
#include "libft.h"

char	*string_sub(char *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	string_len;
	size_t	j;

	j = 0;
	substring = NULL;
	string_len = ft_strlen(s);
	if (s[start] == '\n')
		start++;
	if (s && start < string_len + 1 && len < string_len + 1)
	{
		if ((substring = malloc(sizeof(char) * len + 1)) == NULL)
			return (NULL);
		while (start < string_len && j < len)
		{
			substring[j] = s[start];
			start++;
			j++;
		}
		substring[j] = '\0';
	}
	free(s);
	return (substring);
}

int get_next_line_fl(const int fd, char **line)
{
	static char *result_string;
	char buffer[BUFF_SIZE+1];
	int read_bytes = 0;

	if (fd < 0 || fd > MAX_FILES || BUFF_SIZE < 0 || line == NULL)
		return (-1);
	if (!result_string)
		result_string = ft_strnew(1);
	while (!(ft_strchr(result_string, '\n')))
	{
		read_bytes = read(fd, buffer, BUFF_SIZE);
		if (read_bytes == -1)
			return (-1);
		buffer[read_bytes] = '\0';
		result_string = ft_strjoin(result_string, buffer);
		if (read_bytes == 0)
		{
			if (*result_string == '\0')
				return (0);
			else
				break;
		}
	}

	int str_len;

	str_len = ft_strlen(result_string);

	int counter = 0;
	while (*result_string != '\n' && *result_string != '\0')
	{
		result_string++;
		counter++;
	}
	result_string -= counter;
	*line = ft_strnew(counter);
	*line = ft_strncpy(*line, result_string, counter);

	result_string = string_sub(result_string, counter,
							(str_len - counter));

	return (1);
}