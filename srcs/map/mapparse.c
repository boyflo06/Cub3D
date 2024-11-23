/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:34:58 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/23 16:36:47 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	check_map_contenter(t_prog *prog, int i, int j, int *player)
{
	if (!ft_strchr(" 01NSWE", prog->map.data[i][j]))
		return (0);
	if (ft_strchr("NSWE", prog->map.data[i][j]))
		(*player)++;
	if ((i == 0 || i == prog->map.height - 1 || j == 0
			|| j == prog->map.width - 1)
		&& !ft_strchr(" 1", prog->map.data[i][j]))
		return (0);
	if (prog->map.data[i][j] == ' ' && i < prog->map.height
		&& j < prog->map.width - 1)
	{
		if (i > 0 && !ft_strchr(" 1", prog->map.data[i - 1][j]))
			return (0);
		if (i < prog->map.height - 1
			&& !ft_strchr(" 1", prog->map.data[i + 1][j]))
			return (0);
		if (j > 0 && !ft_strchr(" 1", prog->map.data[i][j - 1]))
			return (0);
		if (j < prog->map.width - 1
			&& !ft_strchr(" 1", prog->map.data[i][j + 1]))
			return (0);
	}
	return (1);
}

int	check_map_content(t_prog *prog)
{
	int	i;
	int	j;
	int	player;

	i = -1;
	player = 0;
	while (prog->map.data[++i])
	{
		j = -1;
		while (prog->map.data[i][++j])
		{
			if (!check_map_contenter(prog, i, j, &player))
				return (0);
		}
		if (player > 1)
			return (0);
	}
	return (1);
}

int	parsemap(t_prog *prog)
{
	int		i;
	int		j;
	int		width;

	i = 0;
	j = 0;
	width = 0;
	while (prog->map.data[i])
	{
		j = ft_strlen(prog->map.data[i]);
		if (j > width)
			width = j;
		i++;
	}
	prog->map.height = i;
	prog->map.width = width;
	if (!add_spaces_map(prog))
		return (write(2, "Error\nCub3D: Malloc failed\n", 27) - 27);
	if (!check_map_content(prog))
		return (write(2, "Error\nCub3D: Invalid map\n", 25) - 25);
	return (1);
}
