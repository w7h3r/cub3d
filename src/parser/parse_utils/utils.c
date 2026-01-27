/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:53:35 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/26 23:48:16 by keezgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/parser.h"

size_t	parser_ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	parser_ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*parser_ft_strdup(char *str)
{
	int		i;
	char	*s1;
	size_t	len;

	if (!str)
		return (NULL);
	i = 0;
	len = parser_ft_strlen(str);
	s1 = (char *)reg_alloc((len + 1) * sizeof(char));
	if (!s1)
		return (NULL);
	while (str[i])
	{
		s1[i] = str[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*parser_ft_substr(char *s, unsigned int start, size_t len)
{
	char	*buffer;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= parser_ft_strlen(s))
		len = 0;
	else if (parser_ft_strlen(s) < len + start)
		len = parser_ft_strlen(s) - start;
	buffer = (char *)reg_alloc((len + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		buffer[i] = s[start + i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

int	parser_ft_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - 48);
		if (num > 255)
			return (-1);
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i])
		return (-1);
	return (num);
}
