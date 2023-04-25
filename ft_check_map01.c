#include "cub3d.h"

int *ft_transform_rgb(char *ret)
{
	int	*rgb;
	char **matrix;
	int	i;
	int j;
	
	i = -1;
	matrix = ft_split(ret, ',');
	free(ret);
	if(!matrix)
		return(NULL);
	while (matrix[++i])
	{
		j = -1;
		if (ft_strlen(matrix[i]) > 3)
		{
			ft_free_matrix(matrix);
			return(NULL);
		}
		while (matrix[i][++j])
		{
			if (ft_isdigit(matrix[i][j]) == 0)
			{
				ft_free_matrix(matrix);
				return(NULL);
			}
		}
	}
	if(i != 3)
	{
		ft_free_matrix(matrix);
		return(NULL);
	}
	rgb = malloc(sizeof(int) * 3);
	rgb[0] = ft_atoi(matrix[0]);
	rgb[1] = ft_atoi(matrix[1]);
	rgb[2] = ft_atoi(matrix[2]);
	ft_free_matrix(matrix);
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
	{
		free(rgb);
		return(NULL);
	}
	return(rgb);

}

char *ft_check_good(char *str)
{
	char *ret;
	char	*aux;

	aux = str;
	while (*aux && *aux == ' ')
		aux++;
	while (*aux && *aux != ' ')
		aux++;
	while (*aux && *aux == ' ')
		aux++;
	ret = ft_strdup(aux);
	return(ret);
}

int	*ft_get_color(char **map, char *str)
{
	int	i;
	int j;
	char *ret;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while(map[i][j] && map[i][j] == ' ')
			i++;
		if (ft_strncmp(map[i], str, ft_strlen(str)) == 0)
		{
			ret = ft_check_good(map[i]);
			return(ft_transform_rgb(ret));
		}
	}
	return (NULL);
}


char	*ft_check_tex(char **map, char *str)
{
	int	i;
	int j;
	char *ret;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while(map[i][j] && map[i][j] == ' ')
			i++;
		if (ft_strncmp(map[i], str, ft_strlen(str)) == 0)
		{
			ret = ft_check_good(map[i]);
			return(ret);
		}
	}
	return (NULL);
}

t_all	*ft_check_map01(char **read)
{
	t_all	*all;

	all = ft_calloc(sizeof(t_all), 1);
	all->mapest = ft_calloc(sizeof(t_map), 1);
	all->mapest->no_tex_path = ft_check_tex(read, "NO ");
	printf("no = %s\n", all->mapest->no_tex_path);
	all->mapest->so_tex_path = ft_check_tex(read, "SO ");
	printf("so = %s\n", all->mapest->so_tex_path);
	all->mapest->we_tex_path = ft_check_tex(read, "WE ");
	printf("we = %s\n", all->mapest->we_tex_path);
	all->mapest->ea_tex_path = ft_check_tex(read, "EA ");
	printf("ea = %s\n", all->mapest->ea_tex_path);
	all->mapest->f_color = ft_get_color(read, "F");
	all->mapest->c_color = ft_get_color(read, "C");
	if(all->mapest->f_color == NULL || !(all->mapest->f_color) || all->mapest->c_color == NULL || !(all->mapest->c_color))
		ft_error("Error: Bad colors");
	if(all->mapest->no_tex_path == NULL || !(*all->mapest->no_tex_path) 
		|| all->mapest->no_tex_path == NULL || !(*all->mapest->no_tex_path)
			|| all->mapest->no_tex_path == NULL || !(*all->mapest->no_tex_path)
				|| all->mapest->no_tex_path == NULL || !(*all->mapest->no_tex_path))
					ft_error("Error: Bad colors");
	return(all);
}
