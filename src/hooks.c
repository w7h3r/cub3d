/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:15:20 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/28 06:41:14 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>

int	exit_program(t_data *data)
{
	if (data->mlx->img)
		mlx_destroy_image(data->mlx->mlx, data->mlx->img);
	if (data->mlx->bg_img)
		mlx_destroy_image(data->mlx->mlx, data->mlx->bg_img);
	if (data->map->texture_n.img)
		mlx_destroy_image(data->mlx->mlx, data->map->texture_n.img);
	if (data->map->texture_s.img)
		mlx_destroy_image(data->mlx->mlx, data->map->texture_s.img);
	if (data->map->texture_e.img)
		mlx_destroy_image(data->mlx->mlx, data->map->texture_e.img);
	if (data->map->texture_w.img)
		mlx_destroy_image(data->mlx->mlx, data->map->texture_w.img);
	if (data->mlx->win)
		mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	if (data->mlx->mlx)
	{
		mlx_destroy_display(data->mlx->mlx);
		free(data->mlx->mlx);
	}
	free_all_mem();
	exit(0);
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

int	key_release(int key_code, t_data *data)
{
	set_key_state(&data->player->key_state, key_code, 0);
	return (0);
}

