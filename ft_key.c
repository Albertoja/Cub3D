/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:34:10 by magonzal          #+#    #+#             */
/*   Updated: 2023/06/01 16:02:32 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	endwindow(t_ray	*ray)
{
	(void )ray;
	exit(0);
}

int	ft_key_push(int key_code, t_ray *ray)
{
	if (key_code == 53)
		endwindow(ray);
	if (key_code == KEYLEFT || key_code == 123)
		ray->spinspeed = -0.2;
	if (key_code == KEYRIGHT || key_code == 124)
		ray->spinspeed = 0.2;
	if (key_code == KEYUP)
		ray->speed = 0.2;
	if (key_code == KEYDOWN)
		ray->speed = -0.2;
	return (0);
}

int	ft_key_release(int key_code, t_ray *ray)
{
	if (key_code == KEYLEFT || key_code == 123)
		ray->spinspeed = 0;
	if (key_code == KEYRIGHT || key_code == 124)
		ray->spinspeed = 0;
	if (key_code == KEYUP)
		ray->speed = 0;
	if (key_code == KEYDOWN)
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
