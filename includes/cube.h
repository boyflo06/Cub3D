/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:16 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/20 00:31:38 by fghysbre         ###   ########.fr       */
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
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F;
	int		C;
}	t_map;

typedef	struct s_plyr
{
	int		x;
	int		y;
	int		rot;
}	t_plyr;

typedef struct s_prog
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_plyr	player;
}	t_prog;
