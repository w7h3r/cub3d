/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:49:30 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/27 02:49:44 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	hook_events(t_data *data)
{
	mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx->win, 17, 0, exit_program, data);
}

int	is_player_moving(t_key_state *key_state)
{
	return (key_state->w_key || key_state->a_key || key_state->s_key
		|| key_state->d_key || key_state->left_arrow || key_state->right_arrow);
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
