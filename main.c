/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:58:50 by muokcan           #+#    #+#             */
/*   Updated: 2025/09/19 16:43:13 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lib/libft/libft.h"

int	detect_argument_err(int argc, char **argv)
{
	size_t	file_name_len;

	if (argc != 2)
	{
		printf("Error: Invalid number of arguments.\n");
		return (1);
	}
	if (argv[1][0] == '\0')
	{
		printf("Error: Argument cannot be an empty string.\n");
		return (1);
	}
	file_name_len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][file_name_len - 4], ".cub", 4) != 0)
	{
		printf("Error: File extension must be .cub\n");
		return (1);
	}
	if (file_name_len < 5)
	{
		printf("Error: File name is too short to have a valid .cub extension.\n");
		return (1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	if (detect_argument_err(argc, argv))
		return (1);
	return (0);
}

