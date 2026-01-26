/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 22:53:32 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/26 21:59:09 by keezgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void flood_fill(char **map, int x, int y, int width, int height)
{
    if (x < 0 || y < 0 || y >= height || x >= width)
        parser_print_err_exit("Map is not closed (Player can go outside)!");
    if (map[y][x] == '1' || map[y][x] == 'F')
        return;
    if (map[y][x] == '2')
        parser_print_err_exit("Map is not closed (Space found inside)!");
    map[y][x] = 'F';
    flood_fill(map, x + 1, y, width, height);
    flood_fill(map, x - 1, y, width, height);
    flood_fill(map, x, y + 1, width, height);
    flood_fill(map, x, y - 1, width, height);
}

void set_player_location(t_game *game)
{
    int     i;
    int     j;
    i = 0;
    while (game->matrix_map[i])
    {
        j = 0;
        while (game->matrix_map[i][j])
        {
            if (ft_strchr("NSWE", game->matrix_map[i][j]))
            {
                game->player_x = j;
                game->player_y = i;
                game->player_dir = game->matrix_map[i][j];
                break;
            }
            j++;
        }
        i++;
    }
    flood_fill(game->tmp, game->player_x, game->player_y, ft_strlen(game->matrix_map[0]), get_matrix_height(game->matrix_map));
}