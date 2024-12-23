/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapassign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:13:16 by mleonet           #+#    #+#             */
/*   Updated: 2024/11/24 23:24:48 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

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

int	assign_textures(t_prog *prog, char *line)
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
		if (!prog->map.f)
			return (0);
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (prog->map.c)
			return (0);
		prog->map.c = assign_rgb(line + 1);
		if (!prog->map.c)
			return (0);
	}
	return (1);
}

int	add_spaces_map(t_prog *prog)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = NULL;
	while (prog->map.data[i])
	{
		j = ft_strlen(prog->map.data[i]);
		if (j < prog->map.width)
		{
			new_line = malloc(prog->map.width + 1);
			if (!new_line)
				return (0);
			ft_strlcpy(new_line, prog->map.data[i], j + 1);
			while (j < prog->map.width)
				new_line[j++] = ' ';
			new_line[j] = '\0';
			free(prog->map.data[i]);
			prog->map.data[i] = new_line;
		}
		i++;
	}
	return (1);
}
