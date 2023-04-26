#include "cub3d.h"

int	ft_count_lines(int fd)
{
	int		a;
	int		ret;
	char	*line;

	line = (char *)malloc(sizeof(char) * (1 + 1));
	ret = 0;
	a = 1;
	while (a == 1)
	{
		a = read(fd, line, 1);
		line[1] = 0;
		if (a == -1)
			return (0);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
			ret++;
	}
	if (line)
		free(line);
	return (ret + 1);
}

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_trgb(int t, int r, int g, int b) //trasformo los colores en trgb bits
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	my_pixel_get(t_data *data, int x, int y)
{
	return (*(unsigned int *)(data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8))));
}

void	choose_tex(t_ray ray, t_wall p, int x)
{
	if (ray.side == NORTH)
		ft_pixel_put(&ray.img, x, p.y,
			my_pixel_get(&ray.tex.no, p.xwall, p.ywall));
	else if (ray.side == EAST)
		ft_pixel_put(&ray.img, x, p.y,
			my_pixel_get(&ray.tex.ea, p.xwall, p.ywall));
	else if (ray.side == SOUTH)
		ft_pixel_put(&ray.img, x, p.y,
			my_pixel_get(&ray.tex.so, p.xwall, p.ywall));
	else if (ray.side == WEST)
		ft_pixel_put(&ray.img, x, p.y,
			my_pixel_get(&ray.tex.we, p.xwall, p.ywall));
}
