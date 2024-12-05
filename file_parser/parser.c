#include "../mini.h"
#include "get_next_line.h"
#include <string.h>

int check_file_extention(char *filename)
{
	char *str;

	if (ft_strlen(filename) < 4)
		return (0);
	str = ft_substr(filename, ft_strlen(filename) - 3, 3);
	if (strcmp(str, ".rt"))
		return (0);
	return (1);
}

int file_parser(char *filename)
{
	int file;
	char *str;

	if (check_file_extention(filename) == 0)
	{
		errno = 22;
		perror("error , file extention ");
		return (1);
	}
	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		perror("error ");
		return (1);
	}
	str = get_next_line(file, 1);
	if (str == NULL)
	{
		errno = 22;
		perror("error , empty line ");
		return (1);
	}
	close(file);
	return (0);
}
