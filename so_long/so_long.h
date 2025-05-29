/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:31:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/29 00:39:26 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# define FILE_NOT_EXIST "File does not exist."
# define FILE_EXT_ERR "Non compatible map extension."
# define MAP_CHR_ERR "Map must have one exit, one starting position and at least one collectable."
# define MAP_INV_CHR_ERR "Map has an invalid character."
# define MAP_WALL_ERR "Map not surronded by walls."
# define MAP_SIZE_ERR "File .ber must have at least 3 lines."

typedef struct	s_map
{
	int	start_pos;
	int	exits;
	int	collects;
}	t_map;

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

int	send_err(char *err, int status);
int clean_and_return(t_list **lst, int fd, int status);


#endif 