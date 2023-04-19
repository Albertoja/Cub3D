#include "cub3d.h"

char *ft_check_tex(char **map, char *str)
{
	int	i;
	int j;
	char **aux;

	aux = map;
	j = 0;
	i = -1;
	while (aux[++i])
	{
		j = 0;
		while(*aux[i] && *aux[i] == ' ')
			aux[i]++;
		if (ft_strncmp(aux[i], str, ft_strlen(str)) == 0)
		{
			aux = NULL;
			return(map[i]);
		}
	}
	return NULL;
}

void	ft_check_map01(t_all all)
{
	all.mapest.no_tex_path = ft_check_tex(all.mapest.map, "NO");
	printf("no = %s\n", all.mapest.no_tex_path);
	all.mapest.so_tex_path = ft_check_tex(all.mapest.map, "SO");
	printf("so = %s\n", all.mapest.so_tex_path);
	all.mapest.we_tex_path = ft_check_tex(all.mapest.map, "WE");
	printf("we = %s\n", all.mapest.we_tex_path);
	all.mapest.ea_tex_path = ft_check_tex(all.mapest.map, "EA");
	printf("ea = %s\n", all.mapest.ea_tex_path);
	exit(0);
}
