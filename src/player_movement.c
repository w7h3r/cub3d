/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:52:36 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/27 02:45:05 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <math.h>

int	move_forward(t_player *player)
{
	double	new_x;
	double	new_y;

	new_x = player->x_coor;
	new_y = player->y_coor;
	new_x += player->x_dir * MOVEMENT_SPEED * player->data->delta_time;
	new_y += player->y_dir * MOVEMENT_SPEED * player->data->delta_time;
	if (player->data->map->map_grids
		[(int)(player->y_coor)][(int)(new_x)] != '1')
		player->x_coor = new_x;
	if (player->data->map->map_grids
		[(int)(new_y)][(int)(player->x_coor)] != '1')
		player->y_coor = new_y;
	return (0);
}

int	move_backward(t_player *player)
{
	double	new_x;
	double	new_y;

	new_x = player->x_coor;
	new_y = player->y_coor;
	new_x -= player->x_dir * MOVEMENT_SPEED * player->data->delta_time;
	new_y -= player->y_dir * MOVEMENT_SPEED * player->data->delta_time;
	if (player->data->map->map_grids
		[(int)(player->y_coor)][(int)(new_x)] != '1')
		player->x_coor = new_x;
	if (player->data->map->map_grids
		[(int)(new_y)][(int)(player->x_coor)] != '1')
		player->y_coor = new_y;
	return (0);
}

int	move_left(t_player *player)
{
	double	new_x;
	double	new_y;

	new_x = player->x_coor;
	new_y = player->y_coor;
	new_x -= player->x_plane * MOVEMENT_SPEED * player->data->delta_time;
	new_y -= player->y_plane * MOVEMENT_SPEED * player->data->delta_time;
	if (player->data->map->map_grids
		[(int)(player->y_coor)][(int)(new_x)] != '1')
		player->x_coor = new_x;
	if (player->data->map->map_grids
		[(int)(new_y)][(int)(player->x_coor)] != '1')
		player->y_coor = new_y;
	return (0);
}

int	move_right(t_player *player)
{
	double	new_x;
	double	new_y;

	new_x = player->x_coor;
	new_y = player->y_coor;
	new_x += player->x_plane * MOVEMENT_SPEED * player->data->delta_time;
	new_y += player->y_plane * MOVEMENT_SPEED * player->data->delta_time;
	if (player->data->map->map_grids
		[(int)(player->y_coor)][(int)(new_x)] != '1')
		player->x_coor = new_x;
	if (player->data->map->map_grids
		[(int)(new_y)][(int)(player->x_coor)] != '1')
		player->y_coor = new_y;
	return (0);
}
