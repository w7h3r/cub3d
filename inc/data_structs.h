/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:03:13 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/27 15:52:01 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTS_H
# define DATA_STRUCTS_H

# include <unistd.h>
# include <stdbool.h>
# include "../lib/minilibx-linux/mlx.h"

typedef struct s_mlx
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

typedef enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_direction;

typedef struct s_key_state
{
	int	w_key;
	int	a_key;
	int	s_key;
	int	d_key;
	int	left_arrow;
	int	right_arrow;
}	t_key_state;

typedef struct s_data	t_data;

typedef struct s_player
{
	double		x_coor;
	double		y_coor;
	double		x_dir;
	double		y_dir;
	double		x_plane;
	double		y_plane;
	double		angle;
	t_direction	player_dir;
	t_key_state	key_state;
	t_data		*data;
}	t_player;

typedef struct s_dda
{
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		did_hit_wall;
	int		side;
}	t_dda;

typedef struct s_ray
{
	double	cam_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	t_dda	dda;
	double	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bitbp;
	int		l_len;
	int		endian;
	char	*path;
}	t_texture;

typedef struct s_pixel_info
{
	double	wall_x;
	int		wall_height;
	int		wall_start;
	int		wall_end;
	int		y;
	int		color;
}	t_pixel_info;

typedef struct s_map
{
	char				**map_grids;
	int					width;
	int					height;
	unsigned int		floor_color;
	unsigned int		ceiling_color;
	t_texture			texture_n;
	t_texture			texture_s;
	t_texture			texture_e;
	t_texture			texture_w;
}	t_map;

typedef struct s_data
{
	t_mlx				*mlx;
	t_player			*player;
	t_map				*map;
	t_ray				*ray;
	double				delta_time;
	long long			last_frame_time;
}	t_data;

typedef struct s_all_mem
{
	void				*mem;
	struct s_all_mem	*next;
}	t_all_mem;

typedef struct s_mem_manager
{
	t_all_mem	*head;
	t_all_mem	*tail;
	size_t		allocated_blocks;
	size_t		total_allocated_size;
}	t_mem_manager;

typedef struct s_list
{
	char			*content;
	size_t			length;
	size_t			width;
	struct s_list	*next;
}	t_list;

typedef struct s_parse
{
	bool	west_set;
	bool	east_set;
	bool	north_set;
	bool	south_set;
	bool	floor_set;
	bool	ceiling_set;
	bool	is_map_started;
	char	*west_file;
	char	*east_file;
	char	*north_file;
	char	*south_file;
	char	*floor_line;
	char	*ceiling_line;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
}	t_parse;

typedef struct s_game
{
	t_parse	parse;
	t_list	*map;
	char	**matrix_map;
	char	**tmp;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_game;

#endif
