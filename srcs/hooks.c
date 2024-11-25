/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@stduent.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:48:27 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/25 17:03:08 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	keypress(int key, t_prog *prog)
{
	if (key == 'w')
		prog->keys = prog->keys | KEY_UP;
	else if (key == 's')
		prog->keys = prog->keys | KEY_DOWN;
	else if (key == 'a')
		prog->keys = prog->keys | KEY_LEFT;
	else if (key == 'd')
		prog->keys = prog->keys | KEY_RIGHT;
	else if (key == 65363)
		prog->keys = prog->keys | KEY_ARRRIGHT;
	else if (key == 65361)
		prog->keys = prog->keys | KEY_ARRLEFT;
	else if (key == 65307)
		destroy(prog);
	return (1);
}

int	keyrelease(int key, t_prog *prog)
{
	if (key == 'w')
		prog->keys = prog->keys & ~(KEY_UP);
	if (key == 's')
		prog->keys = prog->keys & ~(KEY_DOWN);
	if (key == 'a')
		prog->keys = prog->keys & ~(KEY_LEFT);
	if (key == 'd')
		prog->keys = prog->keys & ~(KEY_RIGHT);
	if (key == 65363)
		prog->keys = prog->keys & ~(KEY_ARRRIGHT);
	if (key == 65361)
		prog->keys = prog->keys & ~(KEY_ARRLEFT);
	return (1);
}

void	fillbg(t_prog *prog, t_data *img)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
		{
			if (y > WIN_H / 2)
				ft_pixelput(img, x, y, prog->map.f);
			else
				ft_pixelput(img, x, y, prog->map.c);
		}
	}
}

int	loop(t_prog	*prog)
{
	static long		milisave = 0;
	struct timeval	currenttime;
	long			miliseconds;

	gettimeofday(&currenttime, NULL);
	miliseconds = currenttime.tv_sec * 1000 + currenttime.tv_usec / 1000;
	if (milisave)
		prog->fps = (1000.0 / (float)(miliseconds - milisave));
	milisave = miliseconds;
	updateplayer(prog);
	fillbg(prog, &prog->img);
	raycast(prog, &prog->img);
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
	return (1);
}
