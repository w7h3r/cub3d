/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 02:43:52 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/27 02:45:48 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <math.h>

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
