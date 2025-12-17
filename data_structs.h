/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:03:13 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/17 17:46:26 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_STRUCTS_H
# define GAME_STRUCTS_H

# include "lib/minilibx-linux/mlx.h"

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	void	*bg_img;
	char	*bg_addr;
	int		bitbp;
	int		l_len;
	int		endian;
}	t_mlx;

//	*** FUCNTIONS RELATED TO BRESSENHAM'LINE ALGORITHM ***

typedef struct s_pos
{
	int	x0;
	int	y0;
	int	z0;
	int	x1;
	int	y1;
	int	z1;
}	t_pos;

typedef struct s_bres_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_bres_line;

typedef struct	s_rect
{
	int	x;
	int	y;
	int	x_coor;
	int	y_coor;
	int	color;
}	t_rect;

typedef struct	s_circle
{
	int	x_center_coor;
	int	y_center_coor;
	int	radius;
	int	color;

}	t_circle;

typedef struct	s_player
{
	double	x_coor;
	double	y_coor;
	double	x_dir;
	double	y_dir;
	double	x_plane;
	double	y_plane;
}	t_player;

typedef struct	s_data
{
	t_mlx		*mlx;
	t_player	*player;
}	t_data;

#endif
