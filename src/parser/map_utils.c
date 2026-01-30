/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 22:56:12 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/26 23:44:40 by keezgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	find_max_width(t_list *map)
{
	size_t	len;
	t_list	*tmp;

	tmp = map;
	len = 0;
	while (tmp)
	{
		if (len < tmp->width)
			len = tmp->width;
		tmp = tmp->next;
	}
	return (len);
}

int	get_matrix_height(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

char	**copy_matrix(char **map, size_t height)
{
	char	**copy;
	size_t	i;

	copy = reg_alloc(sizeof(char *) * (height + 1));
	i = 0;
	while (i < height)
	{
		copy[i] = parser_ft_strdup(map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	**list_to_matrix(t_list *map)
{
	char	**matrix;
	t_list	*temp;
	size_t	i;

	matrix = reg_alloc(sizeof(char *) * (parser_get_list_size(map) + 1));
	temp = map;
	i = 0;
	while (temp)
	{
		matrix[i] = parser_ft_strdup(temp->content);
		temp = temp->next;
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}
