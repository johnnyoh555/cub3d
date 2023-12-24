/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:08:56 by jooh              #+#    #+#             */
/*   Updated: 2023/12/24 18:57:23 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
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
}	t_info;

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

#endif