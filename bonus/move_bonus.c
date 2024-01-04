/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:35:50 by sungyoon          #+#    #+#             */
/*   Updated: 2024/01/04 21:29:47 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	move_foward(t_cub3d *cub3d)
{
	double	cal_x;
	double	cal_y;

	cal_x = cub3d->render.pos_x + cub3d->render.dir_x / 7;
	cal_y = cub3d->render.pos_y + cub3d->render.dir_y / 7;
	if (cub3d->info.map[(int)cal_x][(int)(cub3d->render.pos_y)] >= M_PATH
		&& !(cub3d->info.map[(int)cal_x][(int)(cub3d->render.pos_y)] == M_DOOR
		&& cub3d->move_door))
		cub3d->render.pos_x += cub3d->render.dir_x / 7;
	if (cub3d->info.map[(int)(cub3d->render.pos_x)][(int)cal_y] >= M_PATH
		&& !(cub3d->info.map[(int)(cub3d->render.pos_x)][(int)cal_y] == M_DOOR
		&& cub3d->move_door))
		cub3d->render.pos_y += cub3d->render.dir_y / 7;
}

void	move_back(t_cub3d *cub3d)
{
	double	cal_x;
	double	cal_y;

	cal_x = cub3d->render.pos_x - cub3d->render.dir_x / 7;
	cal_y = cub3d->render.pos_y - cub3d->render.dir_y / 7;
	if (cub3d->info.map[(int)cal_x][(int)(cub3d->render.pos_y)] >= M_PATH
		&& !(cub3d->info.map[(int)cal_x][(int)(cub3d->render.pos_y)] == M_DOOR
		&& cub3d->move_door))
		cub3d->render.pos_x -= cub3d->render.dir_x / 7;
	if (cub3d->info.map[(int)(cub3d->render.pos_x)][(int)cal_y] >= M_PATH
		&& !(cub3d->info.map[(int)(cub3d->render.pos_x)][(int)cal_y] == M_DOOR
		&& cub3d->move_door))
		cub3d->render.pos_y -= cub3d->render.dir_y / 7;
}

void	move_left(t_cub3d *cub3d)
{
	double	cal_x;
	double	cal_y;

	cal_x = cub3d->render.pos_x - cub3d->render.dir_y / 7;
	cal_y = cub3d->render.pos_y + cub3d->render.dir_x / 7;
	if (cub3d->info.map[(int)cal_x][(int)(cub3d->render.pos_y)] >= M_PATH
		&& !(cub3d->info.map[(int)cal_x][(int)(cub3d->render.pos_y)] == M_DOOR
		&& cub3d->move_door))
		cub3d->render.pos_x -= cub3d->render.dir_y / 7;
	if (cub3d->info.map[(int)(cub3d->render.pos_x)][(int)cal_y] >= M_PATH
		&& !(cub3d->info.map[(int)(cub3d->render.pos_x)][(int)cal_y] == M_DOOR
		&& cub3d->move_door))
		cub3d->render.pos_y += cub3d->render.dir_x / 7;
}

void	move_right(t_cub3d *cub3d)
{
	double	cal_x;
	double	cal_y;

	cal_x = cub3d->render.pos_x + cub3d->render.dir_y / 7;
	cal_y = cub3d->render.pos_y - cub3d->render.dir_x / 7;
	if (cub3d->info.map[(int)cal_x][(int)(cub3d->render.pos_y)] >= M_PATH
		&& !(cub3d->info.map[(int)cal_x][(int)(cub3d->render.pos_y)] == M_DOOR
		&& cub3d->move_door))
		cub3d->render.pos_x += cub3d->render.dir_y / 7;
	if (cub3d->info.map[(int)(cub3d->render.pos_x)][(int)cal_y] >= M_PATH
		&& !(cub3d->info.map[(int)(cub3d->render.pos_x)][(int)cal_y] == M_DOOR
		&& cub3d->move_door))
		cub3d->render.pos_y -= cub3d->render.dir_x / 7;
}
