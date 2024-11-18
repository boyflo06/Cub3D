/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:17:37 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/18 17:03:08 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// RayCasters

t_ray	raycasth(t_prog *prog, double ra);
t_ray	raycastv(t_prog *prog, double ra);

// Utils

t_ray	errorray(void);
float	dist(float ax, float ay, float bx, float by);
int		getpixelcolor(t_data *data, int x, int y);
