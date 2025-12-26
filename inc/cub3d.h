/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:01:31 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/23 14:10:35 by muokcan          ###   ########.fr       */
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
void	fill_background(t_data *data, int color);

//	*** MLX FUNCTIONS ***
void	init_mlx(t_data *data);
void	init_data(t_data *data);
void	init_player(t_player *player);
int		exit_program(t_data *data);

//	*** TIME FUNCTIONS ***
long long	get_time(void);
long long	time_diff(long long last_fr_t, long long curr_fr_t);

//	*** RENDER ***
void	renderer(t_data *data);
int		should_render(void);
int		is_player_moving(t_key_state *key_state);
void	hook_events(t_data *data);
int		render_loop(t_data *data);
void	detect_determ_input(t_player *player);
void	update_vectors(t_player *player);
int		key_press(int key_code, t_data *data);
int		key_release(int key_code, t_data *data);

//	*** PLAYER MOVEMENT ***
int		move_forward(t_player *player);
int		move_backward(t_player *player);
int		rotate_left(t_player *player);
int		rotate_right(t_player *player);
int		move_left(t_player *player);
int		move_right(t_player *player);


#endif
