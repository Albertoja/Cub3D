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
			return(NULL);
		while (matrix[i][++j])
		{
			if (ft_isdigit(matrix[i][j]) == 0)
				return(NULL);
		}
	}
	if(i != 3)
		return(NULL);
	rgb = malloc(sizeof(int) * 3);
	rgb[0] = ft_atoi(matrix[0]);
	rgb[1] = ft_atoi(matrix[1]);
	rgb[2] = ft_atoi(matrix[2]);
	ft_free_matrix(matrix);
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return(NULL);
	return(rgb);

}

char *ft_check_good(char *str, char *comp, int a)
{
	int i;
	int j;
	char *ret;
	int		len;

	len = ft_strlen(comp);
	i = 0;
	j = 0;

	while(str[i] && str[i] != comp[a])
		i++;
	if(str[i + 1] == ' ')
	{
		i++;
		ret = malloc(sizeof(char) * (ft_strlen(str) - 1 - a));
		while(str[i++])
		{
			ret[j] = str[i];
			j++;
		}
		return (ret);
	}
	return (NULL);
}

int	*ft_get_color(char **map, char *str)
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
			return(ft_transform_rgb(ret));
		}
	}
	return (NULL);
}


char	*ft_check_tex(char **map, char *str)
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
			ret = ft_check_good(aux[i], str, 1);
			aux = NULL;
			return(ret);
		}
	}
	return (NULL);
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
	all.mapest.f_color = ft_get_color(all.mapest.map, "F");
	all.mapest.c_color = ft_get_color(all.mapest.map, "C");
	if(all.mapest.f_color == NULL || !(all.mapest.f_color) || all.mapest.c_color == NULL || !(all.mapest.c_color))
		ft_error("Error: Bad colors", all);
	if(all.mapest.no_tex_path == NULL || !(*all.mapest.no_tex_path) 
		|| all.mapest.no_tex_path == NULL || !(*all.mapest.no_tex_path)
			|| all.mapest.no_tex_path == NULL || !(*all.mapest.no_tex_path)
				|| all.mapest.no_tex_path == NULL || !(*all.mapest.no_tex_path))
					ft_error("Error: Bad colors", all);
}
