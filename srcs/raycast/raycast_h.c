/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:18:09 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/22 15:23:27 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	setvars(t_prog *prog, double ra, t_ray *ray, t_point *off)
{
	float	atan;

	atan = -1 / tan(ra);
	ray->dist = 1000000;
	ray->point.x = prog->player.x;
	ray->point.y = prog->player.y;
	ray->side = 0;
	off->x = 0;
	off->y = 0;
	if (ra > PI)
	{
		ray->point.y = (((int) prog->player.y >> 6) << 6) - 0.0001;
		ray->point.x = (prog->player.y - ray->point.y) * atan + prog->player.x;
		off->y = -64;
		off->x = -off->y * atan;
	}
	else if (ra < PI)
	{
		ray->point.y = (((int) prog->player.y >> 6) << 6) + 64;
		ray->point.x = (prog->player.y - ray->point.y) * atan + prog->player.x;
		off->y = 64;
		off->x = -off->y * atan;
	}
}

t_ray	raycasth(t_prog *prog, double ra)
{
	t_ray	res;
	t_point	off;
	int		mx;
	int		my;

	setvars(prog, ra, &res, &off);
	if (ra == 0 || ra == PI)
		return (errorray());
	while (1)
	{
		mx = (int) res.point.x >> 6;
		my = (int) res.point.y >> 6;
		if ((mx < 0 || mx >= prog->map.width || my < 0
				|| my >= prog->map.height))
			break ;
		if (prog->map.data[my][mx] == '1')
		{
			res.dist = dist(prog->player.x, prog->player.y,
					res.point.x, res.point.y);
			return (res);
		}
		updateraypoint(&res, off);
	}
	return (errorray());
}
