/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_game_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 21:59:30 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/02 13:51:10 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	render_img(t_game *game, void *img_ptr, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img_ptr, x, y);
	return (1);
}

void	mount_game(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (game->grid_map[i])
	{
		j = 0;
		while (game->grid_map[i][j])
		{
			if (game->grid_map[i][j] == '1')
				render_img(game, game->image.wall, j * SIZE, i * SIZE);
			else if (game->grid_map[i][j] == '0')
				render_img(game, game->image.floor, j * SIZE, i * SIZE);
			else if (game->grid_map[i][j] == 'P')
				render_img(game, game->image.p_f, j * SIZE, i * SIZE);
			else if (game->grid_map[i][j] == 'E')
				render_img(game, game->image.exit, j * SIZE, i * SIZE);
			else if (game->grid_map[i][j] == 'C')
				render_img(game, game->image.collect, j * SIZE, i * SIZE);
			else if (game->grid_map[i][j] == 'K')
				render_img(game, game->image.enemy_1, j * SIZE, i * SIZE);
			j++;
		}
		i++;
	}
}

int	load_images(t_image *image, void *mlx_ptr)
{
	int	x;
	int	y;

	image->collect = mlx_xpm_file_to_image(mlx_ptr, "textures/c.xpm", &x, &y);
	image->floor = mlx_xpm_file_to_image(mlx_ptr, "textures/0.xpm", &x, &y);
	image->p_f = mlx_xpm_file_to_image(mlx_ptr, "textures/pf.xpm", &x, &y);
	image->p_lf_1 = mlx_xpm_file_to_image(mlx_ptr, "textures/pl1.xpm", &x, &y);
	image->p_lf_2 = mlx_xpm_file_to_image(mlx_ptr, "textures/pl2.xpm", &x, &y);
	image->p_rt_1 = mlx_xpm_file_to_image(mlx_ptr, "textures/pr1.xpm", &x, &y);
	image->p_rt_2 = mlx_xpm_file_to_image(mlx_ptr, "textures/pr2.xpm", &x, &y);
	image->p_up = mlx_xpm_file_to_image(mlx_ptr, "textures/pu.xpm", &x, &y);
	image->wall = mlx_xpm_file_to_image(mlx_ptr, "textures/1.xpm", &x, &y);
	image->exit = mlx_xpm_file_to_image(mlx_ptr, "textures/e.xpm", &x, &y);
	image->enemy_1 = mlx_xpm_file_to_image(mlx_ptr, "textures/en1.xpm", &x, &y);
	image->enemy_2 = mlx_xpm_file_to_image(mlx_ptr, "textures/en2.xpm", &x, &y);
	if (!image->collect || !image->floor || !image->p_f || !image->p_lf_1
		|| !image->p_lf_2 || !image->p_rt_1 || !image->p_rt_2 || !image->p_up
		|| !image->wall || !image->exit || !image->enemy_1 || !image->enemy_2)
		return (send_err("Can't load images.", 0));
	return (1);
}

void	move_player(int x, int y, t_game *game, char key)
{
	int	old_x;
	int	old_y;

	old_x = game->map.start_coord.x;
	old_y = game->map.start_coord.y;
	if (game->grid_map[y][x] == 'C' || game->grid_map[y][x] == '0')
	{
		game->grid_map[old_y][old_x] = '0';
		if (game->grid_map[y][x] == 'C')
			game->score++;
		game->grid_map[y][x] = '0';
		render_str(game);
		render_img(game, game->image.floor, old_x * SIZE, old_y * SIZE);
		render_player(game, x * SIZE, y * SIZE, key);
		game->map.start_coord.x = x;
		game->map.start_coord.y = y;
		if (game->image.enemy_mv == 2)
			render_enemy(game, old_x, old_y, 1);
		if (render_enemy(game, x, y, 2))
			game->image.enemy_mv = 2;
	}
	else if (game->grid_map[y][x] == 'K'
		|| (game->grid_map[y][x] == 'E' && game->score == game->map.colls))
		exit_game(game);
}

int	handle_key(int keysym, t_game *game)
{
	int	x;
	int	y;

	x = game->map.start_coord.x;
	y = game->map.start_coord.y;
	if (keysym == XK_w)
		move_player(x, y - 1, game, 'w');
	else if (keysym == XK_s)
		move_player(x, y + 1, game, 's');
	else if (keysym == XK_a)
		move_player(x - 1, y, game, 'a');
	else if (keysym == XK_d)
		move_player(x + 1, y, game, 'd');
	else if (keysym == XK_Escape)
		exit_game(game);
	return (0);
}
