/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:26:32 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/29 14:53:43 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
	int		fd;
	t_list	*lst;
	t_map	map;

	if (argc == 2)
	{
		lst = NULL;
		if (!is_valid_map(&lst, &map, &fd, argv[1]))
			return (clean_and_return(&lst, &map.collects_cord, fd, 1));
	}
	return (0);
}