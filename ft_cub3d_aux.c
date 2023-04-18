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
