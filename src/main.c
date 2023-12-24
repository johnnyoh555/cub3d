/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:07:42 by jooh              #+#    #+#             */
/*   Updated: 2023/12/24 18:09:38 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_info	info;

	init_info(&info, ac, av);
	for(int y = 0; y < info.height; y++)
	{
		for(int x = 0; x < info.width; x++)
			printf("%d", info.map[y][x]);
		printf("\n");
	}
	return (0);
}
