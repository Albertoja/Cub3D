#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_all	all;

	//all = NULL;
	if(argc != 2)
		return(1);
	ft_parse_map(argv, &all);
}
