/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 23:53:27 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/27 17:15:06 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <math.h>

void	init_ray_vars(t_player *player, t_ray *ray, int x)
{
	ray->cam_x = 2.0 * x / (double)(W_WI) - 1.0;
	ray->ray_dir_x = player->x_dir + player->x_plane * ray->cam_x;
	ray->ray_dir_y = player->y_dir + player->y_plane * ray->cam_x;
	ray->map_x = (int)(player->x_coor);
	ray->map_y = (int)(player->y_coor);
}

void	init_dda_vars(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x == 0)
		ray->dda.delta_dist_x = 1e30;
	else
		ray->dda.delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->dda.delta_dist_y = 1e30;
	else
		ray->dda.delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	ray->dda.did_hit_wall = 0;
	ray->dda.perp_wall_dist = 0;
	init_dda_vars_x(ray, player);
	init_dda_vars_y(ray, player);
}

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

void	dda_algorithm(t_data *data, t_ray *ray)
{
	int	i;

	i = 0;
	while (ray->dda.did_hit_wall == 0 && i < DDA_IT_LIMIT)
	{
		dda_iter(data, ray);
		i++;
	}
	if (ray->dda.side == 0)
		ray->dda.perp_wall_dist = ray->dda.side_dist_x - ray->dda.delta_dist_x;
	else
		ray->dda.perp_wall_dist = ray->dda.side_dist_y - ray->dda.delta_dist_y;
	if (ray->dda.perp_wall_dist < 0.0001)
		ray->dda.perp_wall_dist = 0.0001;
}

void	cast_rays(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < W_WI)
	{
		init_ray_vars(data->player, &ray, x);
		init_dda_vars(&ray, data->player);
		dda_algorithm(data, &ray);
		render_wall_rectangle(data, &ray,
			x, calculate_wall_x(&ray, data->player));
		x++;
	}
}
