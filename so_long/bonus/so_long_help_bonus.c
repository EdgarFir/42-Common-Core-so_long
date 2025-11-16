/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_help_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:30:56 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/02 12:27:28 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	mount_counter(t_game *game, int color, char *str)
{
	int	x;
	int	y;

	x = 32;
	y = game->map.height * SIZE + 32;
	mlx_string_put(game->mlx_ptr, game->win_ptr, x, y, color, str);
}

int	render_enemy(t_game *game, int p_x, int p_y, int enemy_mv)
{
	void	*img_ptr;

	if (enemy_mv == 1)
		img_ptr = game->image.enemy_1;
	else
		img_ptr = game->image.enemy_2;
	if (game->grid_map[p_y - 1][p_x] == 'K')
		return (render_img(game, img_ptr, p_x * SIZE, (p_y - 1) * SIZE));
	else if (game->grid_map[p_y + 1][p_x] == 'K')
		return (render_img(game, img_ptr, p_x * SIZE, (p_y + 1) * SIZE));
	else if (game->grid_map[p_y][p_x + 1] == 'K')
		return (render_img(game, img_ptr, (p_x + 1) * SIZE, p_y * SIZE));
	else if (game->grid_map[p_y][p_x - 1] == 'K')
		return (render_img(game, img_ptr, (p_x - 1) * SIZE, p_y * SIZE));
	return (0);
}

int	render_str(t_game *game)
{
	char	*moves_nbr;
	char	*old_moves_nbr;
	char	*str;

	game->moves++;
	moves_nbr = ft_itoa(game->moves);
	if (!moves_nbr)
		return (0);
	old_moves_nbr = ft_itoa(game->moves - 1);
	if (!old_moves_nbr)
		return (clean_helper(moves_nbr, NULL, NULL, 0));
	str = ft_strjoin("Moves: ", old_moves_nbr);
	if (!str)
		return (clean_helper(moves_nbr, old_moves_nbr, NULL, 0));
	mount_counter(game, BLACK, str);
	free(str);
	str = ft_strjoin("Moves: ", moves_nbr);
	if (!str)
		return (clean_helper(moves_nbr, old_moves_nbr, NULL, 0));
	mount_counter(game, RED, str);
	return (clean_helper(moves_nbr, old_moves_nbr, str, 1));
}

void	render_side_moves(t_game *game, int x, int y, char key)
{
	if (key == 'a')
	{
		if (game->image.p_lf_mv == 1)
		{
			game->image.p_lf_mv = 2;
			render_img(game, game->image.p_lf_2, x, y);
		}
		else
		{
			game->image.p_lf_mv = 1;
			render_img(game, game->image.p_lf_1, x, y);
		}
		return ;
	}
	if (game->image.p_rt_mv == 1)
	{
		game->image.p_rt_mv = 2;
		render_img(game, game->image.p_rt_2, x, y);
	}
	else
	{
		game->image.p_rt_mv = 1;
		render_img(game, game->image.p_rt_1, x, y);
	}
}

void	render_player(t_game *game, int x, int y, char key)
{
	if (key == 'w')
		render_img(game, game->image.p_up, x, y);
	else if (key == 's')
		render_img(game, game->image.p_f, x, y);
	else
		render_side_moves(game, x, y, key);
}
