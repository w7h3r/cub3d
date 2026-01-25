/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:31:46 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/25 17:21:35 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int    parser_arg_parse(char *str)
{
    size_t pos;

    pos = parser_ft_strlen(str);
    if (pos < 5 || parser_ft_strcmp(&str[pos - 4] , ".cub"))
    {
        parser_print_err("File extension doesn't end with .cub");
        return (1);
    }
    return (0);
}
