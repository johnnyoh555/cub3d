/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_motion_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:04:54 by jooh              #+#    #+#             */
/*   Updated: 2024/01/04 19:46:47 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	close_door(t_cub3d *cub3d)
{
	if (cub3d->open_door > 0 && cub3d->close == 1)
		cub3d->open_door -= 4;
	if (cub3d->open_door == 0 && cub3d->close == 1)
	{
		cub3d->close = 0;
		cub3d->door_flag = 1;
	}
}

void	open_door(t_cub3d *cub3d)
{
	if (cub3d->open_door < cub3d->texture[4].width)
		cub3d->open_door += 4;
	if (cub3d->open_door == cub3d->texture[4].width)
	{
		cub3d->move_door = 0;
		cub3d->time = get_time();
	}
}
