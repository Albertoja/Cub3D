#include "cub3d.h"

void ft_error(char *str, t_all all)
{
	printf("%s\n", str);
	ft_free_matrix(all.mapest.map);
	exit(0);
}
