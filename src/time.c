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
#include <stddef.h>

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

