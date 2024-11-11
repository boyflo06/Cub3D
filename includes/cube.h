/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:16 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/11 16:48:41 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>


#define	TILE_RESX 64
#define	TILE_RESY 64
#define PI 3.1415926
#define DEG 0.0174533

#define KEY_UP 1 << 0
#define KEY_DOWN 1 << 1
#define KEY_LEFT 1 << 2
#define KEY_RIGHT 1 << 3
#define KEY_ARRLEFT 1 << 4
#define KEY_ARRRIGHT 1 << 5
#define	KEY_TOGMOUSE 1 << 6

#define WIN_H 720
#define WIN_W 1280

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		end;
	int		w;
	int		h;
}	t_data;

typedef	struct s_map
{
	char	**data;
	char	*NO_src;
	char	*SO_src;
	char	*WE_src;
	char	*EA_src;
	t_data	NO;
	t_data	SO;
	t_data	WE;
	t_data	EA;
	int		F;
	int		C;
	int		width;
	int		height;
}	t_map;

typedef	struct s_plyr
{
	double	x;
	double	y;
	int		ix;
	int		iy;
	int		rot;
}	t_plyr;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_ray
{
	double		dist;
	t_point	point;
	int		side;
	float	rot;
	float	lheight;
	float	screen_x;
}	t_ray;

typedef struct s_prog
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_plyr	player;
	char	keys;
}	t_prog;

typedef struct s_mlx_ptr
{
	void	*appid;
	void	*win_list;
	void	*img_list;
	void	(*loop_hook)(void *);
	void	*loop_hook_data;
	void	*loop_timer;
	void	*font;
	int		main_loop_active;
}	t_mlx_ptr;

// Memmory managment

void	mlx_destroy(void *mlx_ptr);
void	freemap(t_map *map);

// Initialisation functions

int		initprog(t_prog *prog, char *path);

// Hooks

int		keypress(int key, t_prog *prog);
int		keyrelease(int key, t_prog *prog);
int		loop(t_prog	*prog);

// Player Movement

void	updatemouse(t_prog *prog);
void	updateplayer(t_prog *prog);

//	RayCasting

void	raycast(t_prog *prog, t_data *img);

// Map Handling

int		parsemap(t_prog *prog, char *path);

// Utils

double	radtodeg(double rad);
double	degtorad(double deg);
int		itoargb(unsigned char a, unsigned char r,
			unsigned char g, unsigned char b);
void	ft_pixelput(t_data *data, int x, int y, int color);