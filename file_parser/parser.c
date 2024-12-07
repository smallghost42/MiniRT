#include "../mini.h"

void ft_perror(char *message, int err_stat)
{
	errno = err_stat;
	perror(message);
}

int count_init(t_count **count)
{
	*count = malloc(sizeof(t_count));
	if (count == NULL)
	{
		perror("malloc failed ");
		return (1);
	}
	(*count)->cy = 0;
	(*count)->pl = 0;
	(*count)->sp = 0;
	(*count)->a_l = 0;
	(*count)->cam = 0;
	(*count)->light = 0;
	return (0);
}

int check_first_word_and_count_A_C_L(char *str, int file)
{
	t_count *count;

	count = NULL;
	if (count_init(&count))
		return (1);
	while (str)
	{
		if (!strcmp(str, "\n"))
		{
			free(str);
			str = get_next_line(file, 1);
		}
		else
		{
			if (check_first_and_count_param(str, count) || count->a_l > 1 ||
				count->cam > 1 || count->light > 1)
			{
				free(str);
				return (1);
			}
			free(str);
			str = get_next_line(file, 1);
		}
	}
	return (0);
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
	if (check_first_word_and_count_A_C_L(str, file))
	{
		ft_perror("error , wrong content ", 22);
		return (1);
	}
	return (0);
}

int file_parser(char *filename)
{
	int file;
	int stat;

	stat = 0;
	if (check_file_extention(filename))
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
	{
		close(file);
		return (1);
	}
	close(file);
	return (0);
}
