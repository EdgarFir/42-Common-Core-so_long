/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:31:04 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/29 15:02:08 by edfreder         ###   ########.fr       */
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

int is_valid_path(int *fd, char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		ft_putendl_fd(FILE_NOT_EXIST, 2);
		return (0);
	}
	if (ft_strcmp(extension, ".ber"))
	{
		ft_putendl_fd(FILE_EXT_ERR, 2);
		return (0);
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

void	clean_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}