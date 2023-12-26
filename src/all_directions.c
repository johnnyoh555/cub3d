/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_directions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:31:59 by jooh              #+#    #+#             */
/*   Updated: 2023/12/26 13:18:49 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	identifier_no(t_info *info, char *str)
{
	char	*trim;

	if (info->no_file != 0)
		err_seq("map", "NO identifier overlapped", 1, 0);
	while (*str == ' ')
		str++;
	if (*str == '\n' || *str == 0)
		err_seq("map", "no infomation for NO identifier", 1, 0);
	trim = ft_strdup(str);
	info->no_file = ft_strtrim(trim, "\n");
	free(trim);
	info->cnt++;
}

static void	identifier_so(t_info *info, char *str)
{
	char	*trim;

	if (info->so_file != 0)
		err_seq("map", "SO identifier overlapped", 1, 0);
	while (*str == ' ')
		str++;
	if (*str == '\n' || *str == 0)
		err_seq("map", "no infomation for SO identifier", 1, 0);
	trim = ft_strdup(str);
	info->so_file = ft_strtrim(trim, "\n");
	free(trim);
	info->cnt++;
}

static void	identifier_we(t_info *info, char *str)
{
	char	*trim;

	if (info->we_file != 0)
		err_seq("map", "WE identifier overlapped", 1, 0);
	while (*str == ' ')
		str++;
	if (*str == '\n' || *str == 0)
		err_seq("map", "no infomation for WE identifier", 1, 0);
	trim = ft_strdup(str);
	info->we_file = ft_strtrim(trim, "\n");
	free(trim);
	info->cnt++;
}

static void	identifier_ea(t_info *info, char *str)
{
	char	*trim;

	if (info->ea_file != 0)
		err_seq("map", "EA identifier overlapped", 1, 0);
	while (*str == ' ')
		str++;
	if (*str == '\n' || *str == 0)
		err_seq("map", "no infomation for EA identifier", 1, 0);
	trim = ft_strdup(str);
	info->ea_file = ft_strtrim(trim, "\n");
	free(trim);
	info->cnt++;
}

void	check_identifier(t_info *info, char *str)
{
	info->line++;
	while (*str == ' ')
		str++;
	if (!ft_strncmp(str, "NO ", 3))
		identifier_no(info, str + 3);
	else if (!ft_strncmp(str, "SO ", 3))
		identifier_so(info, str + 3);
	else if (!ft_strncmp(str, "EA ", 3))
		identifier_ea(info, str + 3);
	else if (!ft_strncmp(str, "WE ", 3))
		identifier_we(info, str + 3);
	else if (!ft_strncmp(str, "F ", 2))
		identifier_f(info, str + 2);
	else if (!ft_strncmp(str, "C ", 2))
		identifier_c(info, str + 2);
	else if (*str == '\n' || *str == 0)
		return ;
	else
		err_seq("map", "not a vaild identifier", 1, 0);
}
