/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:04:32 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/25 20:06:32 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	err_exit_init(t_data *data, const char *err_msg)
{
	printf("%s\n", err_msg);
	exit_program(data);
}

void	init_game_struct(t_game *game)
{
	game->map_width = 0;
	game->map_height = 0;
	game->matrix_map = NULL;
	game->tmp = NULL;
}

void	init_texture(t_data *data, t_texture *texture)
{
	texture->width = 0;
	texture->height = 0;
	texture->img = mlx_xpm_file_to_image(data->mlx->mlx, \
			texture->path, &texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Failed path: [%s]\n", texture->path);
		err_exit_init(data, "Error: Can't load texture image");
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bitbp, \
			&texture->l_len, &texture->endian);
	if (!texture->addr)
		err_exit_init(data, "Error: Can't get texture image address");
}

void	init_all_textures(t_data *data)
{
	init_texture(data, &data->map->texture_n);
	init_texture(data, &data->map->texture_s);
	init_texture(data, &data->map->texture_e);
	init_texture(data, &data->map->texture_w);
}

void	init_keys(t_key_state *keys)
{
	keys->w_key = 0;
	keys->a_key = 0;
	keys->s_key = 0;
	keys->d_key = 0;
	keys->left_arrow = 0;
	keys->right_arrow = 0;
}

void	init_map(t_map **map)
{
	*map = reg_alloc(sizeof(t_map));
	if (!*map)
	{
		printf("Map memory allocation failed!\n");
		exit(1);
	}
	(*map)->width = 0;
	(*map)->height = 0;
	(*map)->map_grids = NULL;
	(*map)->floor_color = 0xF01A1A;
	(*map)->ceiling_color = 0x00FFFF;
}

void	init_data(t_data *data, t_game *game)
{
	data->mlx = reg_alloc(sizeof(t_mlx));
	if (!data->mlx)
		err_exit_init(NULL, "MLX memory allocation failed!\n");
	data->player = reg_alloc(sizeof(t_player));
	if (!data->player)
	{
		free(data->mlx);
		err_exit_init(NULL, "Player memory allocation failed!\n");
	}
	init_player(data->player, game);
	init_keys(&data->player->key_state);
	init_map(&data->map);
	data->player->data = data;
	data->mlx->mlx = NULL;
	data->mlx->win = NULL;
	data->mlx->addr = NULL;
	data->mlx->img = NULL;
	data->mlx->bg_addr = NULL;
	data->mlx->bg_img = NULL;
	data->last_frame_time = 0;
	data->delta_time = 0.0;
	data->ray = NULL;
	data->ray = reg_alloc(sizeof(t_ray) * W_WI);
	if (!data->ray)
		err_exit_init(data, "Ray memory allocation failed!\n");
}

void	init_mlx(t_data *data)
{
	data->mlx->mlx = mlx_init();
	if (!data->mlx->mlx)
		err_exit_init(data, "Error: Can't initialize mlx");

	data->mlx->win = mlx_new_window(data->mlx->mlx, W_WI, W_HE, "cub3D");
	if (!data->mlx->win)
		err_exit_init(data, "Error: Can't initialize window");

	data->mlx->img = mlx_new_image(data->mlx->mlx, W_WI, W_HE);
	if (!data->mlx->img)
		err_exit_init(data, "Error: Can't initialize image");
	data->mlx->addr = mlx_get_data_addr(data->mlx->img, &data->mlx->bitbp, \
			&data->mlx->l_len, &data->mlx->endian);
	if (!data->mlx->addr)
		err_exit_init(data, "Error: Can't take the image addr");

	data->mlx->bg_img = mlx_new_image(data->mlx->mlx, W_WI, W_HE);
	if (!data->mlx->bg_img)
		err_exit_init(data, "Error: Can't initialize image");
	data->mlx->bg_addr = mlx_get_data_addr(data->mlx->bg_img, &data->mlx->bitbp, \
			&data->mlx->l_len, &data->mlx->endian);
	if (!data->mlx->bg_addr)
		err_exit_init(data, "Error: Can't take the image addr");
	fill_background(data, IMAGE_ERASE_COLOR);
}

void	update_vectors(t_player *player)
{
	player->x_dir = cos(player->angle);
	player->y_dir = sin(player->angle);
	player->x_plane = -sin(player->angle) * 0.66;
	player->y_plane = cos(player->angle) * 0.66;
}

void	init_player(t_player *player, t_game *game)
{
	player->x_coor = game->player_x + 0.5;
	player->y_coor = game->player_y + 0.5;
	if (game->player_dir == 'N')
		player->angle = 3.14 * 1.5;
	else if (game->player_dir == 'S')
		player->angle = 3.14 * 0.5;
	else if (game->player_dir == 'E')
		player->angle = 0;
	else if (game->player_dir == 'W')
		player->angle = 3.14;
	init_keys(&player->key_state);
	update_vectors(player);
}
