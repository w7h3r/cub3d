/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 06:16:42 by keezgi            #+#    #+#             */
/*   Updated: 2026/01/27 00:00:29 by keezgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static void	save_rgb_to_struct(t_game *game, int *rgb, char type)
{
	if (type == 'F')
	{
		game->parse.floor_r = rgb[0];
		game->parse.floor_g = rgb[1];
		game->parse.floor_b = rgb[2];
		game->parse.floor_set = true;
	}
	else
	{
		game->parse.ceiling_r = rgb[0];
		game->parse.ceiling_g = rgb[1];
		game->parse.ceiling_b = rgb[2];
		game->parse.ceiling_set = true;
	}
}

static void	check_comma_count(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		parser_print_err_exit("Invalid comma count in RGB line!");
}

static void	remove_newline(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '\n')
			str[j] = '\0';
		j++;
	}
}

void	set_rgb(t_game *game, char *line, int i, char type)
{
	char	**tab;
	int		rgb[3];
	int		index;

	index = 0;
	remove_newline(line + i);
	check_comma_count(line + i);
	tab = parser_ft_split(line + i, ',');
	while (tab[index] && index < 3)
	{
		rgb[index] = parser_ft_atoi(tab[index]);
		if (rgb[index] == -1)
		{
			parser_print_err_exit("Invalid RGB value"
				"(must be 0-255 and numeric)!");
		}
		index++;
	}
	if (index != 3)
		parser_print_err_exit("Missing or extra arguments for RGB!");
	save_rgb_to_struct(game, rgb, type);
}

void	set_texture(char **path, bool *flag, char *line, int i)
{
	int	start;

	if (*flag == true)
		parser_print_err_exit("Multiple definition of textures!");
	i += 3;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	*path = parser_ft_substr(line, start, i - start);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
			parser_print_err_exit("Unexpected data after texture path!");
		i++;
	}
	*flag = true;
}
