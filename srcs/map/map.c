/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:51:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/24 23:31:06 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

char	*skip_until_map(int fd, char *buff)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	while (buff && (ft_strchr(buff, '1') == 0
			|| ft_strchr("CFNSWE", buff[0])))
	{
		if (tmp2)
			free(tmp2);
		free(buff);
		tmp = get_next_line(fd);
		tmp2 = ft_strdup(tmp);
		buff = ft_strtrim(tmp, " ");
		free(tmp);
	}
	free(buff);
	return (tmp2);
}

void	push_to_map(t_prog *prog, char *buff)
{
	char	*tmp;
	char	**arrtmp;

	if (ft_strrchr(buff, '\n') && ft_strrchr(buff, '\n')[1] == 0)
		tmp = ft_substr(buff, 0, ft_strlen(buff) - 1);
	else
		tmp = ft_strdup(buff);
	arrtmp = prog->map.data;
	prog->map.data = ft_strarrpush(arrtmp, tmp);
	free(arrtmp);
}

int	check_file_map(char *buff, int fd)
{
	char	*tmp;

	tmp = ft_strtrim(buff, " \n");
	if (!tmp)
	{
		free(buff);
		close(fd);
		return (write(2, "Error\nCub3D: Map has empty lines\n", 34) - 34);
	}
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		free(buff);
		close(fd);
		return (write(2, "Error\nCub3D: Map has empty lines\n", 34) - 34);
	}
	free(tmp);
	return (1);
}

int	check_file_return(char *buff, int fd)
{
	if (!check_file_map(buff, fd))
	{
		close(fd);
		return (0);
	}
	return (1);
}

int	getmap(t_prog *prog, char *path)
{
	int		fd;
	char	*buff;

	prog->map.data = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	buff = get_next_line(fd);
	buff = skip_until_map(fd, buff);
	if (!buff)
	{
		close(fd);
		return (write(2, "Error\nCub3D: No map in file\n", 28) - 28);
	}
	while (buff)
	{
		if (!check_file_return(buff, fd))
			return (0);
		if (ft_strlen(buff) > 1)
			push_to_map(prog, buff);
		free(buff);
		buff = get_next_line(fd);
	}
	close(fd);
	return (1);
}
