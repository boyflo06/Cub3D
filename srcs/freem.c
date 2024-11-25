/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freem.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@stduent.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:54:54 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/25 16:54:42 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_prog_p2(t_prog *prog)
{
	int	i;

	i = -1;
	if (prog->map.data)
	{
		while (prog->map.data[++i])
			free(prog->map.data[i]);
		free(prog->map.data);
	}
	if (prog->win && prog->mlx)
		mlx_destroy_window(prog->mlx, prog->win);
	if (prog->img.img && prog->mlx)
		mlx_destroy_image(prog->mlx, prog->img.img);
	if (prog->mlx)
	{
		mlx_destroy_display(prog->mlx);
		free(prog->mlx);
	}
}

void	free_prog(t_prog *prog)
{
	if (prog->map.no_src)
		free(prog->map.no_src);
	if (prog->map.so_src)
		free(prog->map.so_src);
	if (prog->map.we_src)
		free(prog->map.we_src);
	if (prog->map.ea_src)
		free(prog->map.ea_src);
	if (prog->map.no.img)
		mlx_destroy_image(prog->mlx, prog->map.no.img);
	if (prog->map.so.img)
		mlx_destroy_image(prog->mlx, prog->map.so.img);
	if (prog->map.we.img)
		mlx_destroy_image(prog->mlx, prog->map.we.img);
	if (prog->map.ea.img)
		mlx_destroy_image(prog->mlx, prog->map.ea.img);
	free_prog_p2(prog);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	destroy(t_prog *prog)
{
	free_prog(prog);
	exit(0);
}
