/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:29:58 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/26 23:54:39 by keezgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../lib/get_next_line/get_next_line.h"
# include "cub3d.h"
# include "data_structs.h"
# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// structs removed, defined in data_structs.h

// utils
void	parser_print_err(char *str);
void	parser_putstr_err(char *str);
void	parser_print_err_exit(char *str);
int		parser_ft_strcmp(char *s1, char *s2);
char	*parser_ft_strdup(char *str);
char	*parser_ft_substr(char *s, unsigned int start, size_t len);
char	**parser_ft_split(char *s, char c);
int		parser_ft_atoi(char *str);
size_t	parser_ft_strlen(char *str);

// list utils
void	parser_list_add_back(t_list **list, char *content, int length);
size_t	parser_get_list_size(t_list *list);

// parser
void	parser_read_file(t_game *game, char *file);
void	set_texture(char **path, bool *flag, char *line, int i);
void	set_rgb(t_game *game, char *line, int i, char type);
int		parser_handle_map(t_game *game);

// parser utils
size_t	find_max_width(t_list *map);
int		get_matrix_height(char **map);
char	**copy_matrix(char **map, size_t height);
char	**list_to_matrix(t_list *map);

// map algorithm
void	flood_fill(t_game *game, char **map, int x, int y);
void	set_player_location(t_game *game);

// handle map
int		parser_handle_map(t_game *game);
#endif
