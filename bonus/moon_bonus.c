/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moon_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:26:09 by jooh              #+#    #+#             */
/*   Updated: 2024/01/04 19:46:47 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*choose_moon_img(int idx)
{
	if (idx < 21)
		return (moon_name1(idx));
	else if (idx < 34)
		return (moon_name2(idx));
	else if (idx < 47)
		return (moon_name3(idx));
	else if (idx < 60)
		return (moon_name4(idx));
	return (moon_name5(idx));
}

static void	put_moon(int idx, t_cub3d *cub3d)
{
	int				x;
	int				y;
	char			*dst;
	unsigned int	color;

	y = 0;
	while (y < 192)
	{
		x = 0;
		while (x < 192)
		{
			color = *(unsigned int *)(cub3d->texture[idx].addr + \
				(cub3d->texture[idx].line * (y / 4) + \
				(x / 4) * (cub3d->texture[idx].bpp / 8)));
			if (!(color & 0xFF000000))
			{
				dst = cub3d->mlx.addr + ((y + 180) * \
					cub3d->mlx.line + (x + 320) * (cub3d->mlx.bpp / 8));
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
