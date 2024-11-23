/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:18:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/23 22:00:04 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	putpixels_p2(t_ray *ray, t_data *img, t_ipoint pos, t_prog *prog)
{
	double	rx;

	rx = ray->point.x;
	if (ray->side == 0 && ray->rot > PI)
		ft_pixelput(img, pos.x, pos.y, getpixelcolor(&prog->map.no,
				(int)(((float)(fmod(rx, 64) * prog->map.no.w) / 64.f)),
				(int)((float)((float)(pos.y - ((WIN_H / 2)
								- ((int) ray->lheight / 2)) + ((ray->slheight
									- ray->lheight) / 2))
						/ (float) ray->slheight) *(prog->map.no.h))));
	else if (ray->side == 0 && ray->rot < PI)
		ft_pixelput(img, pos.x, pos.y, getpixelcolor(&prog->map.so,
				(int)(((float)((64 - fmod(rx, 64)) * prog->map.so.w) / 64.f)),
				(int)((float)((float)(pos.y - ((WIN_H / 2)
								- ((int) ray->lheight / 2)) + ((ray->slheight
									- ray->lheight) / 2))
						/ (float) ray->slheight) *(prog->map.so.h))));
}

static void	putpixels(t_ray *ray, t_data *img, t_ipoint pos, t_prog *prog)
{
	double	ry;

	ry = ray->point.y;
	if (ray->side == 1 && (ray->rot < PI / 2 || ray->rot > 3 * PI / 2))
		ft_pixelput(img, pos.x, pos.y, getpixelcolor(&prog->map.ea,
				(int)(((float)(fmod(ry, 64) * prog->map.ea.w) / 64.f)),
				(int)((float)((float)(pos.y - ((WIN_H / 2)
								- ((int) ray->lheight / 2)) + ((ray->slheight
									- ray->lheight) / 2))
						/ (float) ray->slheight) *(prog->map.ea.h))));
	else if (ray->side == 1 && ray->rot > PI / 2 && ray->rot < 3 * PI / 2)
		ft_pixelput(img, pos.x, pos.y, getpixelcolor(&prog->map.we,
				(int)(((float)(64 - (fmod(ry, 64)) * prog->map.we.w) / 64.f)),
				(int)((float)((float)(pos.y - ((WIN_H / 2)
								- ((int) ray->lheight / 2)) + ((ray->slheight
									- ray->lheight) / 2))
						/ (float) ray->slheight) *(prog->map.we.h))));
	else if (ray->side == 0)
		putpixels_p2(ray, img, pos, prog);
}

int	displayray(t_prog *prog, t_data *img, t_ray *ray)
{
	int		y;
	int		x;

	x = (ray->screen_x - (WIN_W / 960));
	ray->slheight = ray->lheight;
	if (ray->lheight > WIN_H)
		ray->lheight = WIN_H;
	while (x <= ray->screen_x + (WIN_W / 960))
	{
		y = (WIN_H / 2) - ((int) ray->lheight / 2);
		while (x >= 0 && x < WIN_W
			&& y <= (WIN_H / 2) + ((int) ray->lheight / 2))
		{
			putpixels(ray, img, (t_ipoint){x, y}, prog);
			y++;
		}
		x++;
	}
	return (1);
}

static double	fixfisheye(t_prog *prog, t_ray ray, double ra)
{
	float	ca;

	ca = degtorad(prog->player.rot) - ra;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	return (ray.dist * cos(ca));
}

void	raycast(t_prog *prog, t_data *img)
{
	int		r;
	double	ra;
	t_ray	rayv;
	t_ray	rayh;

	ra = degtorad(prog->player.rot) - (DEG * 30);
	r = -1;
	while (++r < 480)
	{
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
		rayh = raycasth(prog, ra);
		rayv = raycastv(prog, ra);
		if (rayh.dist < rayv.dist)
			rayv = rayh;
		rayv.dist = fixfisheye(prog, rayv, ra);
		rayv.lheight = (64 * WIN_H) / rayv.dist;
		rayv.screen_x = r * WIN_W / 480 + WIN_W / 960;
		rayv.rot = ra;
		displayray(prog, img, &rayv);
		ra += DEG / 8;
	}
}
