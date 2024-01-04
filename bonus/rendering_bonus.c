/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:53:08 by sungyoon          #+#    #+#             */
/*   Updated: 2024/01/04 19:46:47 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_background(t_cub3d *cub3d)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	while (i < SCN_HEIGHT)
	{
		j = 0;
		while (j < SCN_WIDTH)
		{
			dst = cub3d->mlx.addr + \
				(i * cub3d->mlx.line + j * (cub3d->mlx.bpp / 8));
			if (i < SCN_HEIGHT / 2)
				*(unsigned int *)dst = cub3d->info.c_color;
			else
				*(unsigned int *)dst = cub3d->info.f_color;
			j++;
		}
		i++;
	}
}

void	draw_raycast(t_raycast *raycast, t_cub3d *cub3d, int x)
{
	int				y;
	char			*dst;
	unsigned int	color;

	raycast->tex_x = (int)(raycast->wall_x * raycast->tex_width);
	if ((raycast->side == 0 && raycast->raydir_x > 0) || \
		(raycast->side == 1 && raycast->raydir_y < 0))
		raycast->tex_x = raycast->tex_width - raycast->tex_x - 1;
	raycast->step = 1.0 * raycast->tex_height / raycast->line_height;
	raycast->tex_pos = raycast->draw_start - SCN_HEIGHT / 2;
	raycast->tex_pos += raycast->line_height / 2;
	raycast->tex_pos *= raycast->step;
	y = raycast->draw_start;
	while (y < raycast->draw_end)
	{
		raycast->tex_y = (int)raycast->tex_pos % raycast->tex_height;
		raycast->tex_pos += raycast->step;
		color = *(unsigned int *)(cub3d->texture[raycast->tex_num].addr + \
				(cub3d->texture[raycast->tex_num].line * raycast->tex_y + \
				raycast->tex_x * (cub3d->texture[raycast->tex_num].bpp / 8)));
		dst = cub3d->mlx.addr + \
			(y * cub3d->mlx.line + x * (cub3d->mlx.bpp / 8));
		*(unsigned int *)dst = color;
		y++;
	}
}

static void	check_door(t_cub3d *cub3d)
{
	if (cub3d->door_flag == 1)
		return ;
	if (cub3d->move_door == 1 && cub3d->close == 0)
		open_door(cub3d);
	else if (cub3d->time + 50 < get_time() && \
		cub3d->info.map[(int)cub3d->render.pos_x][(int)cub3d->render.pos_y] \
		!= M_DOOR && cub3d->move_door == 0)
	{
		cub3d->move_door = 1;
		cub3d->close = 1;
	}
	else if (cub3d->close == 1)
		close_door(cub3d);
}

int	rendering(t_cub3d *cub3d)
{
	int			x;
	t_raycast	raycast;

	draw_background(cub3d);
	draw_moon(cub3d);
	x = 0;
	check_door(cub3d);
	while (x < SCN_WIDTH)
	{
		raycast_init(&raycast, cub3d, x);
		raycast_cal_side_dist(&raycast, cub3d);
		raycast_find_wall(&raycast, cub3d);
		raycast_cal_and_sel_wall(&raycast, cub3d);
		draw_raycast(&raycast, cub3d, x);
		if (raycast.door)
			if (cal_door(&raycast, cub3d, x))
				raycast.dbuffer[x] = raycast.prep_door_dist;
		raycast.zbuffer[x] = raycast.prep_wall_dist;
		x++;
	}
	sprite(&raycast, cub3d);
	minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win, \
							cub3d->mlx.img, 0, 0);
	return (0);
}
