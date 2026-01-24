/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:58:50 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/12 22:08:26 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../lib/libft/libft.h"

void	hook_events(t_data *data)
{
	mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx->win, 17, 0, exit_program, data);
}

int	should_render(t_data *data)
{
	long long	curr_time;
	long long	delta;

	curr_time = get_time();
	delta = time_diff(data->last_frame_time, curr_time);
	if (delta < 16)
		return (0);
	data->last_frame_time = curr_time;
	data->delta_time = time_to_seconds(delta);
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

#include <stdio.h>
int	fps_debug(void)
{
	static int	frame_count = 0;
	static long long	last_print = 0;

	frame_count++;
	long long	current_time = get_time();
	if (time_diff(last_print, current_time) >= SECOND)
	{
		printf("FPS: %d\n", frame_count);
		frame_count = 0;
		last_print = current_time;
	}
	return (0);
}

int	render_loop(t_data *data)
{
	if (should_render(data))
	{
		detect_determ_input(data->player);
		renderer(data);
		fps_debug();
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_data	data;
	if (argc != 2)
	{
		return (1);
	}

	init_data(&data);
	load_map(&data, argv[1]);
	init_mlx(&data);
	init_all_textures(&data);
	hook_events(&data);
	renderer(&data);
	mlx_loop_hook(data.mlx->mlx, render_loop, &data);
	mlx_loop(data.mlx->mlx);
	exit_program(&data);
	return (0);
}

