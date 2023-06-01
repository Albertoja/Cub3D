/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:33:18 by magonzal          #+#    #+#             */
/*   Updated: 2023/06/01 16:19:02 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *str)
{
	int	i;

	i = ft_strlen(str);
	write(2, "Error \n", 7);
	write(2, str, i);
	write(2, "\n", 1);
	exit(0);
}

void	ft_free_struct(t_all *all)
{
	free(all->mapest->no_tex_path);
	free(all->mapest->so_tex_path);
	free(all->mapest->we_tex_path);
	free(all->mapest->ea_tex_path);
	free(all->mapest->f_color);
	free(all->mapest->c_color);
	free(all);
}

void	rayaux(t_ray *ray)
{
	if (ray->ray_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (ray->player_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - ray->player_x) * ray->delta_x;
	}
	if (ray->ray_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (ray->player_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - ray->player_y) * ray->delta_y;
	}
}

int	mapname2(char *m)
{
	int	l;
	int	p;

	l = ft_strlen(m);
	p = l - 4;
	if (m[l - 1] == 'm' && m[l - 2] == 'p' && m[l - 3] == 'x' && m[p] == '.' )
		return (0);
	return (1);
}
