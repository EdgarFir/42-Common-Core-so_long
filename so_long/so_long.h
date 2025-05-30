/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:31:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/30 16:48:12 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# define PIXEL_SIZE 64
# define FILE_NOT_EXIST "File does not exist."
# define FILE_EXT_ERR "Non compatible map extension."
# define MAP_CHR_ERR "Map must have one exit, one starting position and at least one collectable."
# define MAP_INV_CHR_ERR "Map has an invalid character."
# define MAP_WALL_ERR "Map not surronded by walls."
# define MAP_SIZE_ERR "File .ber must have at least 3 lines."
# define MAP_COLLECT_ERR "Invalid map. Collectables not reachable."
# define MAP_EXIT_ERR "Invalid map. Exit not reachable."

typedef struct s_coord
{
	int				x;
	int				y;
	struct s_coord *next;
}	t_coord;

typedef struct	s_map
{
	int		start_pos;
	int		exit;
	int		collects;
	t_coord	start_pos_cord;
	t_coord	exit_cord;
	t_coord	*collects_cord;
}	t_map;

typedef struct s_image
{
	void	*collect;
	void	*floor;
	void 	*player;
	void	*wall;
	void	*exit;
} t_image;

typedef struct s_game
{
	t_map	*map;
	t_image image;
	char	**grid_map;
	int		score;
	int		moves;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_game;


# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "X11/keysym.h"
# include "X11/X.h"

/* Errors */
int		send_err(char *err, int status);
int		clean_and_return(t_list **lst, t_map *map, int fd, int status);
int		is_valid_char(char c);
char	**get_grid_map(t_list **lst, t_map *map, int *fd, char *filename);
/* Utils */
char	**create_grid(t_list *lst, int height);
void	clean_grid(char **grid);
int		is_valid_path(int *fd, char *filename);
int		save_map_info(char *line, int line_index, t_map *map);
int		build_map(t_list **lst, int fd);
/* Coord utils */
void	coord_addback(t_coord **head, t_coord *new);
int		save_coord(t_map *map, int x, int y, char c);
void	ft_coord_lstclear(t_coord **coord_lst);
int		coord_check(t_coord *coord, char **grid_map, char c);
/* Map */
int		check_rectangule(int *line_len, int *curr_len);
int		check_valid_plays(char **grid, t_map map);
int		check_map(char **grid, t_map *map);
void	mark_valid_plays(char **grid_map, int x, int y, char mark);


#endif