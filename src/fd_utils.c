/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 01:26:09 by muokcan           #+#    #+#             */
/*   Updated: 2026/02/03 04:41:49 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	*reg_fd(void)
{
	static int	fd = -1;

	return (&fd);
}

void	close_reg_fd(void)
{
	int	fd;

	fd = *reg_fd();
	if (fd != -1)
		close(fd);
}

int	open_reg_fd(const char *pathname, int flags)
{
	*reg_fd() = open(pathname, flags);
	return (*reg_fd());
}
