/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 08:38:28 by jooh              #+#    #+#             */
/*   Updated: 2023/12/25 17:58:52 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_arg(t_info *info, int ac, char **av)
{
	int	idx;

	if (ac == 1)
		err_seq("argc", "none argument", 1, 0);
	if (ac != 2)
		err_seq("argc", "to much arguments", 1, 0);
	idx = 0;
	while (av[1][idx])
		idx++;
	idx -= 4;
	if (ft_strncmp(&(av[1][idx]), ".cub", 4))
		err_seq("map", "mapname not valid", 1, 0);
	info->mapname = av[1];
}

static void	check_map_file(t_info *info)
{
	int		fd;
	char	*str;

	fd = open(info->mapname, O_RDONLY);
	if (fd == -1)
		err_seq("map", "failed to open map", 1, 0);
	while (1)
	{
		str = get_next_line(fd);
		if (str == 0)
			break ;
		if (info->cnt < 6)
			check_identifier(info, str);
		else
			check_map_size(info, str);
		free(str);
	}
	if (info->cnt < 6 || info->height == 0)
		err_seq("map", "not enough elements", 1, 0);
	if (info->start_point == 0)
		err_seq("map", "none starting position", 1, 0);
	if (info->start_point != 1)
		err_seq("map", "to much starting positions", 1, 0);
	close(fd);
}

void	init_info(t_info *info, int ac, char **av)
{
	ft_bzero(info, sizeof(t_info));
	check_arg(info, ac, av);
	check_map_file(info);
	make_map(info);
	check_valid_map(info);
}
