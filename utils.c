/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:33:26 by magonzal          #+#    #+#             */
/*   Updated: 2023/05/30 20:16:32 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_free_matrix(char **result)
{
	int	i;

	i = -1;
	if (!result)
		return (0);
	while (result[++i])
		free(result[i]);
	free(result);
	return (0);
}

t_ray	cube2aux(t_ray ray, t_wall	*wall, int x)
{
	while (wall->y < ray.height)
	{
		if (wall->y < wall->startdraw)
			ft_pixel_put(&ray.img, x, wall->y,
				ft_trgb(0, ray.mapest->c_color[0],
					ray.mapest->c_color[1], ray.mapest->c_color[2]));
		else if (wall->y >= wall->startdraw && wall->y <= wall->enddraw)
		{
			wall->ywall = (int)wall->exacthit & (ray.tex.height - 1);
			wall->exacthit += wall->stepy;
			choose_tex(ray, *wall, x);
		}
		else
			ft_pixel_put(&ray.img, x, wall->y,
				ft_trgb(0, ray.mapest->f_color[0],
					ray.mapest->f_color[1], ray.mapest->f_color[2]));
		wall->y++;
	}
	return (ray);
}

void	inicializeray(t_ray *ray, int x, int y)
{
	ray->dir_x = x;
	ray->dir_y = y;
}

int	startplayeraux(t_ray *ray, int i, int j)
{
	if (ft_strchr(PLAYER, ray->mapest->map[i][j]))
	{
		ray->player_x = j + 0.5;
		ray->player_y = i + 0.5;
		if (ray->mapest->map[i][j] == 'N')
			inicializeray(ray, 0, -1);
		else if (ray->mapest->map[i][j] == 'S')
			inicializeray(ray, 0, 1);
		else if (ray->mapest->map[i][j] == 'E')
			inicializeray(ray, 1, 0);
		else if (ray->mapest->map[i][j] == 'W')
			inicializeray(ray, -1, 0);
		return (0);
	}
	return (1);
}
