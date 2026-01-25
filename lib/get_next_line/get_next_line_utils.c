/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:33:17 by keezgi            #+#    #+#             */
/*   Updated: 2025/12/26 13:39:52 by keezgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t ft_strlen_gnl(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*buffer;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	buffer = malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!buffer)
		return (free(buffer), NULL);
	i = -1;
	while (s1[++i])
		buffer[i] = s1[i];
	j = -1;
	while (s2[++j])
		buffer[i + j] = s2[j];
	buffer[i + j] = '\0';
	return (free(s1), buffer);
}

int	gnl_strchr(char *str, char a)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == a)
			return (1);
		str++;
	}
	return (0);
}
