/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:52:32 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/23 13:45:27 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../lib/libft/libft.h"
#include "../lib/minilibx-linux/mlx.h"

void	clear_image(t_data *data)
{
	ft_memcpy(data->mlx->addr, \
		data->mlx->bg_addr, W_WI * W_HE * sizeof(int));
}

void	renderer(t_data *data)
{
	clear_image(data);
	draw_minimap(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
}
