/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:31:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/02 01:36:06 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H

# define SO_LONG_BONUS_H

# define SIZE 64
# define FILE_NOT_EXIST "File does not exist."
# define FILE_EXT_ERR "Non compatible map extension."
# define MAP_CHR_ERR "Map must have 1 exit, 1 start and at least 1 collectable and 1 enemy."
# define MAP_INV_CHR_ERR "Map has an invalid character."
# define MAP_WALL_ERR "Map not surronded by walls."
# define MAP_SIZE_ERR "File .ber must have at least 3 lines."
# define MAP_COLLECT_ERR "Invalid map. Collectables not reachable."
# define MAP_EXIT_ERR "Invalid map. Exit not reachable."
# define MAP_RECT_ERR "Map is not a rectangule."

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "X11/keysym.h"
# include "X11/X.h"

typedef struct s_coord
{
	int				x;
	int				y;
	struct s_coord	*next;
}	t_coord;

typedef struct s_map
{
	int		width;
	int		height;
	int		start;
	int		exit;
	int		colls;
	int		enemies;
	t_coord	start_coord;
	t_coord	exit_coord;
	t_coord	*colls_coord;
	t_coord	*enemies_coord;
}	t_map;

typedef struct s_image
{
	void	*collect;
	void	*floor;
	void	*p_f;
	void	*p_up;
	void	*p_lf_1;
	void	*p_lf_2;
	void	*p_rt_1;
	void	*p_rt_2;
	void	*wall;
	void	*exit;
	void	*enemy_1;
	void	*enemy_2;
	int		p_lf_mv;
	int		p_rt_mv;
	int		enemy_mv;
}	t_image;

typedef struct s_game
{
	t_map	map;
	t_image	image;
	char	**grid_map;
	int		score;
	int		moves;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_game;

/* Errors */
int		send_err(char *err, int status);
int		is_valid_path(int *fd, char *filename);
int		is_valid_char(char c);
/* Utils */
char	**create_grid(t_list *lst, int height);
int		save_map_info(char *line, int line_index, t_map *map);
int		build_map(t_list **lst, int fd);
void	reset_map(char **grid_map, t_map *map);
/* Coord utils */
int		coord_addback(t_coord **head, int x, int y);
int		save_coord(t_map *map, int x, int y, char c);
void	coord_lstclear(t_coord **coord_lst);
int		coord_check(t_coord *coord, char **grid_map, char c);
/* Map */
int		check_rectangule(char *line, int *line_len);
int		check_plays(char **grid, t_map *map);
int		check_map(char **grid, t_map *map);
void	mark_plays(char **grid_map, int x, int y, char mark);
/* Clean */
void	clean_grid(char **grid);
int		clean_and_return(t_list **lst, t_game *game, int fd, int status);
int		exit_game(t_game *game);
int		clean_helper(void *ptr1, void *ptr2, void *ptr3, int status);
/* Game */
int		render_img(t_game *game, void *img_ptr, int x, int y);
int		handle_key(int keysym, t_game *game);
void	move_player(int x, int y, t_game *game, char key);
int		load_images(t_image *image, void *mlx_ptr);
void	mount_game(t_game *game);


void	render_player(t_game *game, int x, int y, char key);
int		render_str(t_game *game);
int		render_enemy(t_game *game, int p_x, int p_y, int enemy_mv);


#endif