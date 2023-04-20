#include "cub3d.h"

int	ft_check_end_color(char **map, char *str)
{
	int	i;
	int j;
	char **aux;
	char *ret;

	aux = map;
	i = -1;
	while (aux[++i])
	{
		j = 0;
		while(*aux[i] && *aux[i] == ' ')
			aux[i]++;
		if (ft_strncmp(aux[i], str, ft_strlen(str)) == 0)
		{
			ret = ft_check_good(aux[i], str, 0);
			aux = NULL;
			if(ret)
			{
				free(ret);
				return(i);
			}
		}
	}
	return (0);
}

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

void	ft_check_map02(t_all all)
{
	int i;
	int	j;

	i = ft_check_end_color(all.mapest.map, "C") + 1;
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
