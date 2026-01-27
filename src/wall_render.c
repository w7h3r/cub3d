/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:04:16 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/27 15:57:39 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <math.h>

t_texture	*decide_texture_side(t_data *data, t_ray *ray)
{
	if (ray->dda.side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&data->map->texture_e);
		else
			return (&data->map->texture_w);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&data->map->texture_s);
		else
			return (&data->map->texture_n);
	}
}

double	calculate_wall_x(t_ray *ray, t_player *player)
{
	double	wall_x;

	if (ray->dda.side == 0)
		wall_x = player->y_coor + ray->dda.perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = player->x_coor + ray->dda.perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	get_pixel_image(t_texture *texture, int tex_x, int tex_y)

{
	if (!texture || !texture->addr)
		return (0);
	if (tex_x < 0 || tex_x >= texture->width
		|| tex_y < 0 || tex_y >= texture->height)
		return (0);
	return (*((unsigned int *)(texture->addr
			+ (tex_y * texture->l_len + tex_x * (texture->bitbp / 8)))));
}

int	prepare_pixel(t_ray *ray, t_texture texture, int tex_y, t_pixel_info info)
{
	double	step;
	double	tex_pos;
	int		tex_x;

	step = 1.0 * texture.height / (info.wall_height);
	tex_pos = (info.wall_start - 1.0
			* W_HE / 2 + 1.0 * (info.wall_height) / 2) * step;
	tex_x = (int)(info.wall_x * (double)(texture.width));
	if ((ray->dda.side == 0 && ray->ray_dir_x < 0)
		|| (ray->dda.side == 1 && ray->ray_dir_y > 0))
		tex_x = texture.width - tex_x - 1;
	tex_pos += step;
	return (get_pixel_image(&texture, tex_x, tex_pos
			+ (tex_y - (int)info.wall_start) * step));
}

void	render_wall_rectangle(t_data *data, t_ray *ray, int x, double wall_x)
{
	t_pixel_info	pixel_info;

	pixel_info.wall_height = (int)((double)W_HE / ray->dda.perp_wall_dist);
	pixel_info.wall_start = (W_HE - pixel_info.wall_height) / 2;
	pixel_info.wall_end = (W_HE + pixel_info.wall_height) / 2;
	pixel_info.wall_x = wall_x;
	if (pixel_info.wall_start < 0)
		pixel_info.wall_start = 0;
	if (pixel_info.wall_end >= W_HE)
		pixel_info.wall_end = W_HE;
	pixel_info.y = pixel_info.wall_start;
	while (pixel_info.y < pixel_info.wall_end)
	{
		pixel_info.color = prepare_pixel(ray, *decide_texture_side(data, ray),
				pixel_info.y, pixel_info);
		put_pixel_to_img(data, x, pixel_info.y, pixel_info.color);
		pixel_info.y++;
	}
}
