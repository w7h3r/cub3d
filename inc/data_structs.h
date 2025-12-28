/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:03:13 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/28 04:52:21 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_STRUCTS_H
# define GAME_STRUCTS_H

# include "../lib/minilibx-linux/mlx.h"

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

typedef enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_direction;

typedef struct	s_key_state
{
	int	w_key;
	int	a_key;
	int	s_key;
	int	d_key;
	int	left_arrow;
	int	right_arrow;
}	t_key_state;

typedef struct	s_data	t_data;

typedef struct	s_player
{
	double	x_coor;
	double	y_coor;
	double	x_dir;
	double	y_dir;
	double	x_plane;
	double	y_plane;
	double	angle;
	t_key_state	key_state;
	t_data		*data;
}	t_player;

typedef struct	s_map
{
	char	**map_grids;
	int		width;
	int		height;
}	t_map;

typedef struct	s_data
{
	t_mlx		*mlx;
	t_player	*player;
	t_map		*map;
	double		delta_time;
	long long	last_frame_time;
}	t_data;

#endif
