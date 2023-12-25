/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:07:42 by jooh              #+#    #+#             */
/*   Updated: 2023/12/25 17:49:00 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cub3d	*cub3d;

	cub3d = ft_calloc(1, sizeof(t_cub3d));
	ft_memset(cub3d, 0, sizeof(t_cub3d));
	init_info(&cub3d->info, ac, av);
	if (cub3d_init(cub3d) == 1)
		exit(1);
	return (0);
}
