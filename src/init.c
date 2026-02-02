/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:04:32 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/27 03:23:49 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	err_exit_init(const char *err_msg)
{
	printf("%s\n", err_msg);
	exit_program();
}

void	init_data(t_data *data, t_game *game)
{
	*get_data() = data;
	data->mlx = reg_alloc(sizeof(t_mlx));
	if (!data->mlx)
		err_exit_init("MLX memory allocation failed!\n");
	data->player = reg_alloc(sizeof(t_player));
	if (!data->player)
		err_exit_init("Player memory allocation failed!\n");
	init_player(data->player, game);
	init_keys(&data->player->key_state);
	init_map(&data->map);
	data->player->data = data;
	data->mlx->mlx = NULL;
	data->mlx->win = NULL;
	data->mlx->addr = NULL;
	data->mlx->img = NULL;
	data->last_frame_time = 0;
	data->delta_time = 0.0;
	data->ray = NULL;
	data->ray = reg_alloc(sizeof(t_ray) * W_WI);
	if (!data->ray)
		err_exit_init("Ray memory allocation failed!\n");
}

void	init_mlx(t_data *data)
{
	data->mlx->mlx = mlx_init();
	if (!data->mlx->mlx)
		err_exit_init("Error: Can't initialize mlx");
	data->mlx->win = mlx_new_window(data->mlx->mlx, W_WI, W_HE, "cub3D");
	if (!data->mlx->win)
		err_exit_init("Error: Can't initialize window");
	data->mlx->img = mlx_new_image(data->mlx->mlx, W_WI, W_HE);
	if (!data->mlx->img)
		err_exit_init("Error: Can't initialize image");
	data->mlx->addr = mlx_get_data_addr(data->mlx->img, &data->mlx->bitbp,
			&data->mlx->l_len, &data->mlx->endian);
	if (!data->mlx->addr)
		err_exit_init("Error: Can't take the image addr"); 
}

void	update_vectors(t_player *player)
{
	player->x_dir = cos(player->angle);
	player->y_dir = sin(player->angle);
	player->x_plane = -sin(player->angle) * FOV;
	player->y_plane = cos(player->angle) * FOV;
}

void	init_player(t_player *player, t_game *game)
{
	player->x_coor = game->player_x + 0.5;
	player->y_coor = game->player_y + 0.5;
	if (game->player_dir == 'N')
		player->angle = PI * 1.5;
	else if (game->player_dir == 'S')
		player->angle = PI * 0.5;
	else if (game->player_dir == 'E')
		player->angle = 0; 
	else if (game->player_dir == 'W')
		player->angle = PI;
	init_keys(&player->key_state);
	update_vectors(player);
}
