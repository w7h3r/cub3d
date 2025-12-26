/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:53:15 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/23 12:53:57 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	fill_background(t_data *data, int color)
{
	int	*bg_addr;
	int	total_pixels;
	int	i;

	bg_addr = (int *)data->mlx->bg_addr;
	total_pixels = W_HE * W_WI;
	i = 0;
	while (i < total_pixels)
	{
		bg_addr[i] = color;
		i++;
	}
}
