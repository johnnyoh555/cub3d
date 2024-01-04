/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:14:28 by jooh              #+#    #+#             */
/*   Updated: 2024/01/04 19:46:47 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	minimap_color(t_cub3d *cub3d, int x, int y)
{
	int	pos_x;
	int	pos_y;

	pos_y = (int)(cub3d->render.pos_x);
	pos_x = (int)(cub3d->render.pos_y);
	if (x == 7 && y == 7)
		return (0xff0000);
	if (x < 7)
		pos_x -= 7 - x;
	if (x > 7)
		pos_x += x - 7;
	if (y < 7)
		pos_y -= 7 - y;
	if (y > 7)
		pos_y += y - 7;
	if (pos_x < 0 || pos_y < 0 || pos_x >= cub3d->info.width
		|| pos_y >= cub3d->info.height || (cub3d->info.map[pos_y][pos_x] != 1
		&& cub3d->info.map[pos_y][pos_x] != 7))
		return (0xdcccac);
	if (cub3d->info.map[pos_y][pos_x] == 7 && cub3d->move_door == 1)
		return (0);
	if (cub3d->info.map[pos_y][pos_x] == 7 && !cub3d->move_door)
		return (0xffff33);
	return (0x5f4541);
}

static void	draw_minimap(t_mlx mlx, int x, int y, int map_color)
{
	int		idx_x;
	int		idx_y;
	char	*ptr;

	idx_y = 0;
	while (idx_y < 20)
	{
		idx_x = 0;
		while (idx_x < 20)
		{
			ptr = (mlx.addr) + ((idx_y + y) * mlx.line
					+ ((idx_x + SCN_WIDTH - 301 + x) * mlx.bpp / 8));
			*(int *)ptr = map_color;
			idx_x++;
		}
		idx_y++;
	}
}

void	minimap(t_cub3d *cub3d)
{
	int	x;
	int	y;
	int	map_color;

	y = 0;
	while (y < 15)
	{
		x = 0;
		while (x < 15)
		{
			map_color = minimap_color(cub3d, x, y);
			draw_minimap(cub3d->mlx, x * 20, y * 20, map_color);
			x++;
		}
		y++;
	}
}
