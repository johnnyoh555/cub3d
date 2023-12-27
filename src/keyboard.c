/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:35:01 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/27 11:13:45 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_key(int keycode, t_cub3d *cub3d)
{
	if (keycode == 13)
		move_foward(cub3d);
	else if (keycode == 0)
		move_left(cub3d);
	else if (keycode == 1)
		move_back(cub3d);
	else if (keycode == 2)
		move_right(cub3d);
	else if (keycode == 53)
		cub3d_exit(cub3d);
	return (0);
}
