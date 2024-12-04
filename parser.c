#include "mini.h"

void  ft_checker(char *str, int *amb_light)
{
  int i;
  int index;

  i = 0;
  index = 0;
  while (str[i] != '\0')
  {
    if (str[i] == ' ')
      i++;
    else if (str[i] == 'A' && index == 0)
      index++;
    else if (str[i])
    {
      
    }
  }
}

int file_parser(char *filename)
{
	int file;
  char *str;

  int amb_light;

  amb_light = 0;
	file = open(filename, O_RDONLY);
	if (file == -1)
		return (-1);
	while (1)
	{
		str = get_next_line(file, 1);
		if (str == NULL)
      break;
		else if (str[0] != '\n')
    {
      ft_checker(str, &amb_light);
    }
	}
	close(file);
  if (amb_light == 0)
    return (1);
  return (0);
}
