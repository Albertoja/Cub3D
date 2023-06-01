/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:04 by magonzal          #+#    #+#             */
/*   Updated: 2023/06/01 16:13:35 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc != 2)
		return (1);
	all = ft_parse_map(argv);
	ft_cube(all);
	ft_free_struct(all);
}
