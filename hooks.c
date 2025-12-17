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

int	detect_key_press(t_data *data, int key_code)
{
	if (key_code == KEY_ESC)
		exit_program(data);
	else if (key_code == KEY_W)
		move_forward(data->player);
	else if (key_code == KEY_A)
		move_left(data->player);
	else if (key_code == KEY_S)
		 move_backward(data->player);
	else if (key_code == KEY_D)
		move_right(data->player);
	else if (key_code == KEY_L_ARR)
		rotate_left(data->player);
	else if (key_code == KEY_R_ARR)
		rotate_right(data->player);
	generate_frame(data);
	return (0);
}
