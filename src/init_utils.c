/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 03:04:01 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/27 15:12:14 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_game_struct(t_game *game)
{
	game->map_width = 0;
	game->map_height = 0;
	game->matrix_map = NULL;
	game->tmp = NULL;
	game->player_x = 0;
	game->player_y = 0;
	game->player_dir = 0;
	game->parse.north_file = NULL;
	game->parse.south_file = NULL;
	game->parse.east_file = NULL;
	game->parse.west_file = NULL;
	game->parse.west_set = false;
	game->parse.east_set = false;
	game->parse.south_set = false;
	game->parse.north_set = false;
	game->parse.floor_r = -1;
	game->parse.floor_g = -1;
	game->parse.floor_b = -1;
	game->parse.ceiling_r = -1;
	game->parse.ceiling_g = -1;
	game->parse.ceiling_b = -1;
}

void	init_texture(t_data *data, t_texture *texture)
{
	texture->width = 0;
	texture->height = 0;
	texture->img = mlx_xpm_file_to_image(data->mlx->mlx,
			texture->path, &texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Failed path: [%s]\n", texture->path);
		err_exit_init("Error: Can't load texture image");
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bitbp,
			&texture->l_len, &texture->endian);
	if (!texture->addr)
		err_exit_init("Error: Can't get texture image address");
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
	(*map)->texture_n.path = NULL;
	(*map)->texture_s.path = NULL;
	(*map)->texture_e.path = NULL;
	(*map)->texture_w.path = NULL;
	(*map)->texture_n.img = NULL;
	(*map)->texture_s.img = NULL;
	(*map)->texture_e.img = NULL;
	(*map)->texture_w.img = NULL;
	(*map)->texture_n.addr = NULL;
	(*map)->texture_s.addr = NULL;
	(*map)->texture_e.addr = NULL;
	(*map)->texture_w.addr = NULL;
}
