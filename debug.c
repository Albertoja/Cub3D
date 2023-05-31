/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:06:14 by magonzal          #+#    #+#             */
/*   Updated: 2023/05/30 19:23:23 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_matrix_p(char **mat)
{
	int i = -1;
	int j;

	while (mat[++i])
	{
		j = -1;
		while (mat[i][++j])
			printf("i: %d, j %d %p  |  ", i, j, &mat[i][j]);
		printf("\n");
		fflush(0);
	}
}

int	ft_print_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
	{
		printf("Null\n");
		fflush(0);
		return (1);
	}
	while (matrix[i])
	{
		ft_putstr_fd(matrix[i++], 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}

