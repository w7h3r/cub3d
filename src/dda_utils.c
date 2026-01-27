/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:13:55 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/27 17:14:58 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	dda_iter(t_data *data, t_ray *ray)
{
	if (ray->dda.side_dist_x < ray->dda.side_dist_y)
	{
		ray->dda.side_dist_x += ray->dda.delta_dist_x;
		ray->map_x += ray->dda.step_x;
		ray->dda.side = 0;
	}
	else
	{
		ray->dda.side_dist_y += ray->dda.delta_dist_y;
		ray->map_y += ray->dda.step_y;
		ray->dda.side = 1;
	}
	if (ray->map_y >= 0 && ray->map_y < data->map->height
		&& ray->map_x >= 0 && ray->map_x < data->map->width)
	{
		if (data->map->map_grids[ray->map_y][ray->map_x] == '1')
			ray->dda.did_hit_wall = 1;
	}
	else
		ray->dda.did_hit_wall = 1;
}

void	init_dda_vars_x(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->dda.step_x = -1;
		ray->dda.side_dist_x = (player->x_coor - ray->map_x)
			* ray->dda.delta_dist_x;
	}
	else
	{
		ray->dda.step_x = 1;
		ray->dda.side_dist_x = (ray->map_x + 1.0 - player->x_coor)
			* ray->dda.delta_dist_x;
	}
}

void	init_dda_vars_y(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_y < 0)
	{
		ray->dda.step_y = -1;
		ray->dda.side_dist_y = (player->y_coor - ray->map_y)
			* ray->dda.delta_dist_y;
	}
	else
	{
		ray->dda.step_y = 1;
		ray->dda.side_dist_y = (ray->map_y + 1.0 - player->y_coor)
			* ray->dda.delta_dist_y;
	}
}
