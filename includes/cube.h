/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@stduent.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:16 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/31 13:36:48 by fghysbre         ###   ########.fr       */
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
	int	x;
	int	y;
}	t_point;

typedef struct s_ray
{
	int		dist;
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
}	t_prog;
