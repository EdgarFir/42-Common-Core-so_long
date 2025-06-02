/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:26:32 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/02 00:56:27 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	start_game(t_game *game, int w, int h)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return ;
	game->win_ptr = mlx_new_window(game->mlx_ptr, w * SIZE, (h + 1) * SIZE, "42");
	game->moves = 0;
	if (!game->win_ptr)
	{
		free(game->mlx_ptr);
		return ;
	}
	if (!load_images(&game->image, game->mlx_ptr))
		exit_game(game);
	game->image.p_lf_mv = 1;
	game->image.p_rt_mv = 1;
	game->image.enemy_mv = 1;
	mount_game(game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &handle_key, game);
	mlx_hook(game->win_ptr, 17, StructureNotifyMask, &exit_game, game);
	mlx_loop(game->mlx_ptr);
}

char	**get_grid_map(t_list **lst, t_game *game, int *fd, char *filename)
{
	int		lst_size;
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
	for (int i = 0; i < lst_size; i++)
			ft_printf("%s\n", grid_map[i]);
	ft_printf("\n");
	if (!check_map(grid_map, &game->map) || !check_plays(grid_map, &game->map))
	{
		clean_grid(grid_map);
		return (NULL);
	}
	reset_map(grid_map, &game->map);
	game->map.width = ft_strlen(grid_map[0]);
	game->map.height = lst_size;
	return (grid_map);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_list	*lst;
	t_game	game;

	if (argc == 2)
	{
		lst = NULL;
		ft_memset(&game, 0, sizeof(t_game));
		game.grid_map = get_grid_map(&lst, &game, &fd, argv[1]);
		if (!game.grid_map)
			return (clean_and_return(&lst, &game, fd, 1));
		clean_and_return(&lst, &game, fd, 0);
		start_game(&game, game.map.width, game.map.height);
		clean_grid(game.grid_map);
		return (clean_and_return(NULL, &game, 0, 1));
	}
	return (0);
}
