/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:55:27 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/17 14:38:10 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "data_structs.h"
#include <math.h>

static int	my_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

void	put_pixel_to_img(t_data *data, int x, int y, int color)
{
	int	*pixel;

	if (x < 0 || y < 0 || x >= W_WI || y >= W_HE)
		return ;
	pixel = (int *)(data->mlx->addr + \
			(y * data->mlx->l_len + x * (data->mlx->bitbp / 8)));
	*pixel = color;
}

static void	draw_line_controls(t_bres_line *line, t_pos *pos)
{
	if (pos->x0 < pos->x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (pos->y0 < pos->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
}

static void	line_control(t_pos *pos, t_bres_line *line)
{
	line->e2 = 2 * line->err;
	if (line->e2 > -line->dy)
	{
		line->err -= line->dy;
		pos->x0 += line->sx;
	}
	if (line->e2 < line->dx)
	{
		line->err += line->dx;
		pos->y0 += line->sy;
	}
}

void	draw_line(t_data *data, t_pos pos, int color)
{
	t_bres_line	line;

	line.dx = my_abs(pos.x1 - pos.x0);
	line.dy = my_abs(pos.y1 - pos.y0);
	draw_line_controls(&line, &pos);
	while (1)
	{
		put_pixel_to_img(data, pos.x0, pos.y0, color);
		if (pos.x0 == pos.x1 && pos.y0 == pos.y1)
			break ;
		line_control(&pos, &line);
	}
}
