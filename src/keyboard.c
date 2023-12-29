/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:35:01 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/29 20:17:40 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	open_door(t_cub3d *cub3d)
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
		open_door(cub3d);
	return (0);
}
