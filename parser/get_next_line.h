/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 07:56:55 by ferafano          #+#    #+#             */
/*   Updated: 2024/07/22 07:56:58 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
# endif

char	*get_next_line(int fd, int Buff);
char	*ft_copy_nl(char *line);
char	*ft_read(int fd, char *buf, char *backup, int Buff);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(const char *str);
char	*ft_is_new_line(const char *s);
char	*ft_add_null(void);
char	*ft_join(char const *s1, char const *s2);

#endif
