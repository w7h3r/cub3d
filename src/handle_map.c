/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 05:03:23 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/25 18:13:15 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    fill_map_with_two(t_list *map, size_t max_width)
{
    t_list  *tmp;
    char    *new_row;
    size_t     i;

    tmp = map;
    while (tmp)
    {
        if (tmp->width < max_width || (tmp->width > 0))
        {
            new_row = reg_alloc(sizeof(char) * (max_width + 1));
            i = 0;
            while (tmp->content[i] && tmp->content[i] != '\n')
            {
                new_row[i] = tmp->content[i];
                i++;
            }
            while (i < max_width)
            {
                new_row[i] = '2';
                i++;
            }
            new_row[i] = '\0';
            free(tmp->content);
            tmp->content = new_row;
            tmp->width = max_width;
        }
        tmp = tmp->next;
    }
}

size_t find_max_width(t_list *map)
{
    size_t len;
    t_list *tmp;
    tmp = map;
    len = 0;
    while (tmp)
    {
        if (len < tmp->width)
            len = tmp->width;
        tmp = tmp->next;
    }
    return (len);
}

int    check_rows(t_list *map , int *is_player_set)
{
    t_list *tmp;
    int i;
    tmp = map;
    while (tmp)
    {
        i = 0;
        while (tmp->content[i] && tmp->content[i] != '\n')
        {
            if (tmp->content[i] == '\t' || tmp->content[i] == ' ')
                i++;
            else if (tmp->content[i] == '1' || tmp->content[i] == '0')
                i++;
            else if ((tmp->content[i] == 'N' || tmp->content[i] == 'S' || tmp->content[i] == 'E' || tmp->content[i] == 'W') && *is_player_set == false)
            {
                *is_player_set = true;
                i++;
            }
            else if ((tmp->content[i] == 'N' || tmp->content[i] == 'S' || tmp->content[i] == 'E' || tmp->content[i] == 'W') && *is_player_set == true)
            {
                parser_print_err("Multiple character definition on map!");
                return (0);
            }
            else
            {
                parser_print_err("Undefined character on map!");
                return (0);
            }
        }
        tmp = tmp->next;
    }
    if (*is_player_set == false)
    {
        parser_print_err("No character on map!");
        return (0);
    }
    return (1);
}

char **list_to_matrix(t_list *map)
{
    char **matrix;
    t_list *temp;
    size_t i;
    
    matrix = reg_alloc(sizeof(char *) * (parser_get_list_size(map) + 1));
    temp = map;
    i = 0;
    while (temp)
    {
        matrix[i] = parser_ft_strdup(temp->content);
        temp = temp->next;
        i++;
    }
    matrix[i] = NULL;
    return (matrix);
}

// flood fill için matrix kopyası başlangıcı

int get_matrix_height(char **map)
{
    int i = 0;
    while (map && map[i])
        i++;
    return (i);
}

char **copy_matrix(char **map, size_t height)
{
    char **copy;
    size_t i;

    copy = reg_alloc(sizeof(char *) * (height + 1));
    i = 0;
    while (i < height)
    {
        copy[i] = parser_ft_strdup(map[i]);
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

// flood fill için matrix kopyası bitişi

void flood_fill(char **map, int x, int y, int width, int height)
{
    // 1. SINIR KONTROLÜ
    // Harita dışına çıktıysa -> Map açık demektir (HATA)
    if (x < 0 || y < 0 || y >= height || x >= width)
    {
        printf("Error: Map is not closed (Player can go outside)!\n");
        exit(1);
    }

    // 2. KARAKTER KONTROLÜ
    // Duvar ('1') veya gidilmiş yer ('F') ise dur.
    if (map[y][x] == '1' || map[y][x] == 'F')
        return;

    // Boşluk (' ') ise -> HATA
    if (map[y][x] == ' ')
    {
        parser_print_err("Map is not closed (Space found inside)!");
        exit(1);
    }
    map[y][x] = 'F';
    flood_fill(map, x + 1, y, width, height);
    flood_fill(map, x - 1, y, width, height);
    flood_fill(map, x, y + 1, width, height);
    flood_fill(map, x, y - 1, width, height);
}

void check_map_closed(t_game *game)
{
    int     p_x;
    int     p_y;
    int     i;
    int     j;
    int     found;
    if (!game->matrix_map)
        return;
    found = 0;
    i = 0;
    while (game->matrix_map[i])
    {
        j = 0;
        while (game->matrix_map[i][j])
        {
            if (gnl_strchr("NSWE", game->matrix_map[i][j]))
            {
                p_x = j;
                p_y = i;
                game->player_x = p_x;
                game->player_y = p_y;
                game->player_dir = game->matrix_map[i][j];
                found = 1;
                break; // İlk oyuncuyu bulunca çık (Zaten tek oyuncu kontrolü yapmışsındır)
            }
            j++;
        }
        if (found)
            break;
        i++;
    }
    if (!found) 
    {
        parser_print_err("Player not found for flood fill!");
        exit(1); 
    }
    flood_fill(game->tmp, p_x, p_y, parser_ft_strlen(game->matrix_map[0]), get_matrix_height(game->matrix_map));
}

int parser_handle_map(t_game *game)
{
    size_t max_width;
    size_t max_height;
    int is_player_set;
    is_player_set = false;
    if (!check_rows(game->map , &is_player_set))
        return (0);
    max_width = find_max_width(game->map);
    max_height = parser_get_list_size(game->map);
    game->map_width = max_width;
    game->map_height = max_height;
    fill_map_with_two(game->map , max_width);
    game->matrix_map = list_to_matrix(game->map);
    game->tmp = copy_matrix(game->matrix_map , max_height);
    check_map_closed(game);
    return (1);
}
