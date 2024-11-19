/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:48:27 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/18 14:51:42 by fghysbre         ###   ########.fr       */
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
	else if (key == 'v')
		prog->keys = prog->keys ^ KEY_TOGMOUSE;
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

int	loop(t_prog	*prog)
{
	t_data			img;
	static long		milisave = 0;
	struct timeval	currenttime;
	long			miliseconds;

	gettimeofday(&currenttime, NULL);
	miliseconds = currenttime.tv_sec * 1000 + currenttime.tv_usec / 1000;
	if (milisave)
		prog->fps = (1000.0 / (float) (miliseconds - milisave));
	milisave = miliseconds;
	img.img = mlx_new_image(prog->mlx, WIN_W, WIN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.end);
	if (prog->keys & KEY_TOGMOUSE)
		updatemouse(prog);
	updateplayer(prog);
	raycast(prog, &img);
	printf("%d\n", prog->keys);
	mlx_put_image_to_window(prog->mlx, prog->win, img.img, 0, 0);
	mlx_destroy_image(prog->mlx, img.img);
	return (1);
}