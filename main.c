#include <cub3d.h>

// void	leaks(void)
// {
// 	system("leaks cub3D");
// }

int	main(int argc, char **argv)
{
	t_all	all;

	//atexit(leaks);
	//all = NULL;
	if(argc != 2)
		return(1);
	ft_parse_map(argv, &all);
}
