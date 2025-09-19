/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:09:22 by muokcan           #+#    #+#             */
/*   Updated: 2024/10/25 16:09:22 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	getlen(int n)
{
	int	i;

	i = 0;
	if (n == MIN_INT)
		return (11);
	if (n < 0)
	{
		i++;
		n = -n;
	}
	else if (n == 0)
		return (1);
	if (n > 0)
	{
		while (n != 0)
		{
			n = n / 10;
			i++;
		}
	}
	return (i);
}

static char	*write_digits(char *wd, int number, int gl_digit)
{
	if (number == MIN_INT)
	{
		wd[0] = '-';
		wd[1] = '2';
		number = 147483648;
	}
	else if (number < 0)
	{
		wd[0] = '-';
		number = -number;
	}
	if (number == 0)
	{
		wd[0] = '0';
		return (wd);
	}
	while (number != 0)
	{
		wd[gl_digit--] = (number % 10) + '0';
		number = number / 10;
	}
	return (wd);
}

char	*ft_itoa(int n)
{
	unsigned int	digit;
	char			*res;

	digit = getlen(n);
	res = malloc(sizeof(char) * (digit + 1));
	if (res == NULL)
		return (NULL);
	res[digit--] = '\0';
	return (write_digits(res, n, digit));
}
