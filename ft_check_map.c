#include "cub3d.h"

void	ft_check_map_floor(t_all all, int i, int j)
{
	if (i == 0 || j == 0 || j == (int)(ft_strlen(all.mapest.map[i]) - 1) || !all.mapest.map[i + 1])
		ft_error("Error: map open", all);
	if (!all.mapest.map[i + 1][j] || !all.mapest.map[i - 1][j] || !all.mapest.map[i][j + 1] || !all.mapest.map[i][j - 1])
		ft_error("Error: map open", all);
	if (all.mapest.map[i + 1][j] == ' ' || all.mapest.map[i - 1][j] == ' ' 
		|| all.mapest.map[i][j + 1] == ' ' || all.mapest.map[i][j - 1] == ' ')
			ft_error("Error: map open", all);
}

void	ft_check_map(t_all all)
{
	int i;
	int	j;

	i = -1;
	while (all.mapest.map[++i])
	{
		j = -1;
		while (all.mapest.map[i][++j])
		{
			if (!ft_strchr(SYMBOLS, all.mapest.map[i][j]))
				ft_error("Error: bad symbols", all);
			else if(ft_strchr(FLOOR, all.mapest.map[i][j]))
				ft_check_map_floor(all, i, j);
		}
	}
}
