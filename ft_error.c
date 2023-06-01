/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:53:54 by magonzal          #+#    #+#             */
/*   Updated: 2023/06/01 15:55:46 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *str)
{
	printf("%s\n", str);
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
