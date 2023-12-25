/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:35:50 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/25 17:29:23 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_foward(t_cub3d *cub3d)
{
	int	cal_x;
	int	cal_y;

	cal_x = cub3d->render.pos_x + cub3d->render.dir_x;
	cal_y = cub3d->render.pos_y + cub3d->render.dir_y;
	if (cub3d->info.map[cal_x][(int)(cub3d->render.pos_y)] == M_PATH)
		cub3d->render.pos_x += cub3d->render.dir_x / 2;
	if (cub3d->info.map[(int)(cub3d->render.pos_x)][cal_y] == M_PATH)
		cub3d->render.pos_y += cub3d->render.dir_y / 2;
}

void	move_back(t_cub3d *cub3d)
{
	int	cal_x;
	int	cal_y;

	cal_x = cub3d->render.pos_x - cub3d->render.dir_x;
	cal_y = cub3d->render.pos_y - cub3d->render.dir_y;
	if (cub3d->info.map[cal_x][(int)(cub3d->render.pos_y)] == M_PATH)
		cub3d->render.pos_x -= cub3d->render.dir_x / 2;
	if (cub3d->info.map[(int)(cub3d->render.pos_x)][cal_y] == M_PATH)
		cub3d->render.pos_y -= cub3d->render.dir_y / 2;
}

void	move_left(t_cub3d *cub3d)
{
	int	cal_x;
	int	cal_y;

	cal_x = cub3d->render.pos_x - cub3d->render.dir_y;
	cal_y = cub3d->render.pos_y + cub3d->render.dir_x;
	if (cub3d->info.map[cal_x][(int)(cub3d->render.pos_y)] == M_PATH)
		cub3d->render.pos_x -= cub3d->render.dir_y / 2;
	if (cub3d->info.map[(int)(cub3d->render.pos_x)][cal_y] == M_PATH)
		cub3d->render.pos_y += cub3d->render.dir_x / 2;
}

void	move_right(t_cub3d *cub3d)
{
	int	cal_x;
	int	cal_y;

	cal_x = cub3d->render.pos_x + cub3d->render.dir_y;
	cal_y = cub3d->render.pos_y - cub3d->render.dir_x;
	if (cub3d->info.map[cal_x][(int)(cub3d->render.pos_y)] == M_PATH)
		cub3d->render.pos_x += cub3d->render.dir_y / 2;
	if (cub3d->info.map[(int)(cub3d->render.pos_x)][cal_y] == M_PATH)
		cub3d->render.pos_y -= cub3d->render.dir_x / 2;
}
