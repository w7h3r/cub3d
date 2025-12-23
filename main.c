/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:58:50 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/23 14:23:47 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include "data_structs.h"
#include "lib/libft/libft.h"
#include "lib/minilibx-linux/mlx.h"

void	hook_events(t_data *data)
{
	mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx->win, 17, 0, exit_program, data);
}

int	should_render(void)
{
	static long long	last_frame_time = 0;
	long long			curr_frame_time;
	long long			delta_time;

	curr_frame_time = get_time();
	delta_time = time_diff(last_frame_time, curr_frame_time);
	if (delta_time < 16)
		return (0);
	last_frame_time = curr_frame_time;
	return (1);
}

int	is_player_moving(t_key_state *key_state)
{
	return (key_state->w_key || key_state->a_key || key_state->s_key || \
		key_state->d_key || key_state->left_arrow || key_state->right_arrow);
}

void	detect_determ_input(t_player *player)
{
	if (player->key_state.w_key)
		move_forward(player);
	if (player->key_state.s_key)
		move_backward(player);
	if (player->key_state.a_key)
		move_left(player);
	if (player->key_state.d_key)
		move_right(player);
	if (player->key_state.left_arrow)
		rotate_left(player);
	if (player->key_state.right_arrow)
		rotate_right(player);
}

int	render_loop(t_data *data)
{
	if (!should_render())
		return (0);
	detect_determ_input(data->player);
	if (is_player_moving(&data->player->key_state))
		renderer(data);
	return (0);
}

int main(void)
{
	t_data	data;

	init_data(&data);
	init_mlx(&data);
	hook_events(&data);
	renderer(&data);
	mlx_loop_hook(data.mlx->mlx, render_loop, &data);
	mlx_loop(data.mlx->mlx);
	return (0);
}

