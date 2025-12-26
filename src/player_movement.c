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

int	move_forward(t_player *player)
{
	player->y_coor += cos(player->angle) * MOVEMENT_SPEED;
	player->x_coor += sin(player->angle) * MOVEMENT_SPEED;
	return (0);
}

int	move_backward(t_player *player)
{
	player->y_coor -= cos(player->angle) * MOVEMENT_SPEED;
	player->x_coor -= sin(player->angle) * MOVEMENT_SPEED;
	return (0);
}

int	rotate_left(t_player *player)
{
	player->angle -= ROTATION_SPEED;
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	update_vectors(player);
	return (0);
}

int	rotate_right(t_player *player)
{
	player->angle += ROTATION_SPEED;
	if (player->angle > 2 * M_PI)
		player->angle -= 2 * M_PI;
	update_vectors(player);
	return (0);
}

int	move_left(t_player *player)
{
	player->y_coor += cos(player->angle + M_PI / 2) * MOVEMENT_SPEED;
	player->x_coor += sin(player->angle + M_PI / 2) * MOVEMENT_SPEED;
	return (0);
}

int	move_right(t_player *player)
{
	player->y_coor += cos(player->angle - M_PI / 2) * MOVEMENT_SPEED;
	player->x_coor += sin(player->angle - M_PI / 2) * MOVEMENT_SPEED;
	return (0);
}

