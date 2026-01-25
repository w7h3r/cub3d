/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:55:27 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/25 17:44:40 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel_to_img(t_data *data, int x, int y, int color)
{
	int	*pixel;

	if (x < 0 || y < 0 || x >= W_WI || y >= W_HE)
		return ;
	pixel = (int *)(data->mlx->addr + \
			(y * data->mlx->l_len + x * (data->mlx->bitbp / 8)));
	*pixel = color;
}
