/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:53:08 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/26 13:17:37 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int rendering(t_cub3d *cub3d)
{
	int	x;

	{
		int i = 0;
		int j = 0;
		char *dst;
		while (i < SCN_HEIGHT)
		{
			j = 0;
			while (j < SCN_WIDTH)
			{
				dst = cub3d->mlx.addr + (i * cub3d->mlx.line + j * (cub3d->mlx.bpp / 8));
				if (i < SCN_HEIGHT / 2 + 100)
					*(unsigned int*)dst = cub3d->info.c_color;
				else
					*(unsigned int*)dst = cub3d->info.f_color;
				j++;
			}
			i++;
		}
	}
	
	x = 0;
	while (x < SCN_WIDTH)
	{
		double	cameraX = 2 * x / (double)SCN_WIDTH - 1;
		double	raydir_x = cub3d->render.dir_x + cub3d->render.plane_x * cameraX;
		double	raydir_y = cub3d->render.dir_y + cub3d->render.plane_y * cameraX;
		int	mapX = (int)cub3d->render.pos_x;
		int	mapY = (int)cub3d->render.pos_y;
		double	sideDistX;
		double	sideDistY;

		double deltaDistX = (raydir_x == 0) ? 1e30 : fabs(1 / raydir_x);
		double deltaDistY = (raydir_y == 0) ? 1e30 : fabs(1 / raydir_y);

		double perpWallDist;

		int	stepX;
		int	stepY;

		int	hit = 0;
		int	side;

		if (raydir_x < 0)
		{
			stepX = -1;
			sideDistX = (cub3d->render.pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub3d->render.pos_x) * deltaDistX;
		}
		if (raydir_y < 0)
		{
			stepY = -1;
			sideDistY = (cub3d->render.pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub3d->render.pos_y) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (cub3d->info.map[mapX][mapY] == M_WALL)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		int lineHeight = (int)(SCN_HEIGHT / perpWallDist);

		int pitch = 100;

		int drawStart = -lineHeight / 2 + SCN_HEIGHT / 2 + pitch;
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = lineHeight / 2 + SCN_HEIGHT / 2 + pitch;
		if (drawEnd >= SCN_HEIGHT)
			drawEnd = SCN_HEIGHT - 1;
		
		int texNum = 0;

		double wallX;
		if (side == 0)
			wallX = cub3d->render.pos_y + perpWallDist * raydir_y;
		else
			wallX = cub3d->render.pos_x + perpWallDist * raydir_x;
		wallX -= floor((wallX));
		
		int texX = (int)(wallX * 64);
		if (side == 0 && raydir_x > 0)
		{
			texNum = 0;
			texX = 64 - texX - 1;
		}
		else if (side == 0 && raydir_x <= 0)
			texNum = 1;
		if (side == 1 && raydir_y < 0)
		{
			texNum = 2;
			texX = 64 - texX - 1;
		}
		else if (side == 1 && raydir_y >= 0)
			texNum = 3;
		
		double step = 1.0 * TEXTURE_HEIGHT / lineHeight;
		double texPos = (drawStart - pitch - SCN_HEIGHT / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (TEXTURE_HEIGHT - 1);
			texPos += step;
			unsigned int color = *(unsigned int *)(cub3d->texture[texNum].addr + (cub3d->texture[texNum].line * texY + texX * (cub3d->texture[texNum].bpp / 8)));
			char *dst = cub3d->mlx.addr + (y * cub3d->mlx.line + x * (cub3d->mlx.bpp / 8));
			*(unsigned int*)dst = color;
		}

		x++;
	}
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win, cub3d->mlx.img, 0, 0);
	return (0);
}
