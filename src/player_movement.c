/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:52:36 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/23 13:51:19 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <math.h>

// int	is_wall(t_player *player)
// {
//
// }
//
// int	can_move(t_player *player)
// {
//
// }

int	move_forward(t_player *player)
{
	player->x_coor += player->x_dir * MOVEMENT_SPEED * player->data->delta_time;
	player->y_coor += player->y_dir * MOVEMENT_SPEED * player->data->delta_time;
	return (0);
}

int	move_backward(t_player *player)
{
	player->x_coor -= player->x_dir * MOVEMENT_SPEED * player->data->delta_time;
	player->y_coor -= player->y_dir * MOVEMENT_SPEED * player->data->delta_time;
	return (0);
}

int	rotate_left(t_player *player)
{
	player->angle -= ROTATION_SPEED * player->data->delta_time;
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	update_vectors(player);
	return (0);
}

int	rotate_right(t_player *player)
{
	player->angle += ROTATION_SPEED * player->data->delta_time;
	if (player->angle > 2 * M_PI)
		player->angle -= 2 * M_PI;
	update_vectors(player);
	return (0);
}

int	move_left(t_player *player)
{
	player->x_coor += player->y_dir * MOVEMENT_SPEED * player->data->delta_time;
	player->y_coor -= player->x_dir * MOVEMENT_SPEED * player->data->delta_time;
	return (0);
}

int	move_right(t_player *player)
{
	player->x_coor -= player->y_dir * MOVEMENT_SPEED * player->data->delta_time;
	player->y_coor += player->x_dir * MOVEMENT_SPEED * player->data->delta_time;
	return (0);
}
