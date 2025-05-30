/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_clean_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:02:26 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/30 16:13:26 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int clean_and_return(t_list **lst, t_map *map, int fd, int status)
{
	if (lst && *lst)
		ft_lstclear(lst, &free);
	if (map->collects_cord)
		ft_coord_lstclear(&map->collects_cord);
	if (fd > 2)
		close(fd);
	return (status);
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
