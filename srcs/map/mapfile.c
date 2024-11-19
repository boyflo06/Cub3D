/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:17:26 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/18 15:26:21 by fghysbre         ###   ########.fr       */
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

void	assign_values_file(t_prog *prog, char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0)
		prog->map.NO_src = assign_file(line + 2);
	else if (ft_strncmp(line, "SO", 2) == 0)
		prog->map.SO_src = assign_file(line + 2);
	else if (ft_strncmp(line, "WE", 2) == 0)
		prog->map.WE_src = assign_file(line + 2);
	else if (ft_strncmp(line, "EA", 2) == 0)
		prog->map.EA_src = assign_file(line + 2);
	else if (ft_strncmp(line, "F", 1) == 0)
		prog->map.F = assign_rgb(line + 1);
	else if (ft_strncmp(line, "C", 1) == 0)
		prog->map.C = assign_rgb(line + 1);
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
		assign_values_file(prog, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!prog->map.NO_src || !prog->map.SO_src || !prog->map.WE_src
		|| !prog->map.EA_src || !prog->map.F || !prog->map.C)
		return (write(2, "Error\nCub3D: Wrong data in file\n", 32) - 32);
	return (1);
}
