/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:58:50 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/26 23:16:57 by keezgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
//
// #include <stdio.h>
// int	fps_debug(void)
// {
// 	static int	frame_count = 0;
// 	static long long	last_print = 0;
//
// 	frame_count++;
// 	long long	current_time = get_time();
// 	if (time_diff(last_print, current_time) >= SECOND)
// 	{
// 		printf("FPS: %d\n", frame_count);
// 		frame_count = 0;
// 		last_print = current_time;
// 	}
// 	return (0);
// }

unsigned int compose_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	convert_structs(t_game *game, t_data *data)
{
	data->map->width = game->map_width;
	data->map->height = game->map_height;
	data->map->map_grids = game->matrix_map;
	data->map->floor_color = compose_color(game->parse.floor_r, \
		game->parse.floor_g, game->parse.floor_b);
	data->map->ceiling_color = compose_color(game->parse.ceiling_r, \
		game->parse.ceiling_g, game->parse.ceiling_b);
	data->map->texture_n.path = game->parse.north_file;
	data->map->texture_s.path = game->parse.south_file;
	data->map->texture_e.path = game->parse.east_file;
	data->map->texture_w.path = game->parse.west_file;
}

int    parser_arg_parse(char *str)
{
    size_t pos;

    pos = parser_ft_strlen(str);
    if (pos < 5 || parser_ft_strcmp(&str[pos - 4] , ".cub"))
        parser_print_err_exit("File extension doesn't end with .cub");
    return (0);
} 

int main(int argc, char **argv)
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
	if (!parser_handle_map(&game))
	{
		free_all_mem();
		return (1);
	}
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

