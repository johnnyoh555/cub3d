/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_motion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:04:54 by jooh              #+#    #+#             */
/*   Updated: 2024/01/03 11:43:45 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
