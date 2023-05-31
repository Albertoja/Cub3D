/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:01:42 by magonzal          #+#    #+#             */
/*   Updated: 2023/05/31 17:41:12 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	auxcub(t_ray *ray)
{
	if (ray->side == EAST || ray->side == WEST)
		ray->distperpwall = ray->sidedist_x - ray->delta_x;
	else
		ray->distperpwall = ray->sidedist_y - ray->delta_y;
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

void	collisions(t_ray *ray)
{
	if (ft_strchr("1", ray->mapest->map[(int)ray->player_y]
		[(int)(ray->player_x + ray->dir_x * ray->speed * 2)]) == NULL)
		ray->player_x += ray->dir_x * ray->speed;
	if (ft_strchr("1",ray->mapest->map[(int)(ray->player_y + ray->dir_y * ray->speed * 2)]
		[(int)ray->player_x]) == NULL)
			ray->player_y += ray->dir_y * ray->speed;
}

int	ft_raycasting(t_ray *ray)
{
	int	xsweep;

	ray->plane_x = -ray->dir_y;
	ray->plane_y = ray->dir_x * 0.66;
	collisions(ray);
	ft_rotate(&ray->dir_x, &ray->dir_y, ray->spinspeed);
	mlx_clear_window(ray->mlx, ray->mlx_win);
	xsweep = 0;
	while (xsweep < ray->width)
	{
		*ray = ft_ray(*ray, ray->mapest->map, xsweep);
		*ray = ft_print_wall(*ray, xsweep);
		ray->distance[xsweep] = ray->distperpwall;
		xsweep++;
	}
	mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->img.img, 0, 0);
	return (0);
}

t_ray	*ft_init_ray(t_all *all)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	ray->mapest = all->mapest;
	ray->height = HEIGHT;
	ray->width = WIDTH;
	ray = ft_start_player(ray);
	ray->plane_y = ray->dir_x * 0.66;
	ray->plane_x = -ray->dir_y;
	ray->mlx = mlx_init();
	ray->distance = malloc(sizeof(double) * WIDTH);
	ray->mlx_win = mlx_new_window(ray->mlx, ray->width, ray->height, "alan");
	ray->img.img = mlx_new_image(ray->mlx, ray->width, ray->height);
	ray->img.addr = mlx_get_data_addr(ray->img.img, &ray->img.bppx,
			&ray->img.line_length, &ray->img.endian);
	return (ray);
}

void	ft_cube(t_all *all)
{
	t_ray	*ray;

	ray = ft_init_ray(all);
	ray = ft_load_tex(ray);
	mlx_hook(ray->mlx_win, ON_DESTROY, 0L, endwindow, &ray);
	mlx_hook(ray->mlx_win, ON_KEYDOWN, 1L << 0, ft_key_push, ray);
	mlx_hook(ray->mlx_win, ON_KEYUP, 1L << 1, ft_key_release, ray);
	mlx_loop_hook(ray->mlx, ft_raycasting, ray);
	mlx_loop(ray->mlx);
}
