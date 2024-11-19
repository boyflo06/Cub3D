/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:17:37 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/18 14:25:56 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// RayCasters

t_ray	raycasth(t_prog *prog, double ra);
t_ray	raycastv(t_prog *prog, double ra);

// Utils

t_ray	errorray();
float	dist(float ax, float ay, float bx, float by);
void	raycpy(t_ray *dst, t_ray *src);
int		getpixelcolor(t_data *data, int	x, int y);