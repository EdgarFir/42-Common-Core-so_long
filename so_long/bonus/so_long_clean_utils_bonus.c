/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_clean_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:02:26 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/02 00:55:50 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	clean_and_return(t_list **lst, t_game *game, int fd, int status)
{
	if (lst && *lst)
		ft_lstclear(lst, &free);
	if (game)
	{
		if (game->map.colls_coord)
			coord_lstclear(&game->map.colls_coord);
		if (game->map.enemies_coord)
			coord_lstclear(&game->map.enemies_coord);
	}
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

void	destroy_images(t_game *game)
{
	if (game->image.collect)
		mlx_destroy_image(game->mlx_ptr, game->image.collect);
	if (game->image.p_f)
		mlx_destroy_image(game->mlx_ptr, game->image.p_f);
	if (game->image.p_lf_1)
		mlx_destroy_image(game->mlx_ptr, game->image.p_lf_1);
	if (game->image.p_lf_2)
		mlx_destroy_image(game->mlx_ptr, game->image.p_lf_2);
	if (game->image.p_rt_1)
		mlx_destroy_image(game->mlx_ptr, game->image.p_rt_1);
	if (game->image.p_rt_2)
		mlx_destroy_image(game->mlx_ptr, game->image.p_rt_2);
	if (game->image.p_up)
		mlx_destroy_image(game->mlx_ptr, game->image.p_up);
	if (game->image.exit)
		mlx_destroy_image(game->mlx_ptr, game->image.exit);
	if (game->image.floor)
		mlx_destroy_image(game->mlx_ptr, game->image.floor);
	if (game->image.wall)
		mlx_destroy_image(game->mlx_ptr, game->image.wall);
	if (game->image.enemy_1)
		mlx_destroy_image(game->mlx_ptr, game->image.enemy_1);
	if (game->image.enemy_2)
		mlx_destroy_image(game->mlx_ptr, game->image.enemy_2);
}

int	exit_game(t_game *game)
{
	destroy_images(game);
	clean_grid(game->grid_map);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	clean_and_return(NULL, game, 0, 0);
	free(game->mlx_ptr);
	exit(0);
	return (0);
}

int	clean_helper(void *ptr1, void *ptr2, void *ptr3, int status)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	return (status);
}

