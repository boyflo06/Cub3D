/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@stduent.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:18:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/13 16:23:19 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

float	dist(float ax, float ay, float bx, float by) {
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int	getpixelcolor(t_data *data, int	x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

int	displayray(t_prog *prog, t_data *img, t_ray *ray)
{
	int		y;
	int		x;
	float	slheight;

	x = (ray->screen_x - (WIN_W / 480)) - 1;
	slheight = ray->lheight;
	if (ray->lheight > WIN_H)
		ray->lheight = WIN_H;
	//printf("%f: %f\n",ray->rot, ray->dist);
	while (x <= ray->screen_x + (WIN_W / 480))
	{
		y = (WIN_H / 2) - ((int) ray->lheight / 2);
		while (x >= 0 && x < WIN_W && y <= (WIN_H / 2) + ((int) ray->lheight / 2))
		{
			if (ray->side == 1 && ray->rot > PI / 2 && ray->rot < 3 * PI / 2)
				ft_pixelput(img, x, y, getpixelcolor(&prog->map.EA, (int) (((float) (fmod(ray->point.y, 64) * prog->map.EA.w) / 64.f)),  (int) ((float) ((float) (y - ((WIN_H / 2) - ((int) ray->lheight / 2)) + ((slheight - ray->lheight) / 2)) / (float) slheight) * prog->map.EA.h)));
			else if (ray->side == 1 && (ray->rot < PI / 2 || ray->rot > 3 * PI / 2))
				ft_pixelput(img, x, y, getpixelcolor(&prog->map.WE, (int) (((float) (fmod(ray->point.y, 64) * prog->map.WE.w) / 64.f)),  (int) ((float) ((float) (y - ((WIN_H / 2) - ((int) ray->lheight / 2)) + ((slheight - ray->lheight) / 2)) / (float) slheight) * prog->map.WE.h)));
			else if (ray->side == 0 && ray->rot < PI)
				ft_pixelput(img, x, y, getpixelcolor(&prog->map.NO, (int) (((float) (fmod(ray->point.x, 64) * prog->map.NO.w) / 64.f)),  (int) ((float) ((float) (y - ((WIN_H / 2) - ( ray->lheight / 2.0)) + ((slheight - ray->lheight) / 2.0)) / (float) slheight) * prog->map.NO.h)));
			else if (ray->side == 0 && ray->rot > PI)
				ft_pixelput(img, x, y, getpixelcolor(&prog->map.SO, (int) (((float) (fmod(ray->point.x, 64) * prog->map.SO.w) / 64.f)),  (int) ((float) ((float) (y - ((WIN_H / 2) - ((int) ray->lheight / 2)) + ((slheight - ray->lheight) / 2)) / (float) slheight) * prog->map.SO.h)));
			// else
			// 	ft_pixelput(img, x, y, itoargb(255, 0, 230, 0));
			y++;
		}
		x++;
	}
	return (1);
}

t_ray	errorray()
{
	t_ray	res;
	
	res.dist = 1000000;
	return (res);
}

void	raycpy(t_ray *dst, t_ray *src)
{
	dst->point.x = src->point.x;
	dst->point.y = src->point.y;
	dst->dist = src->dist;
	dst->side = src->dist;
}

void	raycast(t_prog *prog, t_data *img) {
	int		r;
	double	ra;
	t_ray	rayv;
	t_ray	rayh;
	
	ra = degtorad(prog->player.rot) - (DEG * 30);
	if (ra < 0) 
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	for (r = 0; r < 240; r++) {
		rayh = raycasth(prog, ra);
		rayv = raycastv(prog, ra);
		
		if (rayh.dist < rayv.dist) {rayv = rayh;}
		float	ca = degtorad(prog->player.rot) - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		rayv.dist = rayv.dist * cos(ca);
		rayv.lheight = (64 * WIN_H) / rayv.dist;
		rayv.screen_x = r * 5.333333333;
		rayv.rot = ra;
		displayray(prog, img, &rayv);

		ra += DEG / 4;
		if (ra < 0) 
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}