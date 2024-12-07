/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 07:56:32 by ferafano          #+#    #+#             */
/*   Updated: 2024/07/22 07:56:35 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buffer, char *buf_handler, int Buff)
{
	int		x;
	char	*temp;

	x = 1;
	while (x != '\0')
	{
		x = read(fd, buffer, Buff);
		if (x == -1)
			return (NULL);
		else if (x == 0)
			break ;
		buffer[x] = '\0';
		if (buf_handler == NULL)
			buf_handler = ft_add_null();
		temp = buf_handler;
		buf_handler = ft_join(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_is_new_line (buffer))
			break ;
	}
	return (buf_handler);
}

char	*ft_copy_nl(char *line)
{
	size_t	index;
	char	*handler;

	index = 0;
	while (line[index] != '\n' && line[index] != '\0')
		index++;
	if (line[index] == '\0')
		return (NULL);
	handler = ft_substr(line, index + 1, ft_strlen(line) - index);
	if (*handler == '\0')
	{
		free(handler);
		handler = NULL;
	}
	line[index + 1] = '\0';
	return (handler);
}

char	*get_next_line(int fd, int Buff)
{
	char		*line;
	char		*buffer;
	static char	*buf_handler = NULL;

	if (fd < 0 || Buff <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (Buff + 1));
	if (buffer == NULL)
		return (NULL);
	line = ft_read(fd, buffer, buf_handler, Buff);
	free(buffer);
	buffer = NULL;
	if (line == NULL)
		return (NULL);
	buf_handler = ft_copy_nl(line);
	return (line);
}
