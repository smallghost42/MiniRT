#include "../mini.h"
#include "get_next_line.h"
#include <string.h>

void ft_perror(char *message, int err_stat)
{
	errno = err_stat;
	perror(message);
}

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

int check_file_content(int file)
{
	char *str;

	str = get_next_line(file, 1);
	if (str == NULL)
	{
		ft_perror("error , empty line ", 22);
		return (1);
	}
	check_first_word_and_count_A_C_L();
	return (0);
}

int file_parser(char *filename)
{
	int file;

	int stat;

	stat = 0;
	if (check_file_extention(filename) == 0)
	{
		ft_perror("error , file extention ", 22);
		return (1);
	}
	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		perror("error ");
		return (1);
	}
	if (check_file_content(file) == 1)
		return (1);
	return (0);
}
