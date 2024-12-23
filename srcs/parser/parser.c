/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:18:35 by trazanad          #+#    #+#             */
/*   Updated: 2024/12/23 11:50:17 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	(*count)->a_l = 0;
	(*count)->cam = 0;
	(*count)->light = 0;
	return (0);
}

int check_first_word_and_count_A_C_L(char *str, int file, t_data *data)
{
	t_count *count;

	count = NULL;
	if (count_init(&count))
		return (1);
	while (str)
	{
		if (!ft_strcmp(str, "\n"))
		{
			free(str);
			str = get_next_line(file);
		}
		else
		{
			if (check_first_and_count_param(str, count, data) ||
				count->a_l > 1 || count->cam > 1 || count->light > 1)
			{
				free(str);
				free(count);
				return (1);
			}
			free(str);
			str = get_next_line(file);
		}
	}
	free(count);
	return (0);
}

int check_file_content(int file, t_data *data)
{
	char *str;

	if (alloc_data_default(data))
		return (1);
	str = get_next_line(file);
	if (str == NULL)
	{
		ft_perror("error , empty line ", 22);
		return (1);
	}
	if (check_first_word_and_count_A_C_L(str, file, data))
	{
		ft_perror("error , wrong content ", 22);
		return (1);
	}
	return (0);
}

int parse_file(char *filename, t_data *data)
{
	int file;

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
	if (check_file_content(file, data) == 1)
	{
		close(file);
		return (1);
	}
	close(file);
	return (0);
}
