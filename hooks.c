/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:15:20 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/17 18:49:58 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "data_structs.h"
#include "lib/minilibx-linux/mlx.h"
#include <stdlib.h>
#include <math.h>

void	exit_program(t_data *data)
{
	(void)data;
	// clean_data(data);
	mlx_destroy_image(data->mlx->mlx, data->mlx->img);
	mlx_destroy_image(data->mlx->mlx, data->mlx->bg_img);
	mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	mlx_destroy_display(data->mlx->mlx);
	free(data->mlx->mlx);
	exit(0);
}

void	move_forward(t_player *player)
{
	player->y_coor += cos(player->angle) * MOVEMENT_SPEED;
	player->x_coor += sin(player->angle) * MOVEMENT_SPEED;
}

void	move_backward(t_player *player)
{
	player->y_coor -= cos(player->angle) * MOVEMENT_SPEED;
	player->x_coor -= sin(player->angle) * MOVEMENT_SPEED;
}

void	rotate_left(t_player *player)
{
	player->angle -= ROTATION_SPEED;
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	update_vectors(player);
}

void	rotate_right(t_player *player)
{
	player->angle += ROTATION_SPEED;
	if (player->angle > 2 * M_PI)
		player->angle -= 2 * M_PI;
	update_vectors(player);
}

void	move_left(t_player *player)
{
	player->y_coor += cos(player->angle + M_PI / 2) * MOVEMENT_SPEED;
	player->x_coor += sin(player->angle + M_PI / 2) * MOVEMENT_SPEED;
}

void	move_right(t_player *player)
{
	player->y_coor += cos(player->angle - M_PI / 2) * MOVEMENT_SPEED;
	player->x_coor += sin(player->angle - M_PI / 2) * MOVEMENT_SPEED;
}


void	set_key_state(t_key_state *key_event, int key_code, int state)
{
	if (key_code == KEY_W)
		key_event->w_key = state;
	else if (key_code == KEY_A)
		key_event->a_key = state;
	else if (key_code == KEY_S)
		key_event->s_key = state;
	else if (key_code == KEY_D)
		key_event->d_key = state;
	else if (key_code == KEY_L_ARR)
		key_event->left_arrow = state;
	else if (key_code == KEY_R_ARR)
		key_event->right_arrow = state;
}

int	key_press(int key_code, t_data *data)
{
	if (key_code == KEY_ESC)
		exit_program(data);
	set_key_state(&data->player->key_state, key_code, 1);
	return (0);
}

int	detect_key_press(int key_code, t_data *data)
{
	t_key_state	key_event;

	set_key_state(&key_event, key_code, 1);
	if (key_event.w_key)
		move_forward(data->player);
	if (key_event.s_key)
		move_backward(data->player);
	if (key_event.a_key)
		move_left(data->player);
	if (key_event.d_key)
		move_right(data->player);
	if (key_event.left_arrow)
		rotate_left(data->player);
	if (key_event.right_arrow)
		rotate_right(data->player);
	if (key_code == KEY_ESC)
		exit_program(data);
	if (key_code == BUTTON_CLOSE)
		exit_program(data);
	renderer(data);
	return (0);
}
