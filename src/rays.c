/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 23:53:27 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/28 06:41:35 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <math.h>

void	init_ray_vars(t_player *player, t_ray *ray, int x)
{
	ray->cam_x = 2 * x / (double)(W_WI) - 1;
	ray->ray_dir_x = player->x_dir + player->x_plane * ray->cam_x;
	ray->ray_dir_y = player->y_dir + player->y_plane * ray->cam_x;
	ray->map_x = (int)(player->x_coor);
	ray->map_y = (int)(player->y_coor);
}

void	init_dda_vars_x(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->dda.step_x = -1;
		ray->dda.side_dist_x = (ray->map_x - player->x_coor) * ray->dda.delta_dist_x;
	}
	else
	{
		ray->dda.step_x = 1;
		ray->dda.side_dist_x = (ray->map_x + 1.0 - player->x_coor) * ray->dda.delta_dist_x;
	}
}

void	init_dda_vars_y(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_y < 0)
	{
		ray->dda.step_y = -1;
		ray->dda.side_dist_y = (ray->map_y - player->y_coor) * ray->dda.delta_dist_y;
	}
	else
	{
		ray->dda.step_y = 1;
		ray->dda.side_dist_y = (ray->map_y + 1.0 - player->y_coor) * ray->dda.delta_dist_y;
	}
}

void	init_dda_vars(t_ray *ray, t_player *player)
{
	ray->dda.delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->dda.delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->dda.did_hit_wall = 0;
	init_dda_vars_x(ray, player);
	init_dda_vars_y(ray, player);
}

void	dda(t_data *data, t_ray *ray)
{
	while (ray->dda.did_hit_wall == 0)
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
		if (ray->map_x < 0 || ray->map_x >= data->map->width \
			|| ray->map_y < 0 || ray->map_y >= data->map->height)
		{
			ray->dda.did_hit_wall = 1;
			break ;
		}
		if (data->map->map_grids[ray->map_y][ray->map_x] == '1')
			ray->dda.did_hit_wall = 1;
	}
}

void	cast_rays(t_data *data)
{
	int	x;

	x = 0;
	while (x < W_WI)
	{
		init_ray_vars(data->player, data->ray, x);
		init_dda_vars(data->ray, data->player);
		dda(data, data->ray);
		render_wall(data, data->ray, x);
		x++;
	}
}
