/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 23:53:27 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/25 19:52:23 by muokcan          ###   ########.fr       */
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

void	init_dda_vars_x(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->dda.step_x = -1;
		ray->dda.side_dist_x = (player->x_coor - ray->map_x) * ray->dda.delta_dist_x;
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
		ray->dda.side_dist_y = (player->y_coor - ray->map_y) * ray->dda.delta_dist_y;
	}
	else
	{
		ray->dda.step_y = 1;
		ray->dda.side_dist_y = (ray->map_y + 1.0 - player->y_coor) * ray->dda.delta_dist_y;
	}
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

/*  INIT  */

void	dda_algorithm(t_data *data, t_ray *ray)
{
	int	i;

	i = 0;
	while (ray->dda.did_hit_wall == 0 && i < DDA_IT_LIMIT)
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
		i++;
	}
	if (ray->dda.side == 0)
		ray->dda.perp_wall_dist = ray->dda.side_dist_x - ray->dda.delta_dist_x;
	else
		ray->dda.perp_wall_dist = ray->dda.side_dist_y - ray->dda.delta_dist_y;
	if (ray->dda.perp_wall_dist < 0.0001)
		ray->dda.perp_wall_dist = 0.0001;
}

/*  BURAYI EL YORDAMI YAPACAIM SONRA  */

t_texture *decide_texture_side(t_data *data, t_ray *ray)
{
	if (ray->dda.side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&data->map->texture_w);
		else
			return (&data->map->texture_e);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&data->map->texture_n);
		else
			return (&data->map->texture_s);
	}
}

int	get_pixel_image(t_texture *texture, int tex_x, int tex_y)
{
	if (!texture || !texture->addr)
		return (0);
	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0 || tex_y >= texture->height)
		return (0);
	return (*((unsigned int *)(texture->addr + (tex_y * texture->l_len + tex_x * (texture->bitbp / 8)))));
}

double	calculate_wall_x(t_ray *ray, t_player *player);

int	prepare_pixel(t_texture texture, int wall_start, double wall_x, int tex_y, int line_height)
{
	double			step;
	double			tex_pos;

	step = 1.0 * texture.height / (line_height);
	tex_pos = (wall_start - 1.0 * W_HE / 2 + 1.0 * (line_height) / 2) * step;
	int		tex_x = (int)(wall_x * (double)(texture.width));
	tex_pos += step;
	return (get_pixel_image(&texture, tex_x, tex_pos + (tex_y - (int)wall_start) * step));
}

void	render_wall_rectangle(t_data *data, t_ray *ray, int x, double wall_x)
{
	int	wall_height;
	int	wall_start;
	int	wall_end;
	int	start_pixel;
	int	the_key_of_everything;
	int color;

	wall_height = (int)((double)W_HE / ray->dda.perp_wall_dist);
	wall_start = (W_HE - wall_height) / 2;
	wall_end = (W_HE + wall_height) / 2;
	start_pixel = wall_start;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end >= W_HE)
		wall_end = W_HE;
	the_key_of_everything = wall_start;
	while (the_key_of_everything < wall_end)
	{
		color = prepare_pixel(*decide_texture_side(data, ray), start_pixel, wall_x, the_key_of_everything, wall_height);
		put_pixel_to_img(data, x, the_key_of_everything, color);
		the_key_of_everything++;
	}
}

double	calculate_wall_x(t_ray *ray, t_player *player)
{
	double wall_x;

	if (ray->dda.side == 0)
		wall_x = player->y_coor + ray->dda.perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = player->x_coor + ray->dda.perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	cast_rays(t_data *data)
{
	t_ray ray;
	int	x;

	x = 0;
	while (x < W_WI)
	{
		init_ray_vars(data->player, &ray, x);
		init_dda_vars(&ray, data->player);
		dda_algorithm(data, &ray);
		render_wall_rectangle(data, &ray, x, calculate_wall_x(&ray, data->player));
		x++;
	}
}
