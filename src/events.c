/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:49:30 by muokcan           #+#    #+#             */
/*   Updated: 2026/02/03 06:47:21 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	hook_events(t_data *data)
{
	mlx_hook(data->mlx->win, 2, 1, key_press, data);
	mlx_hook(data->mlx->win, 3, 2, key_release, data);
	mlx_hook(data->mlx->win, 17, 0, exit_program, data);
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
