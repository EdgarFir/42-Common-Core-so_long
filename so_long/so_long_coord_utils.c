/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_coord_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:34:11 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/29 15:02:37 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_coord *coord_lstnew(int x, int y)
{
	t_coord	*new;

	new = malloc(sizeof(t_coord));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->x = x;
	new->y = y;
	return (new);
}

int	save_coord(t_map *map, int x, int y, char c)
{
	t_coord *new;

	if (c == 'E')
	{
		map->exit_cord.x = x;
		map->exit_cord.y = y;
		map->exit++;
	}
	else if (c == 'P')
	{
		map->start_pos_cord.x = x;
		map->start_pos_cord.y = y;
		map->start_pos++;
	}
	else if (c == 'C')
	{
		new = coord_lstnew(x, y);
		if (!new)
			return (0);
		coord_addback(&map->collects_cord, new);
		map->collects++;
 	}
	return (1);
}

void coord_addback(t_coord **head, t_coord *new)
{
	t_coord *ptr;

	if (!(*head))
		*head = new;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void ft_coord_lstclear(t_coord **coord_lst)
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
