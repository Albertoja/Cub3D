/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:52:15 by magonzal          #+#    #+#             */
/*   Updated: 2023/06/01 20:59:38 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_clean_map(char **read, int inic)
{
	int		i;
	char	**ret;

	i = 0;
	if (!inic)
		ft_error("bad arguments");
	while (read[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i - inic));
	i = 0;
	inic++;
	while (read[inic])
	{
		ret[i] = ft_strdup(read[inic]);
		i++;
		inic++;
	}
	ret[i] = NULL;
	return (ret);
}
