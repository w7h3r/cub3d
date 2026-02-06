/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:02:19 by muokcan           #+#    #+#             */
/*   Updated: 2025/12/28 06:37:31 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <sys/time.h>

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	time_diff(long long last_frame_time, long long curr_frame_time)
{
	return (curr_frame_time - last_frame_time);
}

double	time_to_seconds(long long time_in_ms)
{
	return ((double)time_in_ms / 1000.0);
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
	if (data->delta_time > 0.1)
		data->delta_time = 0.1;
	return (1);
}
