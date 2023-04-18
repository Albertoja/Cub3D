#include "cub3d.h"

char	**ft_free_matrix(char **result)
{
	int	i;

	i = -1;
	if (!result)
		return (0);
	while (result[++i])
		free(result[i]);
	free(result);
	return (0);
}
