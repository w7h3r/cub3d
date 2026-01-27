/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 05:44:45 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/26 23:31:26 by keezgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static char	*ft_after_newline(char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	temp = reg_alloc(ft_strlen_gnl(str) - i + 1);
	if (!temp)
		return (NULL);
	if (str[i] == '\n')
		i++;
	while (str[i])
		temp[j++] = str[i++];
	temp[j] = '\0';
	return (temp);
}

static char	*ft_before_newline(char *str)
{
	char	*temp;
	int		i;

	i = 0;
	if (!str || !str[i])
		return (NULL);
	while (str[i] && (str[i] != '\n'))
		i++;
	if (str[i] == '\n')
		i++;
	temp = reg_alloc(i + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (str[i] && (str[i] != '\n'))
	{
		temp[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		temp[i++] = '\n';
	temp[i] = '\0';
	return (temp);
}

static char	*ft_read(int fd, char *str)
{
	char	*temp;
	int		size;

	size = 1;
	temp = reg_alloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while (!gnl_strchr(str, '\n') && size != 0)
	{
		size = read(fd, temp, BUFFER_SIZE);
		if (size == -1)
			return (NULL);
		temp[size] = '\0';
		str = gnl_strjoin(str, temp);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_before_newline(buffer);
	buffer = ft_after_newline(buffer);
	return (line);
}
