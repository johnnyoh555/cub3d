/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:35:01 by sungyoon          #+#    #+#             */
/*   Updated: 2024/01/08 14:34:36 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	open_door_flag(t_cub3d *cub3d)
{
	if (cub3d->door_flag == 0)
		return ;
	cub3d->door_flag = 0;
	cub3d->time = get_time();
}

int	read_key(int keycode, t_cub3d *cub3d)
{
	if (keycode == 13)
		move_foward(cub3d);
	else if (keycode == 0)
		move_left(cub3d);
	else if (keycode == 1)
		move_back(cub3d);
	else if (keycode == 2)
		move_right(cub3d);
	else if (keycode == 53)
		cub3d_exit(cub3d);
	else if (keycode == 49)
		open_door_flag(cub3d);
	else if (keycode == 123)
		camera_rotate(cub3d, 0);
	else if (keycode == 124)
		camera_rotate(cub3d, 1);
	return (0);
}
