/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:23:03 by jooh              #+#    #+#             */
/*   Updated: 2023/12/24 19:07:39 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_when_path(t_info *info, int x, int y)
{
	if (!(info->map[y][x - 1] >= M_WALL && info->map[y][x - 1] <= M_SPAWN_W))
		err_seq("map", "not a valid map", 1, 0);
	if (!(info->map[y - 1][x - 1] >= M_WALL
		&& info->map[y - 1][x - 1] <= M_SPAWN_W))
		err_seq("map", "not a valid map", 1, 0);
	if (!(info->map[y + 1][x - 1] >= M_WALL
		&& info->map[y + 1][x - 1] <= M_SPAWN_W))
		err_seq("map", "not a valid map", 1, 0);
	if (!(info->map[y][x + 1] >= M_WALL && info->map[y][x + 1] <= M_SPAWN_W))
		err_seq("map", "not a valid map", 1, 0);
	if (!(info->map[y - 1][x + 1] >= M_WALL
		&& info->map[y - 1][x + 1] <= M_SPAWN_W))
		err_seq("map", "not a valid map", 1, 0);
	if (!(info->map[y + 1][x + 1] >= M_WALL
		&& info->map[y + 1][x + 1] <= M_SPAWN_W))
		err_seq("map", "not a valid map", 1, 0);
	if (!(info->map[y - 1][x] >= M_WALL && info->map[y - 1][x] <= M_SPAWN_W))
		err_seq("map", "not a valid map", 1, 0);
	if (!(info->map[y + 1][x] >= M_WALL && info->map[y + 1][x] <= M_SPAWN_W))
		err_seq("map", "not a valid map", 1, 0);
}

static void	check_when_notmap(t_info *info, int x, int y)
{
	if (x != 0
		&& !(info->map[y][x - 1] == M_NO || info->map[y][x - 1] == M_WALL))
		err_seq("map", "not a valid map", 1, 0);
	if (x != 0 && y != 0 && \
		!(info->map[y - 1][x - 1] == M_NO || info->map[y - 1][x - 1] == M_WALL))
		err_seq("map", "not a valid map", 1, 0);
	if (x != 0 && y != info->height - 1 && \
		!(info->map[y + 1][x - 1] == M_NO || info->map[y + 1][x - 1] == M_WALL))
		err_seq("map", "not a valid map", 1, 0);
	if (x != info->width - 1 && \
		!(info->map[y][x + 1] == M_NO || info->map[y][x + 1] == M_WALL))
		err_seq("map", "not a valid map", 1, 0);
	if (x != info->width - 1 && y != 0 && \
		!(info->map[y - 1][x + 1] == M_NO || info->map[y - 1][x + 1] == M_WALL))
		err_seq("map", "not a valid map", 1, 0);
	if (x != info->width - 1 && y != info->height - 1 && \
		!(info->map[y + 1][x + 1] == M_NO || info->map[y + 1][x + 1] == M_WALL))
		err_seq("map", "not a valid map", 1, 0);
	if (y != 0
		&& !(info->map[y - 1][x] == M_NO || info->map[y - 1][x] == M_WALL))
		err_seq("map", "not a valid map", 1, 0);
	if (y != info->height - 1
		&& !(info->map[y + 1][x] == M_NO || info->map[y + 1][x] == M_WALL))
		err_seq("map", "not a valid map", 1, 0);
}

void	check_valid_map(t_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			if (info->map[y][x] == M_NO)
				check_when_notmap(info, x, y);
			if (info->map[y][x] >= M_PATH && info->map[y][x] <= M_SPAWN_W)
			{
				if (y == 0 || y == info->height - 1
					|| x == 0 || x == info->width - 1)
					err_seq("map", "not a valid map", 1, 0);
				check_when_path(info, x, y);
			}
			x++;
		}
		y++;
	}
}
