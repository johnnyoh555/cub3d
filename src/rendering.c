/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:53:08 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/29 14:01:56 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	raycast->tex_x = (int)(raycast->wall_x * TEXTURE_WIDTH);
	if ((raycast->side == 0 && raycast->raydir_x > 0) || \
		(raycast->side == 1 && raycast->raydir_y < 0))
		raycast->tex_x = TEXTURE_WIDTH - raycast->tex_x - 1;
	raycast->step = 1.0 * TEXTURE_HEIGHT / raycast->line_height;
	raycast->tex_pos = raycast->draw_start - SCN_HEIGHT / 2;
	raycast->tex_pos += raycast->line_height / 2;
	raycast->tex_pos *= raycast->step;
	y = raycast->draw_start;
	while (y < raycast->draw_end)
	{
		raycast->tex_y = (int)raycast->tex_pos & (TEXTURE_HEIGHT - 1);
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

int	rendering(t_cub3d *cub3d)
{
	int			x;
	t_raycast	raycast;

	draw_background(cub3d);
	x = 0;
	while (x < SCN_WIDTH)
	{
		raycast_init(&raycast, cub3d, x);
		raycast_cal_side_dist(&raycast, cub3d);
		raycast_find_wall(&raycast, cub3d);
		raycast_cal_and_sel_wall(&raycast, cub3d);
		draw_raycast(&raycast, cub3d, x);
		x++;
	}
	minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win, \
							cub3d->mlx.img, 0, 0);
	return (0);
}
