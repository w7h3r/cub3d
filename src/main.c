/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:58:50 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/27 03:02:30 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

unsigned int	compose_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	convert_structs(t_game *game, t_data *data)
{
	data->map->width = game->map_width;
	data->map->height = game->map_height;
	data->map->map_grids = game->matrix_map;
	data->map->floor_color = compose_color(game->parse.floor_r,
			game->parse.floor_g, game->parse.floor_b);
	data->map->ceiling_color = compose_color(game->parse.ceiling_r,
			game->parse.ceiling_g, game->parse.ceiling_b);
	data->map->texture_n.path = game->parse.north_file;
	data->map->texture_s.path = game->parse.south_file;
	data->map->texture_e.path = game->parse.east_file;
	data->map->texture_w.path = game->parse.west_file;
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_game	game;

	if (argc != 2 || parser_arg_parse(argv[1]))
	{
		parser_print_err("Usage: ./cub3d <map_file.cub>");
		return (1);
	}
	init_game_struct(&game);
	parser_read_file(&game, argv[1]);
	parser_handle_map(&game);
	init_data(&data, &game);
	convert_structs(&game, &data);
	init_mlx(&data);
	init_all_textures(&data);
	hook_events(&data);
	renderer(&data);
	mlx_loop_hook(data.mlx->mlx, render_loop, &data);
	mlx_loop(data.mlx->mlx);
	exit_program(&data);
	return (0);
}
