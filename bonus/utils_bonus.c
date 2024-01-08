/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:19:59 by jooh              #+#    #+#             */
/*   Updated: 2024/01/08 14:34:36 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	err_seq(char *str, char *err, int ex, int flag)
{
	if (err == 0)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("cub3D: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("cub3D: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd("\n", 2);
	}
	if (flag)
		return (ex);
	exit(ex);
}

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, 0) == -1)
		err_seq("time", "failed to get current time", 1, 0);
	time = (tv.tv_sec * 10) + (tv.tv_usec / 100000);
	return (time);
}
