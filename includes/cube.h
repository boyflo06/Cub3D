/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:16 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/19 13:01:34 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define TILE_RESX 64
#define TILE_RESY 64
#define PI 3.1415926
#define DEG 0.0174533

#define KEY_UP 1 << 0
#define KEY_DOWN 1 << 1
#define KEY_LEFT 1 << 2
#define KEY_RIGHT 1 << 3
#define KEY_ARRLEFT 1 << 4
#define KEY_ARRRIGHT 1 << 5
#define KEY_TOGMOUSE 1 << 6

#define WIN_H 1000
#define WIN_W 1000

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		end;
	int		w;
	int		h;
}	t_data;

typedef struct s_map
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

typedef struct s_plyr
{
	double	x;
	double	y;
	double	rot;
}	t_plyr;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_ray
{
	double		dist;
	t_point		point;
	int			side;
	float		rot;
	float		lheight;
	float		screen_x;
}	t_ray;

typedef struct s_prog
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_plyr	player;
	char	keys;
	float	fps;
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
void	free_tab(char **tab);
void	free_prog(t_prog *prog);

// Initialisation functions

void	init_prog(t_prog *prog);
void	init_img(t_prog *prog);
void	init_map(t_prog *prog);

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

int		getmap(t_prog *prog, char *path);
int		check_file_format(t_prog *prog, char *path);

// Utils

double	radtodeg(double rad);
double	degtorad(double deg);
int		itoargb(unsigned char a, unsigned char r,
			unsigned char g, unsigned char b);
void	ft_pixelput(t_data *data, int x, int y, int color);
char	**ft_strarrpush(char **arr, char *newstr);
