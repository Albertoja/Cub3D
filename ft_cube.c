#include "cub3d.h"

void	ft_print_wall2(t_ray ray, int x, t_wall p)
{
	while (p.y < ray.height)
	{
		if (p.y < p.startdraw)
			my_mlx_pixel_put(&ray.img, x, p.y, create_trgb(0,
					ray.mapest->c_color[0], ray.mapest->c_color[1],
					ray.mapest->c_color[2]));
		else if (p.y >= p.startdraw && p.y <= p.enddraw)
		{
			p.ywall = (int)p.exacthit & (ray.tex.height - 1);
			p.exacthit += p.stepy;
			choose_tex(ray, p, x);
		}
		else
			my_mlx_pixel_put(&ray.img, x, p.y, create_trgb(0,
					ray.mapest->f_color[0], ray.mapest->f_color[1],
					ray.mapest->f_color[2]));
		p.y++;
	}
}

t_ray	ft_print_wall(t_ray ray, int x)
{
	t_wall	p;

	p.wallheight = (int)(ray.height / ray.distperpwall);
	p.startdraw = -p.wallheight / 2 + ray.height / 2;
	if (p.startdraw < 0)
		p.startdraw = 0;
	p.enddraw = p.wallheight / 2 + ray.height / 2;
	if (p.enddraw >= ray.height)
		p.enddraw = ray.height - 1;
	p.y = 0;
	if (ray.side == EAST || ray.side == WEST)
		p.exacthit = ray.player_y + ray.distperpwall * ray.ray_y;
	else
		p.exacthit = ray.player_x + ray.distperpwall * ray.ray_x;
	p.exacthit -= floor((p.exacthit));
	p.xwall = (int)(p.exacthit * (double)ray.tex.width);
	if (ray.side == EAST && ray.ray_x > 0)
		p.xwall = ray.tex.width - p.xwall - 1;
	if (ray.side == SOUTH && ray.ray_y < 0)
		p.xwall = ray.tex.width - p.xwall - 1;
	p.stepy = (double)ray.tex.height / (double)p.wallheight;
	p.exacthit = (p.startdraw - ray.height / 2 + p.wallheight / 2) * p.stepy;
	ft_print_wall2(ray, x, p);
	return (ray);
}

static t_ray	ft_rayhit(t_ray ray, char **map)
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
		else if (map[ray.map_y][ray.map_x] == 'D')
			ray.hit = 2;
	}
	if (ray.side == EAST || ray.side == WEST)
		ray.distperpwall = ray.sidedist_x - ray.delta_x;
	else
		ray.distperpwall = ray.sidedist_y - ray.delta_y;
	return (ray);
}

static t_ray	ft_set_ray(t_ray ray, int a)
{
	ray.camera = 2 * a / (double)ray.width - 1;
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
	if (ray.ray_x < 0)
	{
		ray.step_x = -1;
		ray.sidedist_x = (ray.player_x - ray.map_x) * ray.delta_x;
	}
	else
	{
		ray.step_x = 1;
		ray.sidedist_x = (ray.map_x + 1.0 - ray.player_x) * ray.delta_x;
	}
	return (ray);
}

t_ray	ft_ray(t_ray ray, char **map, int a)
{
	ray = ft_set_ray(ray, a);
	if (ray.ray_y < 0)
	{
		ray.step_y = -1;
		ray.sidedist_y = (ray.player_y - ray.map_y) * ray.delta_y;
	}
	else
	{
		ray.step_y = 1;
		ray.sidedist_y = (ray.map_y + 1.0 - ray.player_y) * ray.delta_y;
	}
	ray = ft_rayhit(ray, map);
	return (ray);
}

int	ft_raycasting(t_ray *ray)
{
	int xsweep;

	ray->plane_x = -ray->dir_y;
	ray->plane_y = ray->dir_x * 0.66;
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
	return(0);
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
			if (ray->mapest->map[i][j] == 'N')
			{
				ray->player_x = j;
				ray->player_y = i;
				ray->dir_x = 0;
				ray->dir_y = -1;
			}
			if (ray->mapest->map[i][j] == 'S')
			{
				ray->player_x = j;
				ray->player_y = i;
				ray->dir_x = 0;
				ray->dir_y = 1;
			}
			if (ray->mapest->map[i][j] == 'E')
			{
				ray->player_x = j;
				ray->player_y = i;
				ray->dir_x = 1;
				ray->dir_y = 0;
			}
			if (ray->mapest->map[i][j] == 'W')
			{
				ray->player_x = j;
				ray->player_y = i;
				ray->dir_x = -1;
				ray->dir_y = 0;
			}
			j++;
		}
		i++;
	}
	return(ray);
}

t_ray *ft_init_ray(t_all *all)
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
	ray->mlx_win = mlx_new_window(ray->mlx, ray->width, ray->height, "error");
	ray->img.img = mlx_new_image(ray->mlx, ray->width, ray->height);
	ray->img.addr = mlx_get_data_addr(ray->img.img, &ray->img.bits_per_pixel, &ray->img.line_length, &ray->img.endian);
	return(ray);
}

void	ft_cube(t_all *all)
{
	t_ray	*ray;

	ray = ft_init_ray(all);
	ray = ft_load_tex(ray);
	mlx_loop_hook(ray->mlx, ft_raycasting, ray);
	mlx_loop(ray->mlx);
}
