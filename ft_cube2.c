/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:27:12 by magonzal          #+#    #+#             */
/*   Updated: 2023/06/01 14:43:53 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	ft_print_wall(t_ray ray, int x)
{
	t_wall	wall;
	int		aux;

	wall.y = 0;
	wall.wallheight = (int)(ray.height / ray.distperpwall);
	wall.startdraw = -wall.wallheight / 2 + ray.height / 2;
	if (wall.startdraw < 0)
		wall.startdraw = 0;
	wall.enddraw = wall.wallheight / 2 + ray.height / 2;
	if (wall.enddraw >= ray.height)
		wall.enddraw = ray.height - 1;
	if (ray.side == EAST || ray.side == WEST)
		wall.exacthit = ray.player_y + ray.distperpwall * ray.ray_y;
	else
		wall.exacthit = ray.player_x + ray.distperpwall * ray.ray_x;
	wall.exacthit -= floor((wall.exacthit));
	wall.xwall = (int)(wall.exacthit * (double)ray.tex.width);
	if (ray.side == EAST && ray.ray_x > 0)
		wall.xwall = ray.tex.width - wall.xwall - 1;
	if (ray.side == SOUTH && ray.ray_y < 0)
		wall.xwall = ray.tex.width - wall.xwall - 1;
	wall.stepy = (double)ray.tex.height / (double)wall.wallheight;
	aux = (wall.startdraw - ray.height / 2 + wall.wallheight / 2);
	wall.exacthit = aux * wall.stepy;
	return (cube2aux(ray, &wall, x));
}

t_ray	ft_ray(t_ray ray, char **map, int xsweep)
{
	ray.camera = 2 * xsweep / (double)ray.width - 1;
	ray.ray_x = ray.dir_x + ray.plane_x * ray.camera;
	ray.ray_y = ray.dir_y + ray.plane_y * ray.camera;
	ray.map_x = (int)ray.player_x;
	ray.map_y = (int)ray.player_y;
	ray.hit = 0;
	if (ray.ray_x == 0)
		ray.delta_x = 1e30;
	else
		ray.delta_x = fabs(1 / ray.ray_x);
	if (ray.ray_y == 0)
		ray.delta_y = 1e30;
	else
		ray.delta_y = fabs(1 / ray.ray_y);
	rayaux(&ray);
	ray = ft_rayhit(ray, map);
	return (ray);
}

t_ray	*ft_start_player(t_ray *ray)
{
	int	i;
	int	j;

	i = 0;
	while (ray->mapest->map[i])
	{
		j = 0;
		while (ray->mapest->map[i][j])
		{
			if (startplayeraux(ray, i, j) == 0)
				return (ray);
			j++;
		}
		i++;
	}
	return (ray);
}

void	ft_move(t_ray *ray)
{
	ray->player_x = ray->player_x + (ray->dir_x * ray->speed);
	ray->player_y = ray->player_y + (ray->dir_y * ray->speed);
}

t_ray	ft_rayhit(t_ray ray, char **map)
{
	while (ray.hit == 0)
	{
		if (ray.sidedist_x < ray.sidedist_y)
		{
			ray.sidedist_x += ray.delta_x;
			ray.map_x += ray.step_x;
			if (ray.ray_x > 0)
				ray.side = EAST;
			else
				ray.side = WEST;
		}
		else
		{
			ray.sidedist_y += ray.delta_y;
			ray.map_y += ray.step_y;
			if (ray.ray_y > 0)
				ray.side = SOUTH;
			else
				ray.side = NORTH;
		}
		if (map[ray.map_y][ray.map_x] == '1')
			ray.hit = 1;
	}
	auxcub(&ray);
	return (ray);
}
