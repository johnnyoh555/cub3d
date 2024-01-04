/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:08:56 by jooh              #+#    #+#             */
/*   Updated: 2024/01/04 16:06:10 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCN_WIDTH 1920
# define SCN_HEIGHT 1080

# define C_ANGLE 5

# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/time.h>

# include "mlx.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

typedef enum e_mapinfo
{
	M_NO,
	M_WALL,
	M_PATH,
	M_SPAWN_N,
	M_SPAWN_S,
	M_SPAWN_E,
	M_SPAWN_W,
	M_DOOR,
	M_SPRIT,
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
	double	sprite_x;
	double	sprite_y;
	int		start_direction;
}	t_info;

typedef struct s_raycast
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	prep_wall_dist;
	double	prep_door_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		side_d;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
	int		door;
	int		tex_width;
	int		tex_height;
	double	zbuffer[SCN_WIDTH];
}	t_raycast;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		height;
	int		width;
	int		draw_s_x;
	int		draw_e_x;
	int		draw_s_y;
	int		draw_e_y;
	int		tex_num;
	int		tex_x;
	int		tex_y;
}	t_sprite;

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
	int		pre_x;
	int		pre_y;
	int		pre_dir;
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
	t_texture	texture[68];
	t_info		info;
	long		time;
	int			door_flag;
	int			move_door;
	int			open_door;
	int			close;
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
long	get_time(void);

// check_valid_map.c
void	check_valid_map(t_info *info);

int		cub3d_init(t_cub3d *cub3d);
int		cub3d_exit(t_cub3d *cub3d);

int		read_key(int keycode, t_cub3d *cub3d);

void	move_foward(t_cub3d *cub3d);
void	move_back(t_cub3d *cub3d);
void	move_left(t_cub3d *cub3d);
void	move_right(t_cub3d *cub3d);

int		read_mouse(int x, int y, t_cub3d *cub3d);

void	camera_init(t_cub3d *cub3d);
void	camera_rotate(t_cub3d *cub3d, int dir);

void	raycast_init(t_raycast *raycast, t_cub3d *cub3d, int x);
void	raycast_cal_side_dist(t_raycast *raycast, t_cub3d *cub3d);
void	raycast_find_wall(t_raycast *raycast, t_cub3d *cub3d);
void	raycast_cal_and_sel_wall(t_raycast *raycast, t_cub3d *cub3d);

int		rendering(t_cub3d *cub3d);

void	find_sprite(t_info *info);
void	sprite(t_raycast *raycast, t_cub3d *cub3d);

// minimap.c
void	minimap(t_cub3d *cub3d);

void	check_if_door(t_raycast *raycast, t_cub3d *cub3d);
void	cal_door(t_raycast *raycast, t_cub3d *cub3d, int x);

void	close_door(t_cub3d *cub3d);
void	open_door(t_cub3d *cub3d);

void	cal_sprit(t_raycast *raycast, t_cub3d *cub3d, int x);

void	draw_moon(t_cub3d *cub3d);
char	*choose_moon_img(int idx);

char	*moon_name1(int idx);
char	*moon_name2(int idx);
char	*moon_name3(int idx);
char	*moon_name4(int idx);
char	*moon_name5(int idx);

#endif