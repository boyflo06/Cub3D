/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:17:26 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/24 15:49:35 by mleonet          ###   ########.fr       */
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

char	*assign_file(char *str)
{
	char	*res;
	int		fd;

	str = ft_strtrim(str, " \n");
	if (!str)
		return (NULL);
	if (!check_textures_format(str))
	{
		free(str);
		return (NULL);
	}
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		free(str);
		return (NULL);
	}
	close(fd);
	res = ft_strdup(str);
	free(str);
	return (res);
}

int assign_textures(t_prog *prog, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		if (prog->map.no_src)
			return (0);
		prog->map.no_src = assign_file(line + 2);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (prog->map.so_src)
			return (0);
		prog->map.so_src = assign_file(line + 2);
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (prog->map.we_src)
			return (0);
		prog->map.we_src = assign_file(line + 2);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (prog->map.ea_src)
			return (0);
		prog->map.ea_src = assign_file(line + 2);
	}
	return (1);
}

int	assign_values_file(t_prog *prog, char *line)
{
	while (*line == ' ')
		line++;	
	if (!assign_textures(prog, line))
		return (0);
	else if (ft_strncmp(line, "F", 1) == 0)
	{
		if (prog->map.f)
			return (0);
		prog->map.f = assign_rgb(line + 1);
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (prog->map.c)
			return (0);
		prog->map.c = assign_rgb(line + 1);
	}
	return (1);
}

int	check_file_format(t_prog *prog, char *path)
{
	int		fd;
	char	*line;

	if (check_file_name(path) == 0)
		return (write(2, "Error\nCub3D: Wrong file name\n", 29) - 29);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error\nCub3D: Cannot open file\n", 30) - 30);
	line = get_next_line(fd);
	if (!line)
		return (write(2, "Error\nCub3D: Empty file\n", 24) - 24);
	while (line)
	{
		if (!assign_values_file(prog, line))
			return (write(2, "Error\nCub3D: Wrong data in file\n", 32) - 32);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!prog->map.no_src || !prog->map.so_src || !prog->map.we_src
		|| !prog->map.ea_src || !prog->map.f || !prog->map.c)
		return (write(2, "Error\nCub3D: Wrong data in file\n", 32) - 32);
	return (1);
}
