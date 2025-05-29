/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_error_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:47:27 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/29 14:56:39 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	send_err(char *err, int status)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err, 2);
	return (status);
}

int clean_and_return(t_list **lst, t_coord **coord_lst, int fd, int status)
{
	if (*lst)
		ft_lstclear(lst, &free);
	if (*coord_lst)
		ft_coord_lstclear(coord_lst);
	if (fd > 2)
		close(fd);
	return (status);
}

int is_valid_char(char c)
{
	char	*valid_chars;

	valid_chars = "10EPC";
	if (!ft_strchr(valid_chars, c))
		return (0);
	return (1);
}