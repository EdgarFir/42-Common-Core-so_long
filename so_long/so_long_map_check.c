/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:29:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/29 16:59:49 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int is_to_fill(char **grid, int x, int y)
{
	// Check down
	if (grid[y][x] == '0')
	{
		// Check down
		if (grid[y - 1][x] == 'P' || grid[y - 1][x] == 'F' || grid[y - 1][x] == '0')
			return (1);
		// Check up
		if (grid[y + 1][x] == 'P' || grid[y + 1][x] == 'F' || grid[y + 1][x] == '0')
			return (1);
		// Check left
		if (grid[y][x - 1] == 'P' || grid[y][x - 1] == 'F' || grid[y][x - 1] == '0')
			return (1);
		// Check right
		if (grid[y][x + 1] == 'P' || grid[y][x + 1] == 'F' || grid[y][x + 1] == '0')
			return (1);
	}
	return (0);
}

void fill(int start_coord[2], int width, char **grid)
{
	int temp_width;
	int	temp_height;

	temp_height = start_coord[0];
	temp_width = start_coord[1];
	while (temp_height >= 1)
	{
		//temp_width = start_coord[1];
		while (grid[temp_height][temp_width] != '1')
		{
			if (is_to_fill(grid, temp_width, temp_height))
				grid[temp_height][temp_width] = 'F';
			temp_width--;
		}
		temp_width = 1;
		ft_printf("%d\n", temp_width);
		temp_height--;
	}
}

int	is_playable_map(char **grid, int width, t_map map)
{
	int start_coord[2];

	start_coord[0] = map.start_pos_cord.y;
	start_coord[1] = map.start_pos_cord.x;
	fill(start_coord, width, grid);
	return (1);
}

int	check_rectangule(int *line_len, int *curr_len)
{
	if (!(*line_len))
		*line_len = *curr_len;
	else
	{
		if (*line_len != *curr_len)
			return (0);
	}
	return (1);
}

int	check_walls(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			return (send_err(MAP_WALL_ERR, 0));
		i++;
	}
	return (1);
}

int	check_map(char **grid, t_map *map)
{
	int		i;

	map->collects = 0;
	map->exit = 0;
	map->start_pos = 0;
	map->collects_cord = NULL;
	i = 0;
	while (grid[i])
	{
		if (!i || !grid[i + 1])
		{
			if (!check_walls(grid[i]))
				return (0);
		}
		else
		{
			if (!save_map_info(grid[i], i, map))
				return (0);
		}
		i++;
	}
	if (map->collects <= 0 || map->exit != 1 || map->start_pos != 1)
		return (send_err(MAP_CHR_ERR, 0));
	return (1);
}

int	is_valid_map(t_list **lst, t_map *map, int *fd, char *filename)
{
	int 	lst_size;
	char	**grid;

	if (!is_valid_path(fd, filename))
		return (0);
	if (!build_map(lst, *fd))
		return (0);
	lst_size = ft_lstsize(*lst);
	if (lst_size < 3)
		return (send_err(MAP_SIZE_ERR, 0));
	grid = create_grid(*lst, lst_size);
	if (!grid)
		return (0);
	if (!check_map(grid, map))
		return (0);
	if (!is_playable_map(grid, ft_strlen(grid[0]), *map))
		return (0);
	// Clean grid.
	int i = 0;
	while (grid[i])
	{
		ft_printf("%s\n", grid[i]);
		i++;
	}
	clean_grid(grid);
	return (1);
}
