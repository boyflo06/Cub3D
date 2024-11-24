/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:17:26 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/24 23:21:15 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	check_file_name(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

int	check_textures_format(char *str)
{
	if (ft_strlen(str) < 5)
		return (0);
	if (ft_strncmp(str + ft_strlen(str) - 4, ".xpm", 4) != 0)
		return (0);
	return (1);
}

int	check_line(t_prog *prog, char *line, int fd)
{
	while (line)
	{
		if (!assign_values_file(prog, line))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	check_file_format(t_prog *prog, char *path)
{
	int		fd;
	char	*line;

	if (!check_file_name(path))
		return (write(2, "Error\nCub3D: Wrong file name\n", 29) - 29);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error\nCub3D: Cannot open file\n", 30) - 30);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (write(2, "Error\nCub3D: Empty file\n", 24) - 24);
	}
	if (!check_line(prog, line, fd))
	{
		close(fd);
		return (write(2, "Error\nCub3D: Wrong data in file\n", 32) - 32);
	}
	close(fd);
	if (!prog->map.no_src || !prog->map.so_src || !prog->map.we_src
		|| !prog->map.ea_src || !prog->map.f || !prog->map.c)
		return (write(2, "Error\nCub3D: Wrong data in file\n", 32) - 32);
	return (1);
}
