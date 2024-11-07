/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:16 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/07 17:46:47 by fghysbre         ###   ########.fr       */
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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		end;
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
