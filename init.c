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

void	err_exit_init(t_data *data, const char *err_msg)
{
	(void)data;
	printf("%s\n", err_msg);
	free(data->mlx);
	free(data->player);
	exit(1);
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
	data->mlx->mlx = NULL;
	data->mlx->win = NULL;
	data->mlx->addr = NULL;
	data->mlx->img = NULL;
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
}

void	init_player(t_player *player)
{
	player->x_coor = 5;
	player->y_coor = 5;
	player->x_dir = -1;
	player->y_dir = 0;
	player->x_plane = 0;
	player->y_plane = 0.66;
}
