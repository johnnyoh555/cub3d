/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 15:19:25 by sungyoon          #+#    #+#             */
/*   Updated: 2024/01/03 11:55:18 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub3d_exit(t_cub3d *cub3d)
{
	int	idx;

	mlx_destroy_image(cub3d->mlx.mlx, cub3d->mlx.img);
	idx = 0;
	while (idx < 8)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->texture[idx++].img);
	mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win);
	exit(0);
}

static void	cub3d_render_init(t_cub3d *cub3d)
{
	cub3d->render.pos_x = cub3d->info.start_y + 0.5;
	cub3d->render.pos_y = cub3d->info.start_x + 0.5;
	camera_init(cub3d);
	cub3d->door_flag = 1;
	cub3d->time = 0;
	cub3d->open_door = 0;
	cub3d->move_door = 1;
}

static char	*cub3d_texture_idx_to_file(int idx, t_cub3d *cub3d)
{
	if (idx == 0)
		return (cub3d->info.no_file);
	else if (idx == 1)
		return (cub3d->info.so_file);
	else if (idx == 2)
		return (cub3d->info.ea_file);
	else if (idx == 3)
		return (cub3d->info.we_file);
	else if (idx == 4)
		return ("./door1.xpm");
	else if (idx == 5)
		return ("./door2.xpm");
	else if (idx == 6)
		return ("./door3.xpm");
	else
		return ("./door4.xpm");
}

static int	cub3d_texture_init(t_cub3d *cub3d)
{
	int		idx;
	char	*file;

	idx = 0;
	while (idx < 8)
	{
		file = cub3d_texture_idx_to_file(idx, cub3d);
		cub3d->texture[idx].img = mlx_xpm_file_to_image(cub3d->mlx.mlx, file, \
					&cub3d->texture[idx].width, &cub3d->texture[idx].height);
		if (cub3d->texture[idx].img == NULL)
			return (1);
		cub3d->texture[idx].addr = mlx_get_data_addr(cub3d->texture[idx].img, \
						&cub3d->texture[idx].bpp, &cub3d->texture[idx].line, \
						&cub3d->texture[idx].endian);
		idx++;
	}
	return (0);
}

int	cub3d_init(t_cub3d *cub3d)
{
	cub3d->mlx.mlx = mlx_init();
	cub3d->mlx.win = mlx_new_window(cub3d->mlx.mlx, SCN_WIDTH, SCN_HEIGHT, \
								"Ray Casting");
	cub3d->mlx.img = mlx_new_image(cub3d->mlx.mlx, SCN_WIDTH, SCN_HEIGHT);
	cub3d->mlx.addr = mlx_get_data_addr(cub3d->mlx.img, &cub3d->mlx.bpp, \
									&cub3d->mlx.line, &cub3d->mlx.endian);
	cub3d_render_init(cub3d);
	if (cub3d_texture_init(cub3d) == 1)
		return (1);
	mlx_hook(cub3d->mlx.win, 2, 0, read_key, cub3d);
	mlx_hook(cub3d->mlx.win, 6, 0, read_mouse, cub3d);
	mlx_hook(cub3d->mlx.win, 17, 0, cub3d_exit, cub3d);
	mlx_loop_hook(cub3d->mlx.mlx, rendering, cub3d);
	mlx_loop(cub3d->mlx.mlx);
	return (0);
}
