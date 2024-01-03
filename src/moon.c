/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moon.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:26:09 by jooh              #+#    #+#             */
/*   Updated: 2024/01/03 20:06:50 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_moon(int idx, t_cub3d *cub3d)
{
	int				x;
	int				y;
	char			*dst;
	unsigned int	color;

	y = 0;
	while (y < 48)
	{
		x = 0;
		while (x < 48)
		{
			color = *(unsigned int *)(cub3d->texture[idx].addr + \
				(cub3d->texture[idx].line * y + \
				x * (cub3d->texture[idx].bpp / 8)));
			if (!(color & 0xFF000000))
			{
				dst = cub3d->mlx.addr + ((y + 200) * \
					cub3d->mlx.line + (x + 350) * (cub3d->mlx.bpp / 8));
				*(unsigned int *)dst = color;
			}
			x++;
		}
		y++;
	}
}

void	draw_moon(t_cub3d *cub3d)
{
	long	time;
	long	remain;

	time = get_time();
	remain = time % 60 + 8;
	put_moon(remain, cub3d);
}
