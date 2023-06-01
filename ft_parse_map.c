/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:35:07 by magonzal          #+#    #+#             */
/*   Updated: 2023/06/01 15:55:58 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	mapname(char *m)
{
	int	l;
	int	p;

	l = ft_strlen(m);
	p = l - 4;
	if (m[l - 1] == 'b' && m[l - 2] == 'u' && m[l - 3] == 'c' && m[p] == '.' )
		return (0);
	return (1);
}

int	count_strs(char **arr)
{
	int	length;

	length = 0;
	if (!arr)
		return (length);
	while (arr[length])
		length++;
	return (length);
}

char	**append_str(char **origin, char *append)
{
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * (count_strs(origin) + 2));
	i = 0;
	if (origin)
	{
		while (origin && origin[i])
		{
			ret[i] = ft_strdup(origin[i]);
			i++;
		}
		ft_free_matrix(origin);
	}
	ret[i] = ft_strdup(append);
	ret[++i] = NULL;
	return (ret);
}

char	**ft_read_map(int fd)
{
	char	*line;
	char	**map;
	char	*append;

	line = get_next_line(fd);
	if (!line)
		exit(0);
	map = NULL;
	while (line)
	{
		append = ft_substr(line, 0, ft_strlen(line) - 1);
		map = append_str(map, append);
		free(line);
		free(append);
		line = get_next_line(fd);
	}
	return (map);
}

t_all	*ft_parse_map(char **argv)
{
	t_all	*all;
	int		fd;
	char	**read;
	int		i;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || mapname(argv[1]) == 1)
		ft_error("bad .cub file");
	read = ft_read_map(fd);
	all = ft_check_map01(read);
	i = ft_check_map_init(read);
	all->mapest->map = ft_clean_map(read, i);
	ft_free_matrix(read);
	ft_check_map02(*all);
	return (all);
}
