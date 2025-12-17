/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:01:31 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/17 18:55:20 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "data_structs.h"
# include "defines.h"

//	*** GRAPHICAL FUNCTIONS ***
void	put_pixel_to_img(t_data *data, int x, int y, int color);
void	draw_line(t_data *data, t_pos pos, int color);
void	draw_rectangle(t_data *data, t_rect	rect);
void	draw_circle(t_data *data, t_circle circle);
void	draw_minimap(t_data *data);
void	draw_player(t_data *data);

//	*** MLX FUNCTIONS ***
void	init_mlx(t_data *data);
void	init_data(t_data *data);
void	init_player(t_player *player);

void	renderer(t_data *data);

#endif
