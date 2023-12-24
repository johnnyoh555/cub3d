/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:19:59 by jooh              #+#    #+#             */
/*   Updated: 2023/12/24 18:48:30 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	err_seq(char *str, char *err, int ex, int flag)
{
	if (err == 0)
	{
		ft_putstr_fd("cube3d: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": Error\n", 2);
	}
	else
	{
		ft_putstr_fd("cube3d: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd(": Error\n", 2);
	}
	if (flag)
		return (ex);
	exit(ex);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (1)
	{
		if (*str1 == 0 && *str2 == 0)
			return (0);
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}
