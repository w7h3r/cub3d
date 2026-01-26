/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:35:15 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/26 15:01:34 by keezgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    parser_print_err(char *str)
{
    parser_putstr_err("Error");
    parser_putstr_err(str);
}

void    parser_putstr_err(char *str)
{
    int i;
    i = 0;

    while (str[i])
    {
        write(2 , &str[i] , 1);
        i++;
    }
    write(2 , "\n" , 1);
}

void parser_print_err_exit(char *str)
{
    parser_print_err(str);
    exit (1);
}
