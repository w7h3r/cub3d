/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 05:03:23 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/26 18:02:59 by keezgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void    fill_map_with_two(t_list *map, size_t max_width)
{
    t_list  *tmp;
    char    *new_row;
    size_t     i;

    tmp = map;
    while (tmp)
    {
        new_row = reg_alloc(sizeof(char) * (max_width + 1));
        i = 0;
        while (tmp->content[i] && tmp->content[i] != '\n')
        {
            new_row[i] = tmp->content[i];
            if (tmp->content[i] == ' ')
                new_row[i] = '2';       
            i++;
        }
        while (i < max_width)
            new_row[i++] = '2';
        new_row[i] = '\0';
        tmp->content = new_row;
        tmp->width = max_width;
        tmp = tmp->next;
    }
}

static int	check_char(char c, int *is_player_set)
{
	if (c == ' ' || c == '\t' || c == '1' || c == '0')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*is_player_set)
		{
			parser_print_err("Multiple character definition on map!");
			return (0);
		}
		*is_player_set = true;
		return (1);
	}
	parser_print_err("Undefined character on map!");
	return (0);
}

static int	check_rows(t_list *map, int *is_player_set)
{
	int		i;

	while (map)
	{
		i = 0;
		while (map->content[i] && map->content[i] != '\n')
		{
			if (!check_char(map->content[i], is_player_set))
				return (0);
			i++;
		}
		map = map->next;
	}
	if (*is_player_set == false)
	{
		parser_print_err("No character on map!");
		return (0);
	}
	return (1);
}

int parser_handle_map(t_game *game)
{
    size_t max_width;
    size_t max_height;
    int is_player_set;
    is_player_set = false;
    if (!check_rows(game->map , &is_player_set))
        return (0);
    max_width = find_max_width(game->map);
    max_height = parser_get_list_size(game->map);
    game->map_width = max_width;
    game->map_height = max_height;
    fill_map_with_two(game->map , max_width);
    game->matrix_map = list_to_matrix(game->map);
    game->tmp = copy_matrix(game->matrix_map , max_height);
    set_player_location(game);
    return (1);
}