/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:35:47 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/23 16:19:22 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	default_img(t_prog *prog)
{
	prog->map.no.img = NULL;
	prog->map.so.img = NULL;
	prog->map.we.img = NULL;
	prog->map.ea.img = NULL;
}

void	default_map(t_prog *prog)
{
	default_img(prog);
	prog->map.no.addr = NULL;
	prog->map.no.w = 0;
	prog->map.no.h = 0;
	prog->map.no.bpp = 0;
	prog->map.no.ll = 0;
	prog->map.no.end = 0;
	prog->map.so.addr = NULL;
	prog->map.so.w = 0;
	prog->map.so.h = 0;
	prog->map.so.bpp = 0;
	prog->map.so.ll = 0;
	prog->map.so.end = 0;
	prog->map.we.addr = NULL;
	prog->map.we.w = 0;
	prog->map.we.h = 0;
	prog->map.we.bpp = 0;
	prog->map.we.ll = 0;
	prog->map.we.end = 0;
	prog->map.ea.addr = NULL;
	prog->map.ea.w = 0;
	prog->map.ea.h = 0;
	prog->map.ea.bpp = 0;
	prog->map.ea.ll = 0;
	prog->map.ea.end = 0;
}

void	default_prog(t_prog *prog)
{
	prog->mlx = NULL;
	prog->win = NULL;
	prog->map.no_src = NULL;
	prog->map.so_src = NULL;
	prog->map.we_src = NULL;
	prog->map.ea_src = NULL;
	prog->map.f = 0;
	prog->map.c = 0;
	prog->map.data = NULL;
	prog->map.width = 0;
	prog->map.height = 0;
	prog->player.x = 0;
	prog->player.y = 0;
	prog->player.rot = 0;
	prog->keys = 0;
	prog->fps = 0;
	prog->img.img = NULL;
	default_map(prog);
}
