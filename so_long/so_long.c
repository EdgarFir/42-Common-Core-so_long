/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:26:32 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/29 00:45:30 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	save_map_info(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!i || !line[i + 1])
		{
			if (line[i] != '1')
				return (send_err(MAP_WALL_ERR, 0));
		}
		else
		{
			if (line[i] == 'E')
				map->exits++;
			else if (line[i] == 'C')
				map->collects++;
			else if (line[i] == 'P')
				map->start_pos++;
			else if (line[i] != '0' && line[i] != '1')
				return (send_err(MAP_INV_CHR_ERR, 0));
		}
		i++;
	}
	return (1);
}

int	check_map(t_list *lst)
{
	t_map	map;
	t_list	*curr;

	map.collects = 0;
	map.exits = 0;
	map.start_pos = 0;
	curr = lst;
	while (curr)
	{
		if (curr == lst || !curr->next)
		{
			if (!check_walls(curr->content))
				return (0);
		}
		else
		{
			if (!save_map_info(curr->content, &map))
				return (0);
		}
		curr = curr->next;
	}
	if (map.collects <= 0 || map.exits != 1 || map.start_pos != 1)
		return (send_err(MAP_CHR_ERR, 0));
	return (1);
}

int	is_valid_map(t_list **lst, int *fd, char *filename)
{
	if (!is_valid_path(fd, filename))
		return (0);
	if (!build_map(lst, *fd))
		return (0);
	if (ft_lstsize(*lst) < 3)
		return (send_err(MAP_SIZE_ERR, 0));
	if (!check_map(*lst))
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	int		fd;
	t_list	*lst;

	if (argc == 2)
	{
		lst = NULL;
		if (!is_valid_map(&lst, &fd, argv[1]))
			return (clean_and_return(&lst, fd, 1));
	}
	return (clean_and_return(&lst, fd, 0));
}