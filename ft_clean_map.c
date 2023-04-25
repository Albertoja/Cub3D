#include "cub3d.h"

int	ft_check_line_init(char **map)
{
	int	i;
	int	j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j] == ' ' || map[i][j] == 'C')
		{
			if(map[i][j] == 'C')
				if(map[i][j + 1] == ' ')
					return(i);
			j++;
		}
		i++;
	}
	return(0);
}

char	**ft_clean_map(char **read)
{
	int	inic;
	int	i;
	char **ret;

	i = 0;
	inic = ft_check_line_init(read);
	printf("inic = %i\n", inic);
	if (!inic)
		ft_error("bad arguments");
	printf("inic = %i\n", inic);
	while(read[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i - inic));
	i = 0;
	inic++;
	while(read[inic])
	{
		ret[i] = ft_strdup(read[inic]);
		i++;
		inic++;
	}
	ret[i] = NULL;
	return(ret);
}
