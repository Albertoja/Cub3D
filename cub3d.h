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
# define WIDTH 1920
# define HEIGHT 1080
# define SYMBOLS " 01NSWE"
# define FLOOR "0NSWE"
# define PLAYER "NSEW"
# define COLLISION "1"
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

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_tex {
	t_data	no;
	t_data	so;
	t_data	we;
	t_data	ea;
	int		width;
	int		height;
}	t_tex;

typedef struct s_ray{
	t_map	*mapest;
	t_data		img;
	t_tex		tex;
	void	*mlx;
	void	*mlx_win;
	int		width;
	int		height;
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	*distance;
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	delta_x;
	double	delta_y;
	int		hit;
	double	camera;
	int		side;
	double	distperpwall;
	double	spinspeed;
	double	speed;


}	t_ray;

typedef struct s_wall {
	int		wallheight;
	int		startdraw;
	int		enddraw;
	double	exacthit;
	double	stepy;
	int		y;
	int		xwall;
	int		ywall;
}			t_wall;

typedef struct s_all{
	t_map *mapest;
}			t_all;

enum {
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
};
size_t	ft_linelen(const char *line);
t_all	*ft_parse_map(char **argv);
char	*get_next_line(int fd);
int		ft_print_matrix(char **matrix);
char	*ft_strjoingnl(const char *s1, char const *s2);
int		ft_count_lines(int fd);
size_t	ft_linelen(const char *line);
char	**ft_free_matrix(char **result);
void	ft_check_map02(t_all all);
void	ft_error(char *str);
t_all	*ft_check_map01(char **read);
char	*ft_check_good(char *str);
int		ft_check_end_color(char **map, char *str);
char	**ft_clean_map(char **read);
void	ft_free_struct(t_all *all);
void	ft_cube(t_all *all);
t_ray	*ft_load_tex(t_ray *ray);
void	ft_pixel_put(t_data *data, int x, int y, int color);
void	choose_tex(t_ray ray, t_wall p, int x);
int		ft_trgb(int t, int r, int g, int b);
int		my_pixel_get(t_data *data, int x, int y);
int		ft_key_push(int key_code, t_ray *ray);
int		ft_key_release(int key_code, t_ray *ray);
void	ft_rotate(double *x, double *y, double angle);
#endif

