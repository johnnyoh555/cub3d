/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:08:56 by jooh              #+#    #+#             */
/*   Updated: 2023/12/25 16:56:28 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCN_WIDTH 1920
# define SCN_HEIGHT 1080

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define C_ANGLE 5

# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "mlx.h"

typedef enum e_mapinfo
{
	M_NO,
	M_WALL,
	M_PATH,
	M_SPAWN_N,
	M_SPAWN_S,
	M_SPAWN_E,
	M_SPAWN_W,
}	t_mapinfo;

typedef struct s_info
{
	int		line;
	int		cnt;
	char	*mapname;
	char	*no_file;
	char	*so_file;
	char	*ea_file;
	char	*we_file;
	int		f_color;
	int		f_flag;
	int		c_color;
	int		c_flag;
	int		width;
	int		height;
	int		start_point;
	int		**map;
	int		start_x;
	int		start_y;
	int		start_direction;
}	t_info;

typedef struct s_texture
{
	int		width;
	int		height;
	void	*img;
	char	*addr;
	int		bpp;
	int		line;
	int		endian;
}	t_texture;

typedef struct s_render
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_render;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line;
	int		endian;
}	t_mlx;

typedef struct s_cub3d
{
	t_mlx		mlx;
	t_render	render;
	t_texture	texture[4];
	t_info		info;
}	t_cub3d;

// all_directions.c
void	check_identifier(t_info *info, char *str);

// color_identifier.c
void	identifier_c(t_info *info, char *str);
void	identifier_f(t_info *info, char *str);

// info.c
void	init_info(t_info *info, int ac, char **av);

// make_map.c
void	make_map(t_info *info);

// map_size.c
void	check_map_size(t_info *info, char *str);

// utils.c
int		err_seq(char *str, char *err, int ex, int flag);
int		ft_strcmp(const char *s1, const char *s2);

// check_valid_map.c
void	check_valid_map(t_info *info);

int		cub3d_init(t_cub3d *cub3d);
int		cub3d_exit(t_cub3d *cub3d);

int		read_key(int keycode, t_cub3d *cub3d);

void	move_foward(t_cub3d *cub3d);
void	move_back(t_cub3d *cub3d);
void	move_left(t_cub3d *cub3d);
void	move_right(t_cub3d *cub3d);

void	camera_rotate(t_cub3d *cub3d, int dir);

int		rendering(t_cub3d *cub3d);

#endif