# get_next_line

This project is about function, that reads a line ending with a newline character from a file descriptor. The return value can be 1, 0 or -1 depending on whether a line has been read, when the reading has been completed, or if an error has happened respectively. Function get_next_line returns its result without ’\n’.

Calling this function in a loop will then allow you to read the text available on a file descriptor one line at a time until the end of the text, no matter the size of either the text or one of its lines.

The implementation of this project can be conditionally divided into 2 stages (solely from my point of view):

## 1) read the whole file into a string (how to?)

Initially it was not obvious to me that reading the file into a string can not be done directly (and without using standard functions). What i mean? It is impossible for example to output the whole string directly on the standart output if you are not allowed to use printf(). In this case you need to use putcar() (this fn simply uses system call write(2)) in the loop and output the string character by character (in the context of C language). So.. Due to the fact that it was necessary to come up with an algorithm for the realization of this task (putting the file into the string), I could not find a specific answer in Google (I wanted to find something like step-by-step instruction). For those who will face such a problem in the future and will be confused, I dicided to write my own instruction, perhaps it will make someone happier or at least improve digestion.

### 1.1 main.c
Here we get the value of the file descriptor by opening the file and call the function i_am_string_maker() where we first transmit the obtained value of FD.
``` C
__main.c__

#include "i_am_string_maker.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>

int	main(int argc, char *argv[])
{
	int	fd;
	char	*file_name;

	file_name = NULL;
	if (argc == 2)
		file_name = argv[1];
	else
		printf("ERROR:there are more than one file as an input!\n");
	fd = open(file_name, O_RDONLY);
	i_am_string_maker(fd);
	return (0);
}
```

The function must be prototyped as follow :
``` C
int i_am_string_maker(const int fd);
```

### 1.2 string_maker.c

#### 1.2.1 step 1
First of all lets's declare a string (using pointer), in which we will put the contents of the file:
``` C
static char	*result_string;
```
and launch our first working function for file reading i_am_for_reading();

#### 1.2.2 step 2
So the function i_am_for_reading() takes as parameters the file descriptor and some pointer to a memory area, which is empty now (or there is rubbish now, doesn't matter). We need a file descriptor for the function read(). The number of bytes that can be read during one iteration doesn't have fixed value, so u can change it (of course it must be more than 0). U can find it in i_am_string_maker.h and it's look like:
``` C
# define BUFF_SIZE 2
```
In this case we will read 2 bytes for 1 iteration. We will do it into intermediate buffer **buffer_for_read** with size **BUFF_SIZE + 1**.
Next, we need to copy the buffer data to the final string **result_string**. Since we do not know the size of the file, we do not know the size of the **result_string**, and we use malloc - asking the system for memory, which corresponds to the size of bytes read. If **result_string** is already empty (means this is the first occurrence into the function), we should use bzero() first to avoid rubbish in the memory area that we requested and then apply memcpy() function, which will copy buffer's contents into **result_string**. When **result_string** is not empty anymore next 2 bytes that we will read from file and write to the buffer will simply need to be attached to existing content. We will use **join_me()** for these purposes.
``` C
__string_maker.c__

#include "i_am_string_maker.h"

char		*join_me(char *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result_string;

	s1_len = 0;
	s2_len = 0;
	result_string = NULL;
	if (s1 != NULL && s2 != NULL)
	{
		s1_len = ft_strlen(s1);
		s2_len = ft_strlen(s2);
		result_string = ft_strnew(s1_len + s2_len + 1);
		if (result_string)
		{
			ft_strncpy(result_string, s1, s1_len);
			free(s1);
			ft_strncpy((result_string + s1_len), s2, s2_len);
		}
		else
			return (NULL);
	}
	return (result_string);
}

char		*i_am_for_reading(int fd, char *result_string)
{
	int			read_bytes;
	char			buffer_for_read[BUFF_SIZE + 1];
	int			counter;
	size_t			res_str_len;

	res_str_len = 0;
	while ((read_bytes = read(fd, buffer_for_read, BUFF_SIZE)) > 0)
	{
		buffer_for_read[read_bytes] = '\0';
		if (!(result_string))
		{
			if (!(result_string = malloc(sizeof(char) * read_bytes + 1)))
				return (NULL);
			ft_bzero(result_string, read_bytes + 1);
			ft_memcpy(result_string, buffer_for_read, read_bytes);
		}
		else
			result_string = join_me(result_string, buffer_for_read);
	}
	res_str_len = ft_strlen(result_string);
	result_string[res_str_len] = '\0';
	return (result_string);
}

int			i_am_string_maker(const int fd)
{
	static char	*result_string;

	if (fd == -1)
		return (0);
	result_string = i_am_for_reading(fd, result_string);
	printf("%s\n", result_string);
	free(result_string);
	return (0);
}
```

``` C
__i_am_string_maker.h__

#ifndef I_AM_STRING_MAKER_H
# define I_AM_STRING_MAKER_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

# define BUFF_SIZE 2

int		i_am_string_maker(const int fd);

#endif
```

``` C
__sample.line__

The wind of Mt. Fuji
I've brought on my fan!
a gift from Edo
```

#### 1.2.3 step 3
All done! So, to run the program u need such files:
- main.c
- string_maker.c
- i_am_string_maker.h
- sample.line

i'm using my own library, so i also need (u can use standart libc, just remove ft_ before functions):

- libft.a
- libft.h

run:
```
> gcc main.c string_maker.c libft.a
> ./a.out sample.line 
```

and you will see:
```
>
The wind of Mt. Fuji
I've brought on my fan!
a gift from Edo
>
```

## 2) come back to get_next_line
So, this function returns a line read from a file descriptor. “Line” is a succession of characters that end with ’\n’ (ascii code
0x0a) or with End Of File (EOF). Also you are able to manage multiple file descriptor with my get_next_line. For example, if the file descriptors 3, 4 and 5 are accessible for reading, then you can call get_next_line once on 3, once on 4, once again on 3 then once on 5 etc. without losing the reading thread on each of the descriptors.

### 2.1 to test the program with single FD use main_one.c
run:
```
$> make -C libft/ fclean && make -C libft/
$> clang -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
$> clang -Wall -Wextra -Werror -I libft/includes -o main_one.o -c main_one.c
$> clang -o test_gnl main_one.o get_next_line.o -I libft/includes -L libft/ -lft
$> ./test_gnl sample.line
```

and you will see:
```
>
The wind of Mt. Fuji
I've brought on my fan!
a gift from Edo
bla bla bla
Found process 25888 (test_gnl) from partial name test
Process 25888: 153 nodes malloced for 17 KB
Process 25888: 0 leaks for 0 total leaked bytes.
>
```

### 2.2 to test the program with single FD use main_two.c
run:
```
$> make -C libft/ fclean && make -C libft/
$> clang -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
$> clang -Wall -Wextra -Werror -I libft/includes -o main_two.o -c main_two.c
$> clang -o test_gnl main_one.o get_next_line.o -I libft/includes -L libft/ -lft
$> ./test_gnl sample.line sample1.line
```
