/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:04:32 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/17 18:24:29 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	err_exit_init(t_data *data, const char *err_msg)
{
	(void)data;
	printf("%s\n", err_msg);
	free(data->mlx);
	free(data->player);
	exit(1);
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

void	init_data(t_data *data)
{
	data->mlx = malloc(sizeof(t_mlx));
	if (!data->mlx)
		err_exit_init(NULL, "MLX memory allocation failed!\n");
	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		free(data->mlx);
		err_exit_init(NULL, "Player memory allocation failed!\n");
	}
	init_player(data->player);
	init_keys(&data->player->key_state);
	data->mlx->mlx = NULL;
	data->mlx->win = NULL;
	data->mlx->addr = NULL;
	data->mlx->img = NULL;
	data->mlx->bg_addr = NULL;
	data->mlx->bg_img = NULL;
}

void	fill_background(t_data *data, int color)
{
	int	*bg_addr;
	int	total_pixels;
	int	i;

	bg_addr = (int *)data->mlx->bg_addr;
	total_pixels = W_HE * W_WI;
	i = 0;
	while (i < total_pixels)
	{
		bg_addr[i] = color;
		i++;
	}
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
	fill_background(data, 0x111111);
}

void	update_vectors(t_player *player)
{
	player->x_dir = cos(player->angle);
	player->y_dir = sin(player->angle);
	player->x_plane = -sin(player->angle) * 0.66;
	player->y_plane = cos(player->angle) * 0.66;
}

void	init_player(t_player *player)
{
	player->x_coor = 5.5;
	player->y_coor = 5.5;
	player->x_dir = -1;
	player->y_dir = 0;
	player->x_plane = 0;
	player->y_plane = 0.66;
	player->angle = 3.14 * 1.5;
	update_vectors(player);
}
