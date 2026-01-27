/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 22:53:32 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/26 23:54:02 by keezgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	flood_fill(t_game *game, char **map, int x, int y)
{
	if (x < 0 || y < 0 || y >= game->map_height || x >= game->map_width)
		parser_print_err_exit("Map is not closed (Player can go outside)!");
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == '2')
		parser_print_err_exit("Map is not closed (Space found inside)!");
	map[y][x] = 'F';
	flood_fill(game, map, x + 1, y);
	flood_fill(game, map, x - 1, y);
	flood_fill(game, map, x, y + 1);
	flood_fill(game, map, x, y - 1);
}

void	set_player_location(t_game *game)
{
	int	i;
	int	j;

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
				break ;
			}
			j++;
		}
		i++;
	}
	flood_fill(game, game->tmp, game->player_x, game->player_y);
}
