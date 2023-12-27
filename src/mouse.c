/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:00:23 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/27 11:21:21 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_mouse(int x, int y, t_cub3d *cub3d)
{
	(void)y;

	if (cub3d->render.m_pos_x - x < -1)
		camera_rotate(cub3d, 1);
	else if (cub3d->render.m_pos_x - x > 1)
		camera_rotate(cub3d, 0);
	cub3d->render.m_pos_x = x;
	return (0);
}
