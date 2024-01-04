/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:21:12 by sungyoon          #+#    #+#             */
/*   Updated: 2024/01/04 19:46:47 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	sprite_init(t_cub3d *cub3d, t_sprite *sprite)
{
	sprite->x = cub3d->info.sprite_x - cub3d->render.pos_x;
	sprite->y = cub3d->info.sprite_y - cub3d->render.pos_y;
	sprite->inv_det = 1.0 / (cub3d->render.plane_x * cub3d->render.dir_y \
					- cub3d->render.dir_x * cub3d->render.plane_y);
	sprite->transform_x = sprite->inv_det * (cub3d->render.dir_y * sprite->x \
					- cub3d->render.dir_x * sprite->y);
	sprite->transform_y = sprite->inv_det * (-cub3d->render.plane_y * \
					sprite->x + cub3d->render.plane_x * sprite->y);
	sprite->screen_x = (int)((SCN_WIDTH / 2) * (1 + sprite->transform_x \
					/ sprite->transform_y));
	sprite->height = abs((int)(SCN_HEIGHT / sprite->transform_y));
	sprite->width = abs((int)(SCN_HEIGHT / sprite->transform_y));
	sprite->draw_s_y = -sprite->height / 2 + SCN_HEIGHT / 2;
	if (sprite->draw_s_y < 0)
		sprite->draw_s_y = 0;
	sprite->draw_e_y = sprite->height / 2 + SCN_HEIGHT / 2;
	if (sprite->draw_e_y >= SCN_HEIGHT)
		sprite->draw_e_y = SCN_HEIGHT - 1;
	sprite->draw_s_x = -sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_s_x < 0)
		sprite->draw_s_x = 0;
	sprite->draw_e_x = sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_e_x >= SCN_WIDTH)
		sprite->draw_e_x = SCN_WIDTH - 1;
}

void	set_texture(t_cub3d *cub3d, t_sprite *sprite, int x, int y)
{
	int				d;
	char			*dst;
	unsigned int	color;

	d = y * 256 - SCN_HEIGHT * 128 + sprite->height * 128;
	sprite->tex_y = ((d * cub3d->texture[sprite->tex_num].height) \
					/ sprite->height) / 256;
	color = *(unsigned int *)(cub3d->texture[sprite->tex_num].addr + \
			(cub3d->texture[sprite->tex_num].line * sprite->tex_y + \
			sprite->tex_x * (cub3d->texture[sprite->tex_num].bpp / 8)));
	if (!(color & 0xFF000000))
	{
		dst = cub3d->mlx.addr + (y * cub3d->mlx.line + x \
			* (cub3d->mlx.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_sprite(t_raycast *raycast, t_cub3d *cub3d, t_sprite *sprite,
		int time)
{
	int				x;
	int				y;

	x = sprite->draw_s_x;
	while (x < sprite->draw_e_x)
	{
		sprite->tex_x = (int)(256 * (x - (-sprite->width / 2 \
			+ sprite->screen_x)) * cub3d->texture[sprite->tex_num].width / 4 \
			/ sprite->width) / 256 + time * 48;
		if (sprite->transform_y > 0 && x > 0 && x < SCN_WIDTH \
			&& sprite->transform_y < raycast->zbuffer[x]
			&& ((raycast->dbuffer[x] && sprite->transform_y \
			< raycast->dbuffer[x]) || raycast->dbuffer[x] == 0))
		{
			y = sprite->draw_s_y;
			while (y < sprite->draw_e_y)
			{
				set_texture(cub3d, sprite, x, y);
				y++;
			}
		}
		x++;
	}
}

void	find_sprite(t_info *info)
{
	int	y;
	int	x;

	x = 0;
	while (x < info->height)
	{
		y = 0;
		while (y < info->width)
		{
			if (info->map[x][y] == M_SPRITE)
			{
				info->sprite_x = x + 0.5;
				info->sprite_y = y + 0.5;
				return ;
			}
			y++;
		}
		x++;
	}
}

void	sprite(t_raycast *raycast, t_cub3d *cub3d)
{
	long		time;
	t_sprite	sprite;

	sprite_init(cub3d, &sprite);
	time = get_time() / 2 % 4;
	sprite.tex_num = 68;
	draw_sprite(raycast, cub3d, &sprite, time);
}
