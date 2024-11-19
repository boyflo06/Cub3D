/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:52:34 by mleonet           #+#    #+#             */
/*   Updated: 2024/11/18 16:52:58 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_img(t_prog *prog)
{
	prog->map.NO.img = NULL;
	prog->map.SO.img = NULL;
	prog->map.WE.img = NULL;
	prog->map.EA.img = NULL;
}

void	init_map(t_prog *prog)
{
	init_img(prog);
	prog->map.NO.addr = NULL;
	prog->map.NO.w = 0;
	prog->map.NO.h = 0;
	prog->map.NO.bpp = 0;
	prog->map.NO.ll = 0;
	prog->map.NO.end = 0;
	prog->map.SO.addr = NULL;
	prog->map.SO.w = 0;
	prog->map.SO.h = 0;
	prog->map.SO.bpp = 0;
	prog->map.SO.ll = 0;
	prog->map.SO.end = 0;
	prog->map.WE.addr = NULL;
	prog->map.WE.w = 0;
	prog->map.WE.h = 0;
	prog->map.WE.bpp = 0;
	prog->map.WE.ll = 0;
	prog->map.WE.end = 0;
	prog->map.EA.addr = NULL;
	prog->map.EA.w = 0;
	prog->map.EA.h = 0;
	prog->map.EA.bpp = 0;
	prog->map.EA.ll = 0;
	prog->map.EA.end = 0;
}

void	init_prog(t_prog *prog)
{
	prog->mlx = NULL;
	prog->win = NULL;
	prog->map.NO_src = NULL;
	prog->map.SO_src = NULL;
	prog->map.WE_src = NULL;
	prog->map.EA_src = NULL;
	prog->map.F = 0;
	prog->map.C = 0;
	prog->map.data = NULL;
	prog->map.width = 0;
	prog->map.height = 0;
	prog->player.x = 0;
	prog->player.y = 0;
	prog->player.rot = 0;
	prog->keys = 0;
	prog->fps = 0;
	init_map(prog);
}
