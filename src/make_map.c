/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:09:16 by jooh              #+#    #+#             */
/*   Updated: 2023/12/24 19:11:02 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_one_line_info(t_info *info, char *str, int y)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == '0')
			info->map[y][x] = M_PATH;
		if (str[x] == '1')
			info->map[y][x] = M_WALL;
		if (str[x] == 'N')
			info->map[y][x] = M_SPAWN_N;
		if (str[x] == 'S')
			info->map[y][x] = M_SPAWN_S;
		if (str[x] == 'E')
			info->map[y][x] = M_SPAWN_E;
		if (str[x] == 'W')
			info->map[y][x] = M_SPAWN_W;
		x++;
	}
}

static void	get_map_info(t_info *info, int fd)
{
	int		y;
	char	*str;

	y = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (str == 0)
			break ;
		get_one_line_info(info, str, y);
		y++;
		free(str);
	}
}

static void	open_go_to_map(t_info *info)
{
	int		fd;
	int		idx;
	char	*str;

	fd = open(info->mapname, O_RDONLY);
	if (fd == -1)
		err_seq("map", "failed to open map", 1, 0);
	idx = 0;
	while (idx < info->line)
	{
		str = get_next_line(fd);
		if (str == 0)
			break ;
		free(str);
		idx++;
	}
	get_map_info(info, fd);
	close(fd);
}

void	make_map(t_info *info)
{
	int	idx;

	info->map = ft_calloc(sizeof(int *), info->height);
	idx = 0;
	while (idx < info->height)
	{
		info->map[idx] = ft_calloc(sizeof(int), info->width);
		idx++;
	}
	open_go_to_map(info);
}
