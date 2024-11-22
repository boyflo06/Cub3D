/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_v.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:18:12 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/22 15:23:03 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	setvars(t_prog *prog, double ra, t_ray *ray, t_point *off)
{
	float	ntan;

	ntan = -tan(ra);
	ray->dist = 1000000;
	ray->point.x = prog->player.x;
	ray->point.y = prog->player.y;
	ray->side = 1;
	off->x = 0;
	off->y = 0;
	if (ra > PI / 2 && ra < 3 * PI / 2)
	{
		ray->point.x = (((int) prog->player.x >> 6) << 6) - 0.0001;
		ray->point.y = (prog->player.x - ray->point.x) * ntan + prog->player.y;
		off->x = -64;
		off->y = -off->x * ntan;
	}
	else if (ra < PI / 2 || ra > 3 * PI / 2)
	{
		ray->point.x = (((int) prog->player.x >> 6) << 6) + 64;
		ray->point.y = (prog->player.x - ray->point.x) * ntan + prog->player.y;
		off->x = 64;
		off->y = -off->x * ntan;
	}
}

void	updateraypoint(t_ray *ray, t_point off)
{
	ray->point.x += off.x;
	ray->point.y += off.y;
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
