/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:48:32 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/17 16:55:17 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "data_structs.h"
#include <math.h>

void	draw_rectangle(t_data *data, t_rect	rect)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect.y)
	{
		j = 0;
		while (j < rect.x)
		{
			put_pixel_to_img(data, \
				rect.x_coor + j, rect.y_coor + i, rect.color);
			j ++;
		}
		i++;
	}
}

void	draw_circle(t_data *data, t_circle circle)
{
	int	i;
	int	j;

	i = -circle.radius;
	while (i <= circle.radius)
	{
		j = -circle.radius;
		while (j <= circle.radius)
		{
			if (i * i + j * j <= circle.radius * circle.radius)
				put_pixel_to_img(data, \
					circle.x_center_coor + j, circle.y_center_coor + i, circle.color);
			j++;
		}
		i++;
	}
}
