#include "cub3d.h"

void	ft_load_no(t_ray *ray)
{
	ray->tex.no.img = mlx_xpm_file_to_image(ray->mlx, ray->mapest->no_tex_path, &ray->tex.width, &ray->tex.height);
	ray->tex.no.addr = mlx_get_data_addr(ray->tex.no.img, &ray->tex.no.bits_per_pixel, &ray->tex.no.line_length, &ray->tex.no.endian);
}

void	ft_load_so(t_ray *ray)
{
	ray->tex.so.img = mlx_xpm_file_to_image(ray->mlx, ray->mapest->so_tex_path, &ray->tex.width, &ray->tex.height);
	ray->tex.so.addr = mlx_get_data_addr(ray->tex.so.img, &ray->tex.so.bits_per_pixel, &ray->tex.so.line_length, &ray->tex.so.endian);
}

void	ft_load_we(t_ray *ray)
{
	ray->tex.we.img = mlx_xpm_file_to_image(ray->mlx, ray->mapest->we_tex_path, &ray->tex.width, &ray->tex.height);
	ray->tex.we.addr = mlx_get_data_addr(ray->tex.we.img, &ray->tex.we.bits_per_pixel, &ray->tex.no.line_length, &ray->tex.we.endian);
}

void	ft_load_ea(t_ray *ray)
{
	ray->tex.ea.img = mlx_xpm_file_to_image(ray->mlx, ray->mapest->ea_tex_path, &ray->tex.width, &ray->tex.height);
	ray->tex.ea.addr = mlx_get_data_addr(ray->tex.ea.img, &ray->tex.ea.bits_per_pixel, &ray->tex.ea.line_length, &ray->tex.ea.endian);
}

t_ray	*ft_load_tex(t_ray *ray)
{
	ft_load_no(ray);
	ft_load_so(ray);
	ft_load_we(ray);
	ft_load_ea(ray);
	return (ray);
}
