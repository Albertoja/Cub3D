/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:52:15 by magonzal          #+#    #+#             */
/*   Updated: 2023/05/31 21:30:42 by aespinos         ###   ########.fr       */
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
