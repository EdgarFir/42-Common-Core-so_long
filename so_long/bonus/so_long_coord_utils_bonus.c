/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_coord_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:34:11 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/02 11:32:24 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	coord_check(t_coord *coord, char **grid_map, char c)
{
	t_coord	*ptr;

	if (coord)
	{
		ptr = coord;
		while (ptr)
		{
			if (grid_map[ptr->y][ptr->x] != c)
				return (0);
			ptr = ptr->next;
		}
	}
	return (1);
}

t_coord	*coord_lstnew(t_coord *coord, int x, int y)
{
	t_coord	*new;

	new = NULL;
	if (!coord)
	{
		new = malloc(sizeof(t_coord));
		if (!new)
			return (NULL);
		new->next = NULL;
		new->x = x;
		new->y = y;
	}
	else
	{
		coord->x = x;
		coord->y = y;
		coord->next = NULL;
	}
	return (new);
}

int	save_coord(t_map *map, int x, int y, char c)
{
	if (c == 'E')
	{
		coord_lstnew(&map->exit_coord, x, y);
		map->exit++;
	}
	else if (c == 'P')
	{
		coord_lstnew(&map->start_coord, x, y);
		map->start++;
	}
	else if (c == 'C')
	{
		if (!coord_addback(&map->colls_coord, x, y))
			return (0);
		map->colls++;
	}
	else if (c == 'K')
	{
		if (!coord_addback(&map->enemies_coord, x, y))
			return (0);
		map->enemies++;
	}
	return (1);
}

int	coord_addback(t_coord **head, int x, int y)
{
	t_coord	*ptr;
	t_coord	*new;

	new = coord_lstnew(NULL, x, y);
	if (!new)
		return (0);
	if (!(*head))
		*head = new;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (1);
}

void	coord_lstclear(t_coord **coord_lst)
{
	t_coord	*ptr;
	t_coord	*next;

	ptr = *coord_lst;
	while (ptr)
	{
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
	*coord_lst = NULL;
}
