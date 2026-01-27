/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:52:32 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/25 17:12:17 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../lib/libft/libft.h"
#include "../lib/minilibx-linux/mlx.h"

void	clear_image(t_data *data)
{
	ft_memcpy(data->mlx->addr, data->mlx->bg_addr, W_WI * W_HE * sizeof(int));
}

void	fill_floor_ceiling(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < W_HE / 2)
	{
		x = 0;
		while (x < W_WI)
		{
			put_pixel_to_img(data, x, y, data->map->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < W_HE)
	{
		x = 0;
		while (x < W_WI)
		{
			put_pixel_to_img(data, x, y, data->map->floor_color);
			x++;
		}
		y++;
	}
}

void	render_scene_frame(t_data *data)
{
	fill_floor_ceiling(data);
	cast_rays(data);
}

void	renderer(t_data *data)
{
	render_scene_frame(data);
	mlx_put_image_to_window(data->mlx->mlx,
		data->mlx->win, data->mlx->img, 0, 0);
}

int	render_loop(t_data *data)
{
	if (should_render(data))
	{
		detect_determ_input(data->player);
		renderer(data);
		return (0);
	}
	return (1);
}
