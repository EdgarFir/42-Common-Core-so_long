/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:31:04 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/30 12:09:48 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	build_map(t_list **lst, int fd)
{
	char	*line;
	int		line_len;
	int		curr_len;
	t_list	*new;

	line_len = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		curr_len = ft_strlen(line);
		line[curr_len - 1] = '\0';
		new = ft_lstnew(line);
		if (!new)
		{
			free(line);
			return (0);
		}
		ft_lstadd_back(lst, new);
		if (!check_rectangule(&line_len, &curr_len))
			return (send_err("Map is not a rectangule.", 0));
	}
	return (1);
}

int	save_map_info(char *line, int line_index, t_map *map)
{
	int	i;

	i = 0;
	while (line[i + 1])
	{
		if (!i || !line[i + 1])
		{
			if (line[i] != '1')
				return (send_err(MAP_WALL_ERR, 0));
		}
		else if (is_valid_char(line[i]))
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

void reset_map(char **grid_map, t_map *map)
{
	t_coord *ptr;

	mark_valid_plays(grid_map, map->start_pos_cord.x, map->start_pos_cord.y, '0');
	ptr = map->collects_cord;
	while (ptr)
	{
		grid_map[ptr->y][ptr->x] = 'C';
		ptr = ptr->next;
	}
}

char	**get_grid_map(t_list **lst, t_map *map, int *fd, char *filename)
{
	int 	lst_size;
	char	**grid_map;

	if (!is_valid_path(fd, filename))
		return (NULL);
	if (!build_map(lst, *fd))
		return (NULL);
	lst_size = ft_lstsize(*lst);
	if (lst_size < 3)
	{
		send_err(MAP_SIZE_ERR, 0);
		return (NULL);
	}
	grid_map = create_grid(*lst, lst_size);
	if (!grid_map)
		return (NULL);
	if (!check_map(grid_map, map) || !check_valid_plays(grid_map, *map))
	{
		clean_grid(grid_map);
		return (NULL);
	}
	reset_map(grid_map, map);
	return (grid_map);
}

