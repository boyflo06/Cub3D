/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_v.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@stduent.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:18:12 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/13 16:19:49 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	setvars(t_prog *prog, double ra, t_ray *ray, t_point *off)
{
	float nTan;
	
	nTan = -tan(ra);
	ray->dist = 1000000;
	ray->point.x = prog->player.x;
	ray->point.y = prog->player.y;
	ray->side = 1;
	if (ra > PI / 2 && ra < 3 * PI / 2) {
		ray->point.x = (((int) prog->player.x >> 6) << 6) - 0.0001;
		ray->point.y = (prog->player.x - ray->point.x) * nTan + prog->player.y;
		off->x = -64;
		off->y = -off->x * nTan;
	} else if (ra < PI / 2 || ra > 3 * PI / 2) {
		ray->point.x = (((int) prog->player.x >> 6) << 6) + 64;
		ray->point.y = (prog->player.x - ray->point.x) * nTan + prog->player.y;
		off->x = 64;
		off->y = -off->x * nTan;
	} 
	else {
		off->x = 0;
		off->y = 0;
	}
}

t_ray	raycastv(t_prog *prog, double ra)
{
	t_ray	res;
	t_point	off;
	int		mx;
	int		my;

	setvars(prog, ra, &res, &off);
	if (ra == PI / 2 || ra == 3 * PI / 2)
		return (errorray());
	while (1) {
		mx = (int) res.point.x >> 6; my = (int) res.point.y >> 6;
		if ((mx < 0 || mx >= prog->map.width || my < 0 || my >= prog->map.height))
			break ;
		if (prog->map.data[my][mx] == '1') {
			res.dist = dist(prog->player.x, prog->player.y, res.point.x, res.point.y);
			return (res);
		}
		else {
			res.point.x += off.x; res.point.y += off.y;
		}
	}
	return (errorray());
}