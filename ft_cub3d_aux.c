/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:53:06 by magonzal          #+#    #+#             */
/*   Updated: 2023/05/22 18:05:17 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_count_lines(int fd)
{
	int		a;
	int		ret;
	char	*line;

	line = (char *)malloc(sizeof(char) * (1 + 1));
	ret = 0;
	a = 1;
	while (a == 1)
	{
		a = read(fd, line, 1);
		line[1] = 0;
		if (a == -1)
			return (0);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
			ret++;
	}
	if (line)
		free(line);
	return (ret + 1);
}

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bppx / 8));
	*(unsigned int *)dst = color;
}

int	ft_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	getpixel(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bppx / 8));
	return (*(unsigned int *)dst);
}

void	choose_tex(t_ray ray, t_wall p, int x)
{
	if (ray.side == NORTH)
		ft_pixel_put(&ray.img, x, p.y, getpixel(&ray.tex.no, p.xwall, p.ywall));
	else if (ray.side == EAST)
		ft_pixel_put(&ray.img, x, p.y, getpixel(&ray.tex.ea, p.xwall, p.ywall));
	else if (ray.side == SOUTH)
		ft_pixel_put(&ray.img, x, p.y, getpixel(&ray.tex.so, p.xwall, p.ywall));
	else if (ray.side == WEST)
		ft_pixel_put(&ray.img, x, p.y, getpixel(&ray.tex.we, p.xwall, p.ywall));
}
