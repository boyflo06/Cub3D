/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@stduent.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:52:34 by mleonet           #+#    #+#             */
/*   Updated: 2024/11/25 13:59:15 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//TODO: ADD more checks trust
int	getplayer(t_prog *prog)
{
	int	i;
	int	j;

	i = -1;
	while (prog->map.data[++i])
	{
		j = -1;
		while (prog->map.data[i][++j])
		{
			if (!ft_strchr("NSWE", prog->map.data[i][j]))
				continue ;
			prog->player.x = (j << 6) + 32;
			prog->player.y = (i << 6) + 32;
			if (prog->map.data[i][j] == 'N')
				return ((prog->player.rot = 270));
			if (prog->map.data[i][j] == 'S')
				return ((prog->player.rot = 90));
			if (prog->map.data[i][j] == 'E')
				return ((prog->player.rot = 0));
			if (prog->map.data[i][j] == 'W')
				return ((prog->player.rot = 180));
		}
	}
	return (-1);
}

int	openimages(t_prog *prog)
{
	prog->map.no.img = mlx_xpm_file_to_image(prog->mlx, prog->map.no_src,
			&prog->map.no.w, &prog->map.no.h);
	prog->map.so.img = mlx_xpm_file_to_image(prog->mlx, prog->map.so_src,
			&prog->map.so.w, &prog->map.so.h);
	prog->map.ea.img = mlx_xpm_file_to_image(prog->mlx, prog->map.ea_src,
			&prog->map.ea.w, &prog->map.ea.h);
	prog->map.we.img = mlx_xpm_file_to_image(prog->mlx, prog->map.we_src,
			&prog->map.we.w, &prog->map.we.h);
	if (!prog->map.no.img || !prog->map.so.img || !prog->map.ea.img
		|| !prog->map.we.img)
		return (0);
	prog->map.no.addr = mlx_get_data_addr(prog->map.no.img, &prog->map.no.bpp,
			&prog->map.no.ll, &prog->map.no.end);
	prog->map.so.addr = mlx_get_data_addr(prog->map.so.img, &prog->map.so.bpp,
			&prog->map.so.ll, &prog->map.so.end);
	prog->map.ea.addr = mlx_get_data_addr(prog->map.ea.img, &prog->map.ea.bpp,
			&prog->map.ea.ll, &prog->map.ea.end);
	prog->map.we.addr = mlx_get_data_addr(prog->map.we.img, &prog->map.we.bpp,
			&prog->map.we.ll, &prog->map.we.end);
	return (1);
}

int	initprog(t_prog *prog, char *path)
{
	default_prog(prog);
	if (!check_file_format(prog, path))
	{
		free_prog(prog);
		return (0);
	}
	prog->mlx = mlx_init();
	if (!prog->mlx)
	{
		free_prog(prog);
		return (write(2, "Error\nCub3D: Cannot init mlx\n", 29) - 29);
	}
	if (!getmap(prog, path) || !openimages(prog))
		return (free_prog(prog), 0);
	if (!parsemap(prog))
		return (free_prog(prog), 0);
	getplayer(prog);
	prog->win = mlx_new_window(prog->mlx, WIN_W, WIN_H, "Hello World!");
	if (!prog->win)
	{
		free_prog(prog);
		return (write(2, "Error\nCub3D: Cannot create window\n", 34) - 34);
	}
	return (1);
}
