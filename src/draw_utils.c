/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:55:27 by muokcan           #+#    #+#             */
/*   Updated: 2026/02/03 05:32:37 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel_to_img(t_data *data, int x, int y, int color)
{
	int	*pixel;

	if (x < 0 || y < 0 || x >= W_WI || y >= W_HE)
		return ;
	pixel = (int *)(data->mlx->addr + (y * data->mlx->l_len + x
				* (data->mlx->bitbp / 8)));
	*pixel = color;
}

void	delete_texture(void)
{
	t_data	*data;

	data = *get_data();
	if (!data)
		return ;
	if (data->map->texture_n.img)
	{
		mlx_destroy_image(data->mlx->mlx, data->map->texture_n.img);
		data->map->texture_n.img = NULL;
	}
	if (data->map->texture_s.img)
	{
		mlx_destroy_image(data->mlx->mlx, data->map->texture_s.img);
		data->map->texture_s.img = NULL;
	}
	if (data->map->texture_e.img)
	{
		mlx_destroy_image(data->mlx->mlx, data->map->texture_e.img);
		data->map->texture_e.img = NULL;
	}
	if (data->map->texture_w.img)
	{
		mlx_destroy_image(data->mlx->mlx, data->map->texture_w.img);
		data->map->texture_w.img = NULL;
	}
}
