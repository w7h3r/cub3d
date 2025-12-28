#include "../inc/cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Basit get_next_line placeholder (satır satır oku)
char	*simple_gnl(int fd)
{
	static char	buffer[10000];
	static int	pos = 0;
	static int	read_size = 0;
	char		*line;
	int			i;

	if (pos >= read_size)
	{
		read_size = read(fd, buffer, 9999);
		if (read_size <= 0)
			return (NULL);
		buffer[read_size] = '\0';
		pos = 0;
	}
	
	i = 0;
	line = malloc(1000);
	while (pos < read_size && buffer[pos] != '\n')
		line[i++] = buffer[pos++];
	line[i] = '\0';
	
	if (pos < read_size && buffer[pos] == '\n')
		pos++;
	
	return (line);
}

// Map satırı mı kontrol et (1, 0, N, S, E, W, space içeriyor mu)
int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' 
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W' 
			&& line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

// Map satır sayısını say
int	count_map_lines(char *filename)
{
	int		fd;
	char	*line;
	int		count;
	int		map_started;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	
	count = 0;
	map_started = 0;
	while (1)
	{
		line = simple_gnl(fd);
		if (!line)
			break;
		
		if (is_map_line(line))
		{
			map_started = 1;
			count++;
		}
		else if (map_started)
			break;  // Map bitti
		
		free(line);
	}
	close(fd);
	return (count);
}

// En uzun satırı bul (width)
int	get_map_width(char *filename)
{
	int		fd;
	char	*line;
	int		max_width;
	int		len;

	fd = open(filename, O_RDONLY);
	max_width = 0;
	
	while (1)
	{
		line = simple_gnl(fd);
		if (!line)
			break;
		
		if (is_map_line(line))
		{
			len = strlen(line);
			if (len > max_width)
				max_width = len;
		}
		free(line);
	}
	close(fd);
	return (max_width);
}

// Map'i parse et
void	parse_map(t_map *map, char *filename)
{
	int		fd;
	char	*line;
	int		y;
	int		x;

	// Boyutları hesapla
	map->height = count_map_lines(filename);
	map->width = get_map_width(filename);
	
	printf("Map size: %d x %d\n", map->width, map->height);
	
	// Memory allocate
	map->map_grids = malloc(sizeof(char *) * map->height);
	for (int i = 0; i < map->height; i++)
		map->map_grids[i] = malloc(map->width + 1);
	
	// Dosyayı tekrar aç ve oku
	fd = open(filename, O_RDONLY);
	y = 0;
	
	while (1)
	{
		line = simple_gnl(fd);
		if (!line)
			break;
		
		// Map satırı mı?
		if (is_map_line(line))
		{
			// Satırı kopyala (space ile doldur)
			x = 0;
			while (line[x] && x < map->width)
			{
				map->map_grids[y][x] = line[x];
				x++;
			}
			// Kalan kısmı space ile doldur
			while (x < map->width)
			{
				map->map_grids[y][x] = ' ';
				x++;
			}
			map->map_grids[y][x] = '\0';
			y++;
		}
		free(line);
	}
	close(fd);
}

// Player başlangıç pozisyonunu bul
void	find_player_start(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (data->map->map_grids[y][x] == 'N' 
				|| data->map->map_grids[y][x] == 'S'
				|| data->map->map_grids[y][x] == 'E' 
				|| data->map->map_grids[y][x] == 'W')
			{
				data->player->x_coor = x + 0.5;
				data->player->y_coor = y + 0.5;
				
				// Yönü ayarla
				if (data->map->map_grids[y][x] == 'N')
					data->player->angle = M_PI * 1.5;  // 270° (yukarı)
				else if (data->map->map_grids[y][x] == 'S')
					data->player->angle = M_PI * 0.5;  // 90° (aşağı)
				else if (data->map->map_grids[y][x] == 'E')
					data->player->angle = 0;  // 0° (sağ)
				else if (data->map->map_grids[y][x] == 'W')
					data->player->angle = M_PI;  // 180° (sol)
				
				// Map'te player'ı boşluk yap
				data->map->map_grids[y][x] = '0';
				
				printf("Player start:  (%.1f, %.1f) angle: %.0f°\n",
					data->player->x_coor, data->player->y_coor,
					data->player->angle * 180 / M_PI);
				
				return;
			}
			x++;
		}
		y++;
	}
}

// Ana parser fonksiyonu
void	load_map(t_data *data, char *filename)
{
	parse_map(data->map, filename);
	find_player_start(data);
	update_vectors(data->player);
	
	// Debug: Map'i yazdır
	printf("\n=== MAP ===\n");
	for (int y = 0; y < data->map->height; y++)
		printf("%s\n", data->map->map_grids[y]);
	printf("===========\n\n");
}
