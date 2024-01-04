/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:23:48 by jooh              #+#    #+#             */
/*   Updated: 2024/01/04 19:33:03 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_width_height_info(t_info *info, char *str)
{
	int	width;

	width = 0;
	while (str[width] == ' ' || str[width] == '1' || str[width] == '0'
		|| str[width] == 'N' || str[width] == 'S' || str[width] == 'E'
		|| str[width] == 'W' || str[width] == 'D' || str[width] == 'C')
	{
		if (str[width] == 'N' || str[width] == 'S' || str[width] == 'E'
			|| str[width] == 'W')
			info->start_point++;
		width++;
	}	
	if (str[width] != '\n' && str[width] != 0)
		err_seq("map", "not a vaild element for map", 1, 0);
	width--;
	while (str[width] == ' ')
		width--;
	width++;
	if (width > info->width)
		info->width = width;
	info->height++;
}

void	check_map_size(t_info *info, char *str)
{
	static int	flag;
	int			idx;

	idx = 0;
	while (str[idx] == ' ')
		idx++;
	if (str[idx] == '\n' || str[idx] == 0)
	{
		if (flag == 0)
			info->line++;
		if (flag == 1)
			flag = 2;
		return ;
	}
	else
		if (flag == 0)
			flag = 1;
	if (flag == 2)
		err_seq("map", "not a vaild map", 1, 0);
	get_width_height_info(info, str);
}
