/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:21:03 by jooh              #+#    #+#             */
/*   Updated: 2024/01/04 22:02:45 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static char	*check_isnum(char **str, int flag)
{
	int		i;
	char	*tmp;

	tmp = *str;
	i = 0;
	while (i < 3 && tmp[i] != '\n' && tmp[i] != 0 && tmp[i] != ',')
	{
		if (!ft_isdigit(tmp[i]))
			return ("-1");
		i++;
	}
	if (i == 0)
		return ("-1");
	if (flag == 1)
		if (tmp[i] != 0 && tmp[i] != '\n')
			return ("-1");
	if (flag == 0 && tmp[i] != ',')
		return ("-1");
	if (flag == 0)
		*str += i + 1;
	return (tmp);
}

static int	change_color_to_int(char *str)
{
	int	r;
	int	g;
	int	b;
	int	color;

	r = ft_atoi(check_isnum(&str, 0));
	g = ft_atoi(check_isnum(&str, 0));
	b = ft_atoi(check_isnum(&str, 1));
	if (!(r >= 0 && r <= 255) || !(g >= 0 && g <= 255)
		|| !(b >= 0 && b <= 255))
		err_seq("map", "wrong color info", 1, 0);
	color = create_trgb(0, r, g, b);
	return (color);
}

void	identifier_f(t_info *info, char *str)
{
	if (info->f_flag != 0)
		err_seq("map", "F identifier overlapped", 1, 0);
	while (*str == ' ')
		str++;
	if (*str == 0)
		err_seq("map", "no infomation for F identifier", 1, 0);
	info->f_color = change_color_to_int(str);
	info->f_flag = 1;
	info->cnt++;
}

void	identifier_c(t_info *info, char *str)
{
	if (info->c_flag != 0)
		err_seq("map", "C identifier overlapped", 1, 0);
	while (*str == ' ')
		str++;
	if (*str == 0)
		err_seq("map", "no infomation for C identifier", 1, 0);
	info->c_color = change_color_to_int(str);
	info->c_flag = 1;
	info->cnt++;
}
