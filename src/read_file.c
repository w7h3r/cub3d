/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:52:55 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/25 17:22:01 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void    parser_read_file(t_game *game, char *file)
{
    int     fd;
    char    *line;
    int     i;
    unsigned int    start;
    int counter; // ceiling ve floor icin gerekli
    int set_length = 0; // mapin uzunlugu için gerekli

    game->map = NULL;
    game->parse.north_set = false;
    game->parse.south_set = false;
    game->parse.west_set = false;
    game->parse.east_set = false;
    game->parse.floor_set = false;
    game->parse.ceiling_set = false;
    game->parse.is_map_started = false;
	game->parse.north_file = NULL;
	game->parse.south_file = NULL;
	game->parse.west_file = NULL;
	game->parse.east_file = NULL;
	game->map_height = 0;
	game->map_width = 0;
    fd = open(file , O_RDONLY);
    if (fd < 0)
    {
        parser_print_err("File doesn't have read permission!");
        exit(1);
    }
    while ((line = get_next_line(fd)))
    {
        i = 0;
        start = 0;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if (line[i] == '\n')
        {
            free(line);
            continue;
        }
        else if (line[i] == 'N' && line[i + 1] == 'O' && game->parse.is_map_started == false && game->parse.north_set == false)
        {
            i += 2;
            while (line[i] == ' ' || line[i] == '\t')
                i++;
            start = i; // burada bir newline ve null kontrolu aklinda bulunsun
            while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
                i++;
            game->parse.north_file = parser_ft_substr(line , start , i - start);
            while (line[i] && line[i] != '\n')
            {
                if (line[i] != ' ' && line[i] != '\t')
                {
                    parser_print_err("Unexpected data after texture path!");
                    exit(1);
                }
                i++;
            }
            game->parse.north_set = true;
            free(line);
            continue;
        }
        else if (line[i] == 'S' && line[i + 1] == 'O' && game->parse.is_map_started == false && game->parse.south_set == false)
        {
            i += 2;
            while (line[i] == ' ' || line[i] == '\t')
                i++;
            start = i; // burada bir newline ve null kontrolu aklinda bulunsun
            while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
                i++;
            game->parse.south_file = parser_ft_substr(line , start , i - start);
            while (line[i] && line[i] != '\n')
            {
                if (line[i] != ' ' && line[i] != '\t')
                {
                    parser_print_err("Unexpected data after texture path!");
                    exit(1);
                }
                i++;
            }
            game->parse.south_set = true;
            free(line);
            continue;
        }
        else if (line[i] == 'E' && line[i + 1] == 'A' && game->parse.is_map_started == false && game->parse.east_set == false)
        {
            i += 2;
            while (line[i] == ' ' || line[i] == '\t')
                i++;
            start = i; // burada bir newline ve null kontrolu aklinda bulunsun
            while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
                i++;
            game->parse.east_file = parser_ft_substr(line , start , i - start);
            while (line[i] && line[i] != '\n')
            {
                if (line[i] != ' ' && line[i] != '\t')
                {
                    parser_print_err("Unexpected data after texture path!");
                    exit(1);
                }
                i++;
            }
            game->parse.east_set = true;
            free(line);
            continue;
        }
        else if (line[i] == 'W' && line[i + 1] == 'E' && game->parse.is_map_started == false && game->parse.west_set == false)
        {
            i += 2;
            while (line[i] == ' ' || line[i] == '\t')
                i++;
            start = i; // burada bir newline ve null kontrolu aklinda bulunsun
            while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
                i++;
            game->parse.west_file = parser_ft_substr(line , start , i - start);
            while (line[i] && line[i] != '\n')
            {
                if (line[i] != ' ' && line[i] != '\t')
                {
                    parser_print_err("Unexpected data after texture path!");
                    exit(1);
                }
                i++;
            }
            game->parse.west_set = true;
            free(line);
            continue;
        }
        else if (line[i] == 'F' && game->parse.is_map_started == false && game->parse.floor_set == false)
        {
            i++;
            while (line[i] == ' ' || line[i] == '\t')
                i++;
            start = i;
            while (line[i] != '\n')
                i++;
            game->parse.floor_line = parser_ft_substr(line , start , i - start);
            i = 0;
            counter = 0;
            while (line[start + i])
            {
                if (line[start + i] == ',')
                {
                    if (line[start + i + 1] && line[start + i + 1] == ',')
                    {
                        parser_print_err("There is a consecutive comma in the color range!");
                        exit (1);
                    }
                    counter++;
                }
                i++;
            }
            if (counter != 2)
            {
                parser_print_err("There are not enough arguments for RGB!");
                exit (1);
            }
            char **floor_data = parser_ft_split(game->parse.floor_line , ',');
            if (!floor_data[0] || !floor_data[1] || !floor_data[2])
            {
                parser_print_err("Missing RGB value!");
                exit(1);
            }
            game->parse.floor_r = parser_ft_atoi(floor_data[0]);
            game->parse.floor_g = parser_ft_atoi(floor_data[1]);
            game->parse.floor_b = parser_ft_atoi(floor_data[2]);

            if (game->parse.floor_r == -1 || game->parse.floor_g == -1 || game->parse.floor_b == -1)
            {
                parser_print_err("Invalid color value, (must be between 0-255)!");
                exit (1);
            }
            game->parse.floor_set = true;
            counter = 0;
            free(line);
            continue;
        }
        else if (line[i] == 'C' && game->parse.is_map_started == false && game->parse.ceiling_set == false)
        {
            i++;
            while (line[i] == ' ' || line[i] == '\t')
                i++;
            start = i;
            while (line[i] != '\n')
                i++;
            game->parse.ceiling_line = parser_ft_substr(line , start , i - start);
            i = 0;
            counter = 0;
            while (line[start + i])
            {
                if (line[start + i] == ',')
                {
                    if (line[start + i + 1] && line[start + i + 1] == ',')
                    {
                        parser_print_err("There is a consecutive comma in the color range!");
                        exit (1);
                    }
                    counter++;
                }
                i++;
            }
            if (counter != 2)
            {
                parser_print_err("There are not enough arguments for RGB!");
                exit (1);
            }
            char **ceiling_data = parser_ft_split(game->parse.ceiling_line , ',');
            if (!ceiling_data[0] || !ceiling_data[1] || !ceiling_data[2])
            {
                parser_print_err("Missing RGB value!");
                exit(1);
            }
            game->parse.ceiling_r = parser_ft_atoi(ceiling_data[0]);
            game->parse.ceiling_g = parser_ft_atoi(ceiling_data[1]);
            game->parse.ceiling_b = parser_ft_atoi(ceiling_data[2]);

            if (game->parse.ceiling_r == -1 || game->parse.ceiling_g == -1 || game->parse.ceiling_b == -1)
            {
                parser_print_err("Invalid color value, (must be between 0-255)!");
                exit (1);
            }
            game->parse.ceiling_set = true;
            counter = 0;
            free(line);
            continue; 
        }
        else if ((line[i] == 'N' && line[i + 1] == 'O' && game->parse.north_set == true) || (line[i] == 'S' && line[i + 1] == 'O' && game->parse.south_set == true) || (line[i] == 'W' && line[i + 1] == 'E' && game->parse.west_set == true) || (line[i] == 'E' && line[i + 1] == 'A' && game->parse.east_set == true) || (line[i] == 'F' && game->parse.floor_set == true) || (line[i] == 'C' && game->parse.ceiling_set == true))
        {
            parser_print_err("Multiple definition of textures!");
            exit(1);
        }
        else if (game->parse.west_set == true && game->parse.east_set == true && game->parse.north_set == true && game->parse.south_set == true && game->parse.floor_set == true && game->parse.ceiling_set == true) 
        { // map başlıyor
            game->parse.is_map_started = true;
            parser_list_add_back(&game->map , line , set_length++);
            continue;
        }
        else
        {
            parser_print_err("Invalid line or missing textures on file");
            exit(1);
        }
    }
    if (!game->parse.north_set || !game->parse.south_set || 
        !game->parse.west_set || !game->parse.east_set || 
        !game->parse.floor_set || !game->parse.ceiling_set || 
        game->map == NULL)
    {
        parser_print_err("Missing textures or map content!");
        exit(1);
    }
}
