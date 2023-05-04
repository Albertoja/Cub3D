#include "cub3d.h"

int	ft_key_push(int key_code, t_ray *ray)
{
	if (key_code == 0)
		ray->spinspeed = -0.2;
	if (key_code == 2)
		ray->spinspeed = 0.2;
	if (key_code == 13)
		ray->speed = 0.5;
	if (key_code == 1)
		ray->speed = -0.5;
	return (0);
}

int	ft_key_release(int key_code, t_ray *ray)
{
	if (key_code == 0)
		ray->spinspeed = 0;
	if (key_code == 2)
		ray->spinspeed = 0;
	if (key_code == 13)
		ray->speed = 0;
	if (key_code == 1)
		ray->speed = 0;
	return (0);
}

void	ft_rotate(double *x, double *y, double rotSpeed)
{
	double	oldir;

	oldir = *x;
	*x = (*x) * cos(rotSpeed) - (*y) * sin(rotSpeed);
	*y = oldir * sin(rotSpeed) + *y * cos(rotSpeed);
}
