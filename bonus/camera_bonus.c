/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:37:29 by sungyoon          #+#    #+#             */
/*   Updated: 2024/01/04 19:46:47 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	camera_init(t_cub3d *cub3d)
{
	cub3d->render.dir_x = 0;
	cub3d->render.dir_y = 0;
	cub3d->render.plane_x = 0;
	cub3d->render.plane_y = 0;
	if (cub3d->info.start_direction == M_SPAWN_N)
	{
		cub3d->render.dir_x = -1;
		cub3d->render.plane_y = 1;
	}
	else if (cub3d->info.start_direction == M_SPAWN_S)
	{
		cub3d->render.dir_x = 1;
		cub3d->render.plane_y = -1;
	}
	else if (cub3d->info.start_direction == M_SPAWN_E)
	{
		cub3d->render.dir_y = 1;
		cub3d->render.plane_x = 1;
	}
	else
	{
		cub3d->render.dir_y = -1;
		cub3d->render.plane_x = -1;
	}
}

void	camera_rotate(t_cub3d *cub3d, int dir)
{
	double	olddir_x;
	double	oldplane_x;
	double	angle;

	olddir_x = cub3d->render.dir_x;
	oldplane_x = cub3d->render.dir_y;
	if (dir == 0)
		angle = C_ANGLE * M_PI / 180;
	else
		angle = -C_ANGLE * M_PI / 180;
	cub3d->render.dir_x = cub3d->render.dir_x * cos(angle) \
						- cub3d->render.dir_y * sin(angle);
	cub3d->render.dir_y = olddir_x * sin(angle) \
						+ cub3d->render.dir_y * cos(angle);
	cub3d->render.plane_x = cub3d->render.plane_x * cos(angle) \
						- cub3d->render.plane_y * sin(angle);
	cub3d->render.plane_y = oldplane_x * sin(angle) \
						+ cub3d->render.plane_y * cos(angle);
}
