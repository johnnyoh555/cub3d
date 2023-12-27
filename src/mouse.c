/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:00:23 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/27 16:55:31 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_mouse(int x, int y, t_cub3d *cub3d)
{
	int	dir;

	dir = -1;
	if (cub3d->render.pre_x - x < -1)
		dir = 1;
	else if (cub3d->render.pre_x - x > 1)
		dir = 0;
	else
	{
		if (x < 0 && cub3d->render.pre_dir == 0)
			dir = 0;
		else if (x > SCN_WIDTH && cub3d->render.pre_dir == 1)
			dir = 1;
	}
	if (dir > -1)
		camera_rotate(cub3d, dir);
	cub3d->render.pre_x = x;
	cub3d->render.pre_y = y;
	cub3d->render.pre_dir = dir;
	return (0);
}
