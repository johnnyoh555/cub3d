/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:37:29 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/25 17:57:40 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
