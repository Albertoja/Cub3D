#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include <errno.h>
# include <sys/time.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# define SYMBOLS "0F1 NSWE"
# define FLOOR "0NSWE"
# define BUFFER_SIZE 3

typedef struct s_map {
	char	*no_tex_path;
	char	*so_tex_path;
	char	*we_tex_path;
	char	*ea_tex_path;
	int		*f_color;
	int		*c_color;
	char	**map;
	int		x;
	int		y;
}			t_map;

typedef struct s_all{
	t_map mapest;
}			t_all;
size_t	ft_linelen(const char *line);
void	ft_parse_map(char **argv, t_all *all);
char	*get_next_line(int fd);
int		ft_print_matrix(char **matrix);
char	*ft_strjoingnl(const char *s1, char const *s2);
int		ft_count_lines(int fd);
size_t	ft_linelen(const char *line);
char	**ft_free_matrix(char **result);
void	ft_check_map02(t_all all);
void	ft_error(char *str, t_all all);
void	ft_check_map01(t_all all);
#endif
