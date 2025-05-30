/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:26:32 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/30 17:08:34 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int destroy_all(t_game *game)
{
	ft_printf("DESTROYING\n");
	if (game->image.collect)
	{
		ft_printf("destroying collects\n");
		mlx_destroy_image(game->mlx_ptr, game->image.collect);
	}
	if (game->image.player)
		mlx_destroy_image(game->mlx_ptr, game->image.player);
	if (game->image.exit)
		mlx_destroy_image(game->mlx_ptr, game->image.exit);
	if (game->image.floor)
		mlx_destroy_image(game->mlx_ptr, game->image.floor);
	if (game->image.wall)
		mlx_destroy_image(game->mlx_ptr, game->image.wall);
	clean_grid(game->grid_map);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	clean_and_return(NULL, game->map, 0, 0);
	free(game->mlx_ptr);
	exit(0);
	return (0);
}

void mount_game(char **grid_map, t_image *image, void *mlx_ptr, void *win_ptr)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (grid_map[i])
	{
		j = 0;
		while (grid_map[i][j])
		{
			if (grid_map[i][j] == '1')
				mlx_put_image_to_window(mlx_ptr, win_ptr, image->floor, j * PIXEL_SIZE, i * PIXEL_SIZE);
			else if (grid_map[i][j] == '0')
				mlx_put_image_to_window(mlx_ptr, win_ptr, image->floor, j * PIXEL_SIZE, i * PIXEL_SIZE);
			else if (grid_map[i][j] == 'P')
				mlx_put_image_to_window(mlx_ptr, win_ptr, image->player, j * PIXEL_SIZE, i * PIXEL_SIZE);
			else if (grid_map[i][j] == 'E')
				mlx_put_image_to_window(mlx_ptr, win_ptr, image->floor,  j * PIXEL_SIZE, i * PIXEL_SIZE);
			else if (grid_map[i][j] == 'C')
				mlx_put_image_to_window(mlx_ptr, win_ptr, image->collect, j * PIXEL_SIZE, i * PIXEL_SIZE);
			j++;
		}
		i++;
	}
}

int load_images(t_image *image, void *mlx_ptr)
{
	int	x;
	int y;

	image->collect = mlx_xpm_file_to_image(mlx_ptr, "textures/collect.xpm", &x, &y);
	image->floor = mlx_xpm_file_to_image(mlx_ptr, "textures/floor.xpm", &x, &y);
	image->player = mlx_xpm_file_to_image(mlx_ptr, "textures/player.xpm", &x, &y);
	image->wall = mlx_xpm_file_to_image(mlx_ptr, "textures/wall.xpm", &x, &y);
	image->exit = mlx_xpm_file_to_image(mlx_ptr, "textures/exit.xpm", &x, &y);
	if (!image->collect || !image->floor || !image->player || !image->wall || !image->exit)
		return (0);
	return (1);
}

int	handle_key(int keysym, t_game *game)
{
	destroy_all(game);
	return (0);
	//ft_printf("%d\n", keysym);
	// if (keysym == XK_Escape)
	// 	destroy_all(game->mlx_ptr, game->win_ptr);
}

int	start_game(t_game *game, char **grid_map, t_map *map, int width, int height)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (1);
	// if (!load_images(&game->image, game->mlx_ptr))
	// {
	// 	ft_printf("Loading images error!\n");
	// 	return (free(game->mlx_ptr), 0);
	// }
	game->grid_map = grid_map;
	game->map = map;
	game->win_ptr = mlx_new_window(game->mlx_ptr, width * PIXEL_SIZE, height * PIXEL_SIZE, "so_long 42");
	game->moves = 0;
	// game->map.moves e score.
	if (!game->win_ptr)
		return (free(game->mlx_ptr), 0);
	if (!load_images(&game->image, game->mlx_ptr))
	{
		ft_printf("Loading images error!\n");
		return (free(game->mlx_ptr), 0);
	}
	// Mount window
	mount_game(grid_map, &game->image, game->mlx_ptr, game->win_ptr);
	// Hook actions
	mlx_hook(game->win_ptr, DestroyNotify, StructureNotifyMask, &destroy_all, game);
	// Put X11 in loop waiting for actions.
	mlx_loop(game->mlx_ptr);
	//destroy_all(game);
	return (0);
}


int main(int argc, char **argv)
{
	int		fd;
	t_list	*lst;
	t_map	map;
	char	**grid_map;
	t_game 	game;
	
	if (argc == 2)
	{
		lst = NULL;
		ft_memset(&map, 0, sizeof(t_map));
		ft_memset(&game, 0, sizeof(t_game));
		// map = malloc(sizeof(t_map));
		// if (!map)
		// 	return (1);
		// else
		// 	ft_memset(map, 0, sizeof(t_map));
		// Validar mapa
		grid_map = get_grid_map(&lst, &map, &fd, argv[1]);
		if (!grid_map)
			return (clean_and_return(&lst, &map, fd, 1));
		// Iniciar jogo
		// Preciso do map, e da lst.
		// Map vai conter as coordenadas dos sprites,
		// mais a quantidade de colecaveis
		// Lst vai ter o meu mapa, o que me vai ajudar a renderizar caracter a caracter.
		// para alem de ter a height e width.
		// start_game(lst, map, ft_strlen((char *)lst->content), ft_lstsize(lst));
		//ft_printf("%d %d\n", ft_strlen((char *)lst->content), ft_lstsize(lst));
		close(fd);
		int height = ft_lstsize(lst);
		int width = ft_strlen((char *)lst->content);
		ft_lstclear(&lst, &free);
		start_game(&game, grid_map, &map, width, height);

		// clean_and_return(&lst, &map, fd, 0);
		// clean_grid(grid_map);
	}
	return (0);
}