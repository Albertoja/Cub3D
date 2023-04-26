#include "cub3d.h"

void	ft_print_wall2(t_ray ray, int x, t_wall wall)
{
	while (wall.y < ray.height)
	{
		if (wall.y < wall.startdraw)
			ft_pixel_put(&ray.img, x, wall.y, ft_trgb(0,
					ray.mapest->c_color[0], ray.mapest->c_color[1],
					ray.mapest->c_color[2]));
		else if (wall.y >= wall.startdraw && wall.y <= wall.enddraw)
		{
			wall.ywall = (int)wall.exacthit & (ray.tex.height - 1);
			wall.exacthit += wall.stepy;
			choose_tex(ray, wall, x);
		}
		else
			ft_pixel_put(&ray.img, x, wall.y, ft_trgb(0,
					ray.mapest->f_color[0], ray.mapest->f_color[1],
					ray.mapest->f_color[2]));
		wall.y++;
	}
}

t_ray	ft_print_wall(t_ray ray, int x)
{
	t_wall	wall;

	wall.y = 0;
	wall.wallheight = (int)(ray.height / ray.distperpwall); // calculo la altura de la pared dividiendo la altura del rayo con su distancia
	wall.startdraw = -wall.wallheight / 2 + ray.height / 2; // calculo el punto de partida desde donde se empieza a dibujar la textura
	if (wall.startdraw < 0) //deformacion de las esquinas al acercarse por ojo de pez
		wall.startdraw = 0;
	wall.enddraw = wall.wallheight / 2 + ray.height / 2; // calculo donde se termina de dibujar la textura
	if (wall.enddraw >= ray.height) //deformacion de las esquinas al acercarse por ojo de pez
		wall.enddraw = ray.height - 1;
	if (ray.side == EAST || ray.side == WEST) //detecto la direccion del bloque
		wall.exacthit = ray.player_y + ray.distperpwall * ray.ray_y;
	else
		wall.exacthit = ray.player_x + ray.distperpwall * ray.ray_x;
	wall.exacthit -= floor((wall.exacthit)); //le doy exactitud al hit con double
	wall.xwall = (int)(wall.exacthit * (double)ray.tex.width); //calculo de forma exacta la longitud de anchura de la textura
	if (ray.side == EAST && ray.ray_x > 0) //distorsion de la textura
		wall.xwall = ray.tex.width - wall.xwall - 1;
	if (ray.side == SOUTH && ray.ray_y < 0)
		wall.xwall = ray.tex.width - wall.xwall - 1;
	wall.stepy = (double)ray.tex.height / (double)wall.wallheight; // calculo de forma exacta la longitud de altura de la textura
	wall.exacthit = (wall.startdraw - ray.height / 2 + wall.wallheight / 2) * wall.stepy; //ojo de pez
	ft_print_wall2(ray, x, wall);
	return (ray);
}

static t_ray	ft_rayhit(t_ray ray, char **map)
{
	while (ray.hit == 0) // si hit = 0 el rayo a golpeado la pared
	{
		if (ray.sidedist_x < ray.sidedist_y) //saltamos al siguiente cuadro ya sea por y o por x
		{
			ray.sidedist_x += ray.delta_x;
			ray.map_x += ray.step_x;
			if (ray.ray_x > 0) //calculo la direccion de la textura
				ray.side = EAST;
			else
				ray.side = WEST;
		}
		else
		{
			ray.sidedist_y += ray.delta_y;
			ray.map_y += ray.step_y;
			if (ray.ray_y > 0) //calculo la direccion de la textura
				ray.side = SOUTH;
			else
				ray.side = NORTH;
		}
		if (map[ray.map_y][ray.map_x] == '1') // compruebo si el rayo a chocado con una pared
			ray.hit = 1;
	}
	if (ray.side == EAST || ray.side == WEST)
		ray.distperpwall = ray.sidedist_x - ray.delta_x; //calculo la distancia a la pared
	else
		ray.distperpwall = ray.sidedist_y - ray.delta_y;
	return (ray);
}

static t_ray	ft_set_ray(t_ray ray, int xsweep)
{
	ray.camera = 2 * xsweep / (double)ray.width - 1; //camara
	ray.ray_x = ray.dir_x + ray.plane_x * ray.camera; //rayos en x
	ray.ray_y = ray.dir_y + ray.plane_y * ray.camera; //rayos en y
	ray.map_x = (int)ray.player_x;
	ray.map_y = (int)ray.player_y;
	ray.hit = 0;
	if (ray.ray_x == 0)
		ray.delta_x = 1e30; //poner lo mas grande, lo pone en la guia por si acaso
	else
		ray.delta_x = fabs(1 / ray.ray_x); //fabs devuelve el absoluto de un numero, 1 porque solo la proporcion entre los delta importa
	if (ray.ray_y == 0)
		ray.delta_y = 1e30;
	else
		ray.delta_y = fabs(1 / ray.ray_y); //// distancia entre entre un y y el otro y
	if (ray.ray_x < 0)
	{
		ray.step_x = -1; //si es negativo 
		ray.sidedist_x = (ray.player_x - ray.map_x) * ray.delta_x; // es la distancia hasta el primer lado a la izquierda
	}
	else
	{
		ray.step_x = 1; //si es positivo
		ray.sidedist_x = (ray.map_x + 1.0 - ray.player_x) * ray.delta_x; // es la distancia hasta el primer lado a la derecha
	}
	return (ray);
}

