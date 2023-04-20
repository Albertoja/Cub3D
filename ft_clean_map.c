#include "cub3d.h"

void	ft_clean_map(t_all all)
{
	int	inic;
	int	i;

	i = 0;
	inic = ft_check_end_color(all.mapest.map, "C") + 1;

	while(i != inic)
	{
		free(all.mapest.map[i]);
		all.mapest.map[i]++;
	}



	//all.mapest.map
}
