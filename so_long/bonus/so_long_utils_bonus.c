/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:31:04 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/02 00:36:14 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	build_map(t_list **lst, int fd)
{
	char	*line;
	int		line_len;
	t_list	*new;

	line_len = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!check_rectangule(line, &line_len))
		{
			free(line);
			return (send_err("Map is not a rectangule.", 0));
		}
		new = ft_lstnew(line);
		if (!new)
		{
			free(line);
			return (0);
		}
		ft_lstadd_back(lst, new);
	}
	return (1);
}

int	save_map_info(char *line, int line_index, t_map *map)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!i || line[i + 1] == '\0')
		{
			if (line[i] != '1')
				return (send_err(MAP_WALL_ERR, 0));
		}
		else if (is_valid_char(line[i]) && (line[i] != '0' || line[i] != '1'))
		{
			if (!save_coord(map, i, line_index, line[i]))
				return (0);
		}
		else
			return (send_err(MAP_INV_CHR_ERR, 0));
		i++;
	}
	return (1);
}

char	**create_grid(t_list *lst, int height)
{
	char	**grid;
	int		i;
	t_list	*curr;

	grid = malloc(sizeof(char *) * (height + 1));
	if (!grid)
		return (0);
	i = 0;
	curr = lst;
	while (curr)
	{
		grid[i] = ft_strdup(curr->content);
		if (!grid[i])
			return (NULL);
		i++;
		curr = curr->next;
	}
	grid[height] = NULL;
	return (grid);
}

void	reset_map(char **grid_map, t_map *map)
{
	t_coord	*ptr;

	mark_plays(grid_map, map->start_coord.x, map->start_coord.y, '0');
	ptr = map->colls_coord;
	while (ptr)
	{
		grid_map[ptr->y][ptr->x] = 'C';
		ptr = ptr->next;
	}
}

void	mark_plays(char **grid_map, int x, int y, char mark)
{
	if (grid_map[y][x] == '1' || grid_map[y][x] == mark ||
		grid_map[y][x] == 'K' || grid_map[y][x] == 'E')
		return ;
	else if (grid_map[y][x] != 'P')
		grid_map[y][x] = mark;
	mark_plays(grid_map, x, y + 1, mark);
	mark_plays(grid_map, x, y - 1, mark);
	mark_plays(grid_map, x - 1, y, mark);
	mark_plays(grid_map, x + 1, y, mark);
}
