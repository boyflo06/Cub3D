/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@stduent.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:17:37 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/13 16:23:30 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// RayCasters

t_ray	raycasth(t_prog *prog, double ra);
t_ray	raycastv(t_prog *prog, double ra);

// Utils

t_ray	errorray();
float	dist(float ax, float ay, float bx, float by);