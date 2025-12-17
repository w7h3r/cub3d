/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:44:17 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/17 18:12:11 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
#include "data_structs.h"

#define	MAP_H 10
#define	MAP_W 10
#define TILE_SIZE 64

static void	draw_grid(t_data *data)
{
	t_pos	line;
	int		i;

	i = 0;
	while (i < MAP_W)
	{
		line.x0 = i * TILE_SIZE;
		line.y0 = 0;
		line.x1 = i * TILE_SIZE;
		line.y1 = MAP_H * TILE_SIZE;
		draw_line(data, line, 0x444444);
		i++;
	}
	i = 0;
	while (i < MAP_H)
	{
		line.y0 = i * TILE_SIZE;
		line.x0 = 0;
		line.y1 = i * TILE_SIZE;
		line.x1 = MAP_H * TILE_SIZE;
		draw_line(data, line, 0x444444);
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	t_rect	tile;
	int	x;
	int	y;
	int	mini_map[MAP_H][MAP_W] = 
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,1,1,0,0,0,0,1},
		{1,0,0,1,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,1,1},
		{1,0,0,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,1},
		{1,1,0,0,0,0,0,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
	};
	tile.x = TILE_SIZE;
	tile.y = TILE_SIZE;

	y = 0;
	while (y < MAP_H)
	{
		x = 0;
		while (x < MAP_W)
		{
			tile.x_coor = x * TILE_SIZE;
			tile.y_coor = y * TILE_SIZE;
			
			if (mini_map[y][x] == 1)
				tile.color = 0xFFFFFF;
			else
				tile.color = 0x000000;
			draw_rectangle(data, tile);
			x++;
		}
		y++;
	}
	draw_grid(data);
}

void	draw_player(t_data *data)
{
	t_circle	circle;
	t_pos		dir_line;
	int			px;
	int			py;


	px = data->player->x_coor * TILE_SIZE;
	py = data->player->y_coor * TILE_SIZE;

	circle.x_center_coor = px;
	circle.y_center_coor = py;

	circle.radius = 5;
	circle.color = 0xFF;
	draw_circle(data, circle);
	
	dir_line.x0 = px;
	dir_line.y0 = py;
	dir_line.x1 = px + (data->player->x_dir * 20);
	dir_line.y1 = py + (data->player->y_dir * 20);
	draw_line(data, dir_line, 0x00FF00);
}
