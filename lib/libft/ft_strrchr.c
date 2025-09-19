/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:02:23 by muokcan           #+#    #+#             */
/*   Updated: 2024/10/18 18:03:00 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	slen;

	slen = ft_strlen(s) + 1;
	while (slen--)
	{
		if (s[slen] == (char)c)
			return ((char *)&s[slen]);
	}
	return (NULL);
}
