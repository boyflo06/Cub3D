/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:52:34 by mleonet           #+#    #+#             */
/*   Updated: 2024/11/19 13:57:33 by fghysbre         ###   ########.fr       */
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
	prog->map.NO.img = mlx_xpm_file_to_image(prog->mlx, prog->map.NO_src,
			&prog->map.NO.w, &prog->map.NO.h);
	prog->map.SO.img = mlx_xpm_file_to_image(prog->mlx, prog->map.SO_src,
			&prog->map.SO.w, &prog->map.SO.h);
	prog->map.EA.img = mlx_xpm_file_to_image(prog->mlx, prog->map.EA_src,
			&prog->map.EA.w, &prog->map.EA.h);
	prog->map.WE.img = mlx_xpm_file_to_image(prog->mlx, prog->map.WE_src,
			&prog->map.WE.w, &prog->map.WE.h);
	if (!prog->map.NO.img || !prog->map.SO.img || !prog->map.EA.img || !prog->map.WE.img)
		return (0);
	prog->map.NO.addr = mlx_get_data_addr(prog->map.NO.img, &prog->map.NO.bpp,
			&prog->map.NO.ll, &prog->map.NO.end);
	prog->map.SO.addr = mlx_get_data_addr(prog->map.SO.img, &prog->map.SO.bpp,
			&prog->map.SO.ll, &prog->map.SO.end);
	prog->map.EA.addr = mlx_get_data_addr(prog->map.EA.img, &prog->map.EA.bpp,
			&prog->map.EA.ll, &prog->map.EA.end);
	prog->map.WE.addr = mlx_get_data_addr(prog->map.WE.img, &prog->map.WE.bpp,
			&prog->map.WE.ll, &prog->map.WE.end);
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
	prog->win = mlx_new_window(prog->mlx, WIN_W, WIN_H, "Hello World!");
	if (!prog->win)
	{
		free_prog(prog);
		return (write(2, "Error\nCub3D: Cannot create window\n", 34) - 34);
	}
	if (!getmap(prog, path) || !openimages(prog))
		return (free_prog(prog), 0);
	getplayer(prog);
	return (1);
}
