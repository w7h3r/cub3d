/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:58:50 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/17 18:10:01 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include "data_structs.h"
#include "lib/libft/libft.h"
#include "lib/minilibx-linux/mlx.h"

int main(void)
{
	t_data	data;

	init_data(&data);
	init_mlx(&data);

	draw_minimap(&data);
	draw_player(&data);

	mlx_put_image_to_window(data.mlx->mlx, data.mlx->win, data.mlx->img, 0, 0);
	mlx_loop(data.mlx->mlx);
	return (0);
}