t_ray	ft_ray(t_ray ray, char **map, int xsweep)
{
	ray = ft_set_ray(ray, xsweep);	//step es la direccion,
	if (ray.ray_y < 0)
	{
		ray.step_y = -1;	//si es negativo, es la distancia por encima, si no por debajo de la posicion
		ray.sidedist_y = (ray.player_y - ray.map_y) * ray.delta_y; //sidedist es la distancia que tiene que viajar el rayo desde su posición inicial hasta el primer lado x y el primer lado y.
	}
	else
	{
		ray.step_y = 1;
		ray.sidedist_y = (ray.map_y + 1.0 - ray.player_y) * ray.delta_y; //delta es la distancia que el rayo tiene que viajar de un lado x a otro x, de un lado al otro del cubo
	}
	ray = ft_rayhit(ray, map); //calculo el choqque del rayo
	return (ray);
}

void	ft_move(t_ray *ray)
{
	ray->player_x += ray->dir_x * ray->speed;
	ray->player_y += ray->dir_y * ray->speed;
}

int	ft_raycasting(t_ray *ray)
{
	int xsweep; //contador de cada rayo

	ray->plane_x = -ray->dir_y;
	ray->plane_y = ray->dir_x * 0.66;
	ft_move(ray); //movimiento alante atras
	ft_rotate(&ray->dir_x, &ray->dir_y, ray->spinspeed); //giro, le paso directamente la velocidad de giro si es negativa o no
	mlx_clear_window(ray->mlx, ray->mlx_win);	//elimina la anterior imagen de la ventana
	xsweep = 0;
	while (xsweep < ray->width) // rayo comparado con la anchura de la pantalla
	{
		*ray = ft_ray(*ray, ray->mapest->map, xsweep); // calculo de rayos
		*ray = ft_print_wall(*ray, xsweep); //pintamos la textura de la pared
		ray->distance[xsweep] = ray->distperpwall; //guardo la distancia a la pared
		xsweep++;
	}
	mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->img.img, 0, 0); //vamos refrescando la imagen
	return(0);
}

t_ray	*ft_start_player(t_ray *ray)
{
	int	i;
	int	j;

	i = 0;
	while (ray->mapest->map[i])
	{
		j = 0;
		while (ray->mapest->map[i][j])
		{
			if(ft_strchr(PLAYER, ray->mapest->map[i][j]))
			{
				ray->player_x = j;
				ray->player_y = i;
				if (ray->mapest->map[i][j] == 'N')
				{
					ray->dir_x = 0;
					ray->dir_y = -1;
				}
				if (ray->mapest->map[i][j] == 'S')
				{
					ray->dir_x = 0;
					ray->dir_y = 1;
				}
				if (ray->mapest->map[i][j] == 'E')
				{
					ray->dir_x = 1;
					ray->dir_y = 0;
				}
				if (ray->mapest->map[i][j] == 'W')
				{
					ray->dir_x = -1;
					ray->dir_y = 0;
				}
				return(ray);
			}
			j++;
		}
		i++;
	}
	return(ray);
}

t_ray *ft_init_ray(t_all *all)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	ray->mapest = all->mapest;	//igualo al mapa de la struct, solo cambiare ese
	ray->height = HEIGHT;	//uso la longitud que tengo en el .h
	ray->width = WIDTH;
	ray = ft_start_player(ray);	//calculo donde esta el jugador y donde esta mirando
	ray->plane_y = ray->dir_x * 0.66; //plano inverso, ya que el plano es en 2d y 0.66 para el fov
	ray->plane_x = -ray->dir_y;
	ray->mlx = mlx_init();
	ray->distance = malloc(sizeof(double) * WIDTH); // igual al ancho por el ray
	ray->mlx_win = mlx_new_window(ray->mlx, ray->width, ray->height, "alan");	// inicio la ventana
	ray->img.img = mlx_new_image(ray->mlx, ray->width, ray->height);	//cargamos la imagen
	ray->img.addr = mlx_get_data_addr(ray->img.img, &ray->img.bits_per_pixel, &ray->img.line_length, &ray->img.endian); //da informacion de la imagen de la textura, endian calcula el tamaño donde meter cada color
	return(ray);
}

void	ft_cube(t_all *all)
{
	t_ray	*ray;

	ray = ft_init_ray(all); //inicializo los dtos de la struct del ray
	ray = ft_load_tex(ray); //cargo las imagenes y los datos de las texturas
	mlx_hook(ray->mlx_win, ON_KEYDOWN, 1L << 0, ft_key_push, ray);
	mlx_hook(ray->mlx_win, ON_KEYUP, 1L << 1, ft_key_release, ray);
	mlx_loop_hook(ray->mlx, ft_raycasting, ray); //el loop con raycasting
	mlx_loop(ray->mlx);
}
