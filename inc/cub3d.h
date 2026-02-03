/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:01:31 by muokcan           #+#    #+#             */
/*   Updated: 2026/02/03 05:33:46 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "data_structs.h"
# include "defines.h"
# include "parser.h"

void		put_pixel_to_img(t_data *data, int x, int y, int color);
void		fill_background(t_data *data, int color);

void		init_mlx(t_data *data);
void		init_data(t_data *data, t_game *game);
void		init_player(t_player *player, t_game *game);
void		init_game_struct(t_game *game);
int			exit_program(void);
void		init_all_textures(t_data *data);
void		init_texture(t_data *data, t_texture *texture);
void		init_game_struct(t_game *game);
void		err_exit_init(const char *err_msg);
void		init_map(t_map **map);
void		init_keys(t_key_state *keys);
t_data		**get_data(void);
int			*reg_fd(void);
void		close_reg_fd(void);
int			open_reg_fd(const char *pathname, int flags);
void		delete_texture(void);

long long	get_time(void);
long long	time_diff(long long last_fr_t, long long curr_fr_t);
double		get_delta_time(long long *last_fr_time);;
double		time_to_seconds(long long time_in_ms);
int			should_render(t_data *data);

void		renderer(t_data *data);
int			should_render(t_data *data);
int			is_player_moving(t_key_state *key_state);
void		hook_events(t_data *data);
int			render_loop(t_data *data);
void		detect_determ_input(t_player *player);
void		update_vectors(t_player *player);
int			key_press(int key_code, t_data *data);
int			key_release(int key_code, t_data *data);
void		cast_rays(t_data *data);
void		render_wall_rectangle(t_data *data,
				t_ray *ray, int x, double wall_x);
double		calculate_wall_x(t_ray *ray, t_player *player);
void		dda_iter(t_data *data, t_ray *ray);
void		init_dda_vars_x(t_ray *ray, t_player *player);
void		init_dda_vars_y(t_ray *ray, t_player *player);

int			move_forward(t_player *player);
int			move_backward(t_player *player);
int			rotate_left(t_player *player);
int			rotate_right(t_player *player);
int			move_left(t_player *player);
int			move_right(t_player *player);

int			parser_arg_parse(char *str);
int			parser_handle_map(t_game *game);
void		parser_read_file(t_game *game, char *file);

void		*reg_alloc(size_t size);
void		free_all_mem(void);

#endif
