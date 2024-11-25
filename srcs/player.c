/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@stduent.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:25:03 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/25 15:58:07 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	updaterot(t_prog *prog)
{
	if ((prog->keys >> 5) % 2)
		prog->player.rot += 1.5 * (60.0 / prog->fps);
	if ((prog->keys >> 4) % 2)
		prog->player.rot -= 1.5 * (60.0 / prog->fps);
	if (prog->player.rot > 359)
		prog->player.rot -= 360;
	if (prog->player.rot < 0)
		prog->player.rot += 360;
}

static void	updatepos(t_prog *prog)
{
	float	dx;
	float	dy;

	dx = cos(degtorad(prog->player.rot)) * 2 * (60 / prog->fps);
	dy = sin(degtorad(prog->player.rot)) * 2 * (60 / prog->fps);
	if (prog->keys % 2)
	{
		prog->player.x += dx;
		prog->player.y += dy;
	}
	if ((prog->keys >> 1) % 2)
	{
		prog->player.x -= dx;
		prog->player.y -= dy;
	}
	if (prog->keys & KEY_RIGHT)
	{
		prog->player.x -= dy;
		prog->player.y += dx;
	}
	if (prog->keys & KEY_LEFT)
	{
		prog->player.x += dy;
		prog->player.y -= dx;
	}
}

void	colisioncheck(t_prog *prog, int x, int y)
{
	if (prog->map.data[(y - 10) / 64][x / 64] == '1')
		prog->player.y = (y / 64) * 64 + 10;
	if (prog->map.data[(y + 10) / 64][x / 64] == '1')
		prog->player.y = ((y / 64) + 1) * 64 - 10;
	if (prog->map.data[y / 64][(x - 10) / 64] == '1')
		prog->player.x = (x / 64) * 64 + 10;
	if (prog->map.data[y / 64][(x + 10) / 64] == '1')
		prog->player.x = ((x / 64) + 1) * 64 - 10;
	if (prog->map.data[(y - 10) / 64][(x - 5) / 64] == '1' ||
		prog->map.data[(y - 10) / 64][(x + 5) / 64] == '1')
		prog->player.y = (y / 64) * 64 + 10;
	if (prog->map.data[(y + 10) / 64][(x - 5) / 64] == '1' ||
		prog->map.data[(y + 10) / 64][(x + 5) / 64] == '1')
		prog->player.y = ((y / 64) + 1) * 64 - 10;
	if (prog->map.data[(y - 5) / 64][(x - 10) / 64] == '1' ||
		prog->map.data[(y + 5) / 64][(x - 10) / 64] == '1')
		prog->player.x = (x / 64) * 64 + 10;
	if (prog->map.data[(y - 5) / 64][(x + 10) / 64] == '1' ||
		prog->map.data[(y + 5) / 64][(x + 10) / 64] == '1')
		prog->player.x = ((x / 64) + 1) * 64 - 10;
}

void	updateplayer(t_prog *prog)
{
	updaterot(prog);
	updatepos(prog);
	colisioncheck(prog, prog->player.x, prog->player.y);
}

void	updatemouse(t_prog *prog)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(prog->mlx, prog->win, &x, &y);
	prog->player.rot += x - (WIN_W / 2);
	mlx_mouse_move(prog->mlx, prog->win, WIN_W / 2, WIN_H / 2);
}
