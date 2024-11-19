/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freem.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:54:54 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/19 16:52:04 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_prog(t_prog *prog)
{
	int	i;

	i = -1;
	if (prog->map.NO_src)
		free(prog->map.NO_src);
	if (prog->map.SO_src)
		free(prog->map.SO_src);
	if (prog->map.WE_src)
		free(prog->map.WE_src);
	if (prog->map.EA_src)
		free(prog->map.EA_src);
	if (prog->map.data)
	{
		while (prog->map.data[++i])
			free(prog->map.data[i]);
		free(prog->map.data);
	}
	if (prog->win)
		mlx_destroy_window(prog->mlx, prog->win);
	if (prog->mlx)
	{
		mlx_destroy_display(prog->mlx);
		free(prog->mlx);
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
