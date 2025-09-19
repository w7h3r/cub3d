/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:59:56 by muokcan           #+#    #+#             */
/*   Updated: 2025/03/11 22:05:45 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	h_sign(const char **nptr)
{
	int	sign;

	sign = 1;
	if (**nptr == '-' || **nptr == '+')
	{
		if (**nptr == '-')
			sign = -1;
		(*nptr)++;
	}
	return (sign);
}

int	ft_atoi_base(const char *nptr, int nptr_base)
{
	int			res;
	short int	sign;

	if (nptr_base < 2 || nptr_base > 16)
		return (0);
	res = 0;
	while (ft_isspace(*nptr))
		nptr++;
	sign = h_sign(&nptr);
	while (*nptr)
	{
		if (*nptr >= '0' && *nptr <= '9')
			res = res * nptr_base + (*nptr - '0');
		else if (*nptr >= 'a' && *nptr <= 'f')
			res = res * nptr_base + (*nptr - 'a' + 10);
		else if (*nptr >= 'A' && *nptr <= 'F')
			res = res * nptr_base + (*nptr - 'A' + 10);
		else
			break ;
		nptr++;
	}
	return (res * sign);
}
