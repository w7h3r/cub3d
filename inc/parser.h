/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:29:58 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/25 18:11:18 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

# include "../lib/get_next_line/get_next_line.h"
# include "data_structs.h"

void	parser_print_err(char *str);
void	parser_putstr_err(char *str);
int		parser_ft_strcmp(char *s1, char *s2);
char	*parser_ft_strdup(char *str);
char	*parser_ft_substr(char *s, unsigned int start, size_t len);
char	**parser_ft_split(char *s, char c);
int		parser_ft_atoi(char *str);
size_t	parser_ft_strlen(char *str);

void	parser_list_add_back(t_list **list, char *content, int length);
size_t	parser_get_list_size(t_list *list);

int		parser_arg_parse(char *str);

void	parser_read_file(t_game *game, char *file);

int		parser_handle_map(t_game *game);

#endif
