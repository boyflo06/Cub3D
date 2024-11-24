/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:16 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/24 17:23:52 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "mlx.h"
# include <fcntl.h>
# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <sys/time.h>

# define TILE_RESX 64
# define TILE_RESY 64
# define PI 3.1415926
# define DEG 0.0174533

// 1 << 0
# define KEY_UP 1
// 1 << 1
# define KEY_DOWN 2
// 1 << 2
# define KEY_LEFT 4
// 1 << 3
# define KEY_RIGHT 8
// 1 << 4
# define KEY_ARRLEFT 16
// 1 << 5
# define KEY_ARRRIGHT 32
// 1 << 6
# define KEY_TOGMOUSE 64

# define WIN_H 1000
# define WIN_W 1000

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
	char	*no_src;
	char	*so_src;
	char	*we_src;
	char	*ea_src;
	t_data	no;
	t_data	so;
	t_data	we;
	t_data	ea;
	int		f;
	int		c;
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

typedef struct s_ipoint
{
	int	x;
	int	y;
}	t_ipoint;

typedef struct s_ray
{
	double		dist;
	t_point		point;
	int			side;
	float		rot;
	float		lheight;
	float		slheight;
	float		screen_x;
}	t_ray;

typedef struct s_prog
{
	void	*mlx;
	void	*win;
	t_data	img;
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

void	default_prog(t_prog *prog);
void	default_img(t_prog *prog);
void	default_map(t_prog *prog);
int		initprog(t_prog *prog, char *path);

// Hooks

int		keypress(int key, t_prog *prog);
int		keyrelease(int key, t_prog *prog);
int		loop(t_prog	*prog);
int		destroy(t_prog *prog);

// Player Movement

void	updatemouse(t_prog *prog);
void	updateplayer(t_prog *prog);

//	RayCasting

void	raycast(t_prog *prog, t_data *img);

// Map Handling

int		getmap(t_prog *prog, char *path);
int		check_file_format(t_prog *prog, char *path);
int		add_spaces_map(t_prog *prog);
int		parsemap(t_prog *prog);

// Utils

double	radtodeg(double rad);
double	degtorad(double deg);
int		itoargb(unsigned char a, unsigned char r,
			unsigned char g, unsigned char b);
void	ft_pixelput(t_data *data, int x, int y, int color);
char	**ft_strarrpush(char **arr, char *newstr);

#endif