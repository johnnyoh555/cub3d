/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:04:26 by sungyoon          #+#    #+#             */
/*   Updated: 2024/01/03 11:37:31 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_init(t_raycast *raycast, t_cub3d *cub3d, int x)
{
	raycast->camera_x = 2 * x / (double)SCN_WIDTH - 1;
	raycast->raydir_x = cub3d->render.dir_x;
	raycast->raydir_x += cub3d->render.plane_x * raycast->camera_x;
	raycast->raydir_y = cub3d->render.dir_y;
	raycast->raydir_y += cub3d->render.plane_y * raycast->camera_x;
	raycast->map_x = cub3d->render.pos_x;
	raycast->map_y = cub3d->render.pos_y;
	if (raycast->raydir_x == 0)
		raycast->delta_dist_x = 1e30;
	else
		raycast->delta_dist_x = fabs(1 / raycast->raydir_x);
	if (raycast->raydir_y == 0)
		raycast->delta_dist_y = 1e30;
	else
		raycast->delta_dist_y = fabs(1 / raycast->raydir_y);
	raycast->hit = 0;
	raycast->door = 0;
	raycast->sprit = 0;
}

void	raycast_cal_side_dist(t_raycast *raycast, t_cub3d *cub3d)
{
	if (raycast->raydir_x < 0)
	{
		raycast->step_x = -1;
		raycast->side_dist_x = cub3d->render.pos_x - raycast->map_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_dist_x = raycast->map_x + 1.0 - cub3d->render.pos_x;
	}
	raycast->side_dist_x *= raycast->delta_dist_x;
	if (raycast->raydir_y < 0)
	{
		raycast->step_y = -1;
		raycast->side_dist_y = cub3d->render.pos_y - raycast->map_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->side_dist_y = raycast->map_y + 1.0 - cub3d->render.pos_y;
	}
	raycast->side_dist_y *= raycast->delta_dist_y;
}

void	raycast_find_wall(t_raycast *raycast, t_cub3d *cub3d)
{
	while (raycast->hit == 0)
	{
		if (raycast->side_dist_x < raycast->side_dist_y)
		{
			raycast->side_dist_x += raycast->delta_dist_x;
			raycast->map_x += raycast->step_x;
			raycast->side = 0;
		}
		else
		{
			raycast->side_dist_y += raycast->delta_dist_y;
			raycast->map_y += raycast->step_y;
			raycast->side = 1;
		}
		if (cub3d->info.map[raycast->map_x][raycast->map_y] == M_SPRIT
			|| (cub3d->info.map[raycast->map_x][raycast->map_y] == M_DOOR))
			check_sprit_door(raycast, cub3d);
		if (cub3d->info.map[raycast->map_x][raycast->map_y] == M_WALL)
			raycast->hit = 1;
	}
	if (raycast->side == 0)
		raycast->prep_wall_dist = raycast->side_dist_x - raycast->delta_dist_x;
	else
		raycast->prep_wall_dist = raycast->side_dist_y - raycast->delta_dist_y;
}

void	raycast_cal_and_sel_wall(t_raycast *raycast, t_cub3d *cub3d)
{
	raycast->line_height = (int)(SCN_HEIGHT / raycast->prep_wall_dist);
	raycast->draw_start = -raycast->line_height / 2 + SCN_HEIGHT / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + SCN_HEIGHT / 2;
	if (raycast->draw_end >= SCN_HEIGHT)
		raycast->draw_end = SCN_HEIGHT - 1;
	if (raycast->side == 0)
		raycast->wall_x = cub3d->render.pos_y + \
						raycast->prep_wall_dist * raycast->raydir_y;
	else
		raycast->wall_x = cub3d->render.pos_x + \
						raycast->prep_wall_dist * raycast->raydir_x;
	raycast->wall_x -= floor(raycast->wall_x);
	if (raycast->side == 0 && raycast->raydir_x > 0)
		raycast->tex_num = 0;
	else if (raycast->side == 0 && raycast->raydir_x <= 0)
		raycast->tex_num = 1;
	else if (raycast->side == 1 && raycast->raydir_y < 0)
		raycast->tex_num = 2;
	else if (raycast->side == 1 && raycast->raydir_y >= 0)
		raycast->tex_num = 3;
	raycast->tex_width = cub3d->texture[raycast->tex_num].width;
	raycast->tex_height = cub3d->texture[raycast->tex_num].height;
}
