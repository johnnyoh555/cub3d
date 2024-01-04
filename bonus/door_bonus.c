/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:47:27 by jooh              #+#    #+#             */
/*   Updated: 2024/01/04 19:46:47 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	choose_door_img(void)
{
	int	time;

	time = get_time() % 20;
	if (time <= 4)
		return (4);
	if (time <= 9)
		return (5);
	if (time <= 14)
		return (6);
	if (time <= 19)
		return (7);
	return (0);
}

static int	draw_door(t_raycast *raycast, t_cub3d *cub3d, int x)
{
	int				y;
	char			*dst;
	unsigned int	color;

	raycast->tex_x = (int)(raycast->wall_x * raycast->tex_width);
	raycast->tex_x += cub3d->open_door;
	raycast->step = 1.0 * raycast->tex_height / raycast->line_height;
	raycast->tex_pos = raycast->draw_start - SCN_HEIGHT / 2;
	raycast->tex_pos += raycast->line_height / 2;
	raycast->tex_pos *= raycast->step;
	y = raycast->draw_start - 1;
	if (raycast->tex_x >= raycast->tex_width)
		return (0);
	while (++y < raycast->draw_end)
	{
		raycast->tex_y = (int)raycast->tex_pos % raycast->tex_height;
		raycast->tex_pos += raycast->step;
		color = *(unsigned int *)(cub3d->texture[raycast->tex_num].addr + \
				(cub3d->texture[raycast->tex_num].line * raycast->tex_y + \
				raycast->tex_x * (cub3d->texture[raycast->tex_num].bpp / 8)));
		dst = cub3d->mlx.addr + \
			(y * cub3d->mlx.line + x * (cub3d->mlx.bpp / 8));
		*(unsigned int *)dst = color;
	}
	return (1);
}

int	cal_door(t_raycast *raycast, t_cub3d *cub3d, int x)
{
	raycast->line_height = (int)(SCN_HEIGHT / raycast->prep_door_dist);
	raycast->draw_start = -raycast->line_height / 2 + SCN_HEIGHT / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + SCN_HEIGHT / 2;
	if (raycast->draw_end >= SCN_HEIGHT)
		raycast->draw_end = SCN_HEIGHT - 1;
	if (raycast->side_d == 0)
		raycast->wall_x = cub3d->render.pos_y + \
						raycast->prep_door_dist * raycast->raydir_y;
	else
		raycast->wall_x = cub3d->render.pos_x + \
						raycast->prep_door_dist * raycast->raydir_x;
	raycast->wall_x -= floor(raycast->wall_x);
	raycast->tex_num = choose_door_img();
	raycast->tex_width = cub3d->texture[raycast->tex_num].width;
	raycast->tex_height = cub3d->texture[raycast->tex_num].height;
	return (draw_door(raycast, cub3d, x));
}

void	check_if_door(t_raycast *raycast, t_cub3d *cub3d)
{
	if (cub3d->info.map[raycast->map_x][raycast->map_y] == M_DOOR
		&& raycast->door == 0)
	{
		raycast->door = 1;
		raycast->side_d = raycast->side;
		if (raycast->side == 0)
			raycast->prep_door_dist
				= raycast->side_dist_x - raycast->delta_dist_x;
		else
			raycast->prep_door_dist
				= raycast->side_dist_y - raycast->delta_dist_y;
	}
}
