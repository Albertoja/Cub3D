/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:30:48 by magonzal          #+#    #+#             */
/*   Updated: 2023/06/01 15:01:43 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_double(char **map, char *str, int i)
{
	int	j;

	while (map[++i])
	{
		j = 0;
		while (map[i] && map[i][j] && map[i][j] == ' ')
			j++;
		if (ft_strncmp(&map[i][j], str, ft_strlen(str)) == 0)
		{
			ft_error("double info");
		}
	}
}

int	ft_get_color_n(char **map, char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i] && map[i][j] && map[i][j] == ' ')
			j++;
		if (ft_strncmp(&map[i][j], str, ft_strlen(str)) == 0)
		{
			ret = ft_check_good(map[i]);
			free(ret);
			ft_check_double(map, str, i);
			return (i);
		}
	}
	return (0);
}

int	ft_check_tex_num(char **map, char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = -1;
	if (!map)
		return (0);
	while (map[++i])
	{
		j = 0;
		while (map[i] && map[i][j] && map[i][j] == ' ')
			j++;
		if (ft_strncmp(&map[i][j], str, ft_strlen(str)) == 0)
		{
			ret = ft_check_good(map[i]);
			free(ret);
			ft_check_double(map, str, i);
			return (i);
		}
	}
	return (0);
}

int	ft_check_map_init(char **read)
{
	int	ret;

	ret = 0;
	if (ret < ft_check_tex_num(read, "NO "))
		ret = ft_check_tex_num(read, "NO ");
	if (ret < ft_check_tex_num(read, "SO "))
		ret = ft_check_tex_num(read, "SO ");
	if (ret < ft_check_tex_num(read, "WE "))
		ret = ft_check_tex_num(read, "WE ");
	if (ret < ft_check_tex_num(read, "EA "))
		ret = ft_check_tex_num(read, "EA ");
	if (ret < ft_get_color_n(read, "F"))
		ret = ft_get_color_n(read, "F");
	if (ret < ft_get_color_n(read, "C"))
		ret = ft_get_color_n(read, "C");
	return (ret);
}
