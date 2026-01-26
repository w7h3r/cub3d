/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:52:55 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/26 23:56:07 by keezgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	handle_map_line(t_game *game, char *line)
{
	if (!game->parse.north_set || !game->parse.south_set
		|| !game->parse.west_set || !game->parse.east_set
		|| !game->parse.floor_set || !game->parse.ceiling_set)
	{
		parser_print_err_exit("Missing textures before map!");
	}
	game->parse.is_map_started = true;
	parser_list_add_back(&game->map, parser_ft_strdup(line),
		parser_ft_strlen(line));
}

static void	process_line(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
	{
		if (game->parse.is_map_started)
			parser_print_err_exit("Map can't be seperated with newline!");
		return ;
	}
	if (!ft_strncmp(&line[i], "NO ", 3))
		set_texture(&game->parse.north_file, &game->parse.north_set, line, i);
	else if (!ft_strncmp(&line[i], "SO ", 3))
		set_texture(&game->parse.south_file, &game->parse.south_set, line, i);
	else if (!ft_strncmp(&line[i], "WE ", 3))
		set_texture(&game->parse.west_file, &game->parse.west_set, line, i);
	else if (!ft_strncmp(&line[i], "EA ", 3))
		set_texture(&game->parse.east_file, &game->parse.east_set, line, i);
	else if (!ft_strncmp(&line[i], "F ", 2))
		set_rgb(game, line, i + 2, 'F');
	else if (!ft_strncmp(&line[i], "C ", 2))
		set_rgb(game, line, i + 2, 'C');
	else
		handle_map_line(game, line);
}

void	parser_read_file(t_game *game, char *file)
{
	int		fd;
	char	*line;

	ft_bzero(&game->parse, sizeof(t_parse));
	game->map = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		parser_print_err_exit("File doesn't have read permission!");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		process_line(game, line);
	}
	close(fd);
	if (!game->map)
		parser_print_err_exit("Map not found!");
}
