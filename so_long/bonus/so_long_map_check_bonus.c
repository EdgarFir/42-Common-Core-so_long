/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map_check_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:29:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/02 01:00:39 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_exit(char **grid_map, int x, int y)
{
	int	no_x;

	no_x = 1;
	if (grid_map[y][x + 1] != 'X' && grid_map[y][x - 1] != 'X' &&
		grid_map[y + 1][x] != 'X' && grid_map[y - 1][x] != 'X')
		no_x = 0;
	if (!no_x)
	{
		if (grid_map[y][x + 1] != 'P' && grid_map[y][x - 1] != 'P' &&
		grid_map[y + 1][x] != 'P' && grid_map[y - 1][x] != 'P')
			return (0);
	}
	return (1);
}

int	check_plays(char **grid_map, t_map *map)
{
	int	e_x;
	int	e_y;

	mark_plays(grid_map, map->start_coord.x, map->start_coord.y, 'X');
	if (!coord_check(map->colls_coord, grid_map, 'X'))
		return (send_err(MAP_COLLECT_ERR, 0));
	e_x = map->exit_coord.x;
	e_y = map->exit_coord.y;
	if (!check_exit(grid_map, e_x, e_y))
		return (send_err(MAP_EXIT_ERR, 0));
	return (1);
}

int	check_rectangule(char *line, int *line_len)
{
	int	curr_len;

	curr_len = ft_strlen(line);
	if (line[curr_len - 1] == '\n')
	{
		line[curr_len - 1] = '\0';
		curr_len--;
	}
	if (!(*line_len))
		*line_len = curr_len;
	else if (*line_len != curr_len)
		return (0);
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

	ft_memset(map, 0, sizeof(map));
	i = 0;
	while (grid[i])
	{
		if (!i || grid[i + 1] == NULL)
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
	if (map->colls <= 0 || map->exit != 1 
		|| map->start != 1 || map->enemies <= 0)
		return (send_err(MAP_CHR_ERR, 0));
	return (1);
}
