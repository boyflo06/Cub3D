/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@stduent.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:30:18 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/15 15:30:50 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

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

float	dist(float ax, float ay, float bx, float by) {
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int	getpixelcolor(t_data *data, int	x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}
