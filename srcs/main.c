/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/18 16:52:52 by mleonet          ###   ########.fr       */
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

int	itoargb(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
{
	return ((((int)255 - (int)a) << 24) | ((int)r << 16) | ((int)g << 8) | b);
}

char	**ft_strarrpush(char	**arr, char *newstr)
{
	int		i;
	char	**res;

	i = -1;
	if (!newstr)
		return (NULL);
	if (!arr)
	{
		res = ft_calloc(2, sizeof(char *));
		if (!res)
			return (NULL);
		res[0] = newstr;
		return (res);
	}
	while (arr[++i])
		;
	res = malloc(sizeof(char *) * (i + 2));
	if (!res)
		return (NULL);
	i = -1;
	while (arr[++i])
		res[i] = arr[i];
	res[i] = newstr;
	res[i + 1] = 0;
	return (res);
}

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

char	*rem_spaces(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			res[j++] = str[i];
		i++;
	}
	res[j] = 0;
	return (res);
}

int	check_rgb(char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (!ft_isdigit(arr[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	i = 0;
	while (arr[i])
	{
		if (ft_atoi(arr[i]) < 0 || ft_atoi(arr[i]) > 255)
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

int	assign_rgb(char *str)
{
	char	**arr;
	int		tmp;

	str = rem_spaces(str);
	if (!str)
		return (0);
	arr = ft_split(str, ',');
	free(str);
	if (!arr)
		return (0);
	if (!check_rgb(arr))
	{
		free_tab(arr);
		return (0);
	}
	tmp = itoargb(255, ft_atoi(arr[0]),
			ft_atoi(arr[1]), ft_atoi(arr[2]));
	free_tab(arr);
	return (tmp);
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

char	*skip_until_map(int fd, char *buff)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	while (buff && (ft_strchr(buff, '1') == 0
			|| ft_strchr("CFNOSEW", buff[0])))
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
		if (!check_file_map(buff, fd))
			return (0);
		if (ft_strlen(buff) > 1)
			push_to_map(prog, buff);
		free(buff);
		buff = get_next_line(fd);
	}
	close(fd);
	return (1);
}

double	degtorad(double deg)
{
	return (deg * (PI / 180));
}

double	radtodeg(double rad)
{
	return (rad * (180 / PI));
}

void	ft_pixelput(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_putline(t_data *data, t_point p1, t_point p2, int color, int width)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	if (!width)
		return ;
	p1.x = (int) p1.x; p1.y = (int) p1.y; p2.x = (int) p2.x; p2.y = (int) p2.y;
	dx = abs((int) (p2.x - p1.x));
	dy = abs((int) (p2.y - p1.y));
	if (p1.x < p2.x)
		sx = 1;
	else
		sx = -1;
	if (p1.y < p2.y)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		for (int i = -width / 2; i <= width / 2; i++)
		{
			//printf("%f %f	%f %f\n", (p1.x), (p1.y) + i, (p1.x) + i, p1.y);
			if (dx > dy && ((int) p1.x) >= 0 && ((int) p1.y) + i >= 0)
				ft_pixelput(data, ((int) p1.x), ((int) p1.y) + i, color);
			else if (((int) p1.x) + i >= 0 && ((int) p1.y) >= 0)
				ft_pixelput(data, ((int) p1.x) + i, (int) p1.y, color);
		}
		if ((int) p1.x == (int) p2.x && (int) p1.y == (int) p2.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			p1.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			p1.y += sy;
		}
	}
}

void	display2D(t_prog *prog, t_data *img) {
	for (int x = 0; x < WIN_W; x++) {
		for (int y = 0; y < WIN_H; y++) {
			ft_pixelput(img, x, y, itoargb(255, 155, 155, 155));
		}
	}
	for (int y = 0; prog->map.data[y >> 6]; y++)
	{
		for (int x = 0; prog->map.data[y >> 6][x >> 6]; x++)
		{
			if (((y >> 6) << 6 == y) || (x >> 6) << 6 == x)
				continue ;
			if (prog->map.data[y >> 6][x >> 6] == '1')
				ft_pixelput(img, x, y, itoargb(255, 200, 200, 200));
			else if (ft_strchr("0NSWE", prog->map.data[y >> 6][x >> 6])
				&& prog->map.data[y >> 6][x >> 6] != 0)
				ft_pixelput(img, x, y, itoargb(255, 100, 100, 100));
		}
	}
}


t_point	getpointercoords(t_prog	*prog)
{
	double	adj;
	double	opp;

	adj = -cos(degtorad(prog->player.rot)) * 20.0;
	opp = -sin(degtorad(prog->player.rot)) * 20.0;
	return ((t_point) {prog->player.x + adj, prog->player.y + opp});
}

void	displayplayer2D(t_prog *prog, t_data *img)
{
	for (int x = prog->player.x - 2; x < prog->player.x + 2; x++)
	{
		for (int y = prog->player.y - 2; y < prog->player.y + 2; y++)
			ft_pixelput(img, x, y, itoargb(255, 230, 230, 0));
	}
	//ft_putline(img, (t_point) {prog->player.x, prog->player.y},
		//getpointercoords(prog), itoargb(255, 230, 230, 0), 1);
}

void	updateplayer(t_prog *prog)
{
	float	dx;
	float	dy;
	double	oldx;
	double	oldy;
	if ((prog->keys >> 5) % 2)
		prog->player.rot += 1.0 * (60 / prog->fps);
	if ((prog->keys >> 4) % 2)
		prog->player.rot -= 1.0 * (60 / prog->fps);
	if (prog->player.rot > 359)
		prog->player.rot -= 360;
	if (prog->player.rot < 0)
		prog->player.rot += 360;
	dx = cos(degtorad(prog->player.rot)) * 2 * (60 / prog->fps);
	dy = sin(degtorad(prog->player.rot)) * 2 * (60 / prog->fps);
	oldx = prog->player.x;
	oldy = prog->player.y;
	if (prog->keys % 2)
	{
		prog->player.x += dx;
		prog->player.y += dy;
	}
	if ((prog->keys >> 1) % 2)
	{
		prog->player.x -= dx;
		prog->player.y -= dy;
	}
	if (prog->keys & KEY_RIGHT)
	{
		prog->player.x -= dy;
		prog->player.y += dx;
	}
	if (prog->keys & KEY_LEFT)
	{
		prog->player.x += dy;
		prog->player.y -= dx;
	}
	if (prog->map.data[(int) prog->player.y >> 6][(int) oldx >> 6] == '1')
		prog->player.y = oldy;
	if (prog->map.data[(int) oldy >> 6][(int) prog->player.x >> 6] == '1')
		prog->player.x = oldx;
	if (prog->map.data[(int) prog->player.y >> 6][(int) prog->player.x >> 6] == '1' &&
		prog->map.data[(int) prog->player.y >> 6][(int) oldx >> 6] != '1' && prog->map.data[(int) oldy >> 6][(int) prog->player.x >> 6] != '1')
	{
		prog->player.x = oldx;
		prog->player.y = oldy;
	}
}

void	updatemouse(t_prog *prog)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(prog->mlx, prog->win, &x, &y);
	prog->player.rot += x - (WIN_W / 2);
	mlx_mouse_move(prog->mlx, prog->win, WIN_W / 2, WIN_H / 2);
}

int	loop(t_prog	*prog)
{
	t_data			img;
	static long		milisave = 0;
	struct timeval	currenttime;
	long			miliseconds;

	gettimeofday(&currenttime, NULL);
	miliseconds = currenttime.tv_sec * 1000 + currenttime.tv_usec / 1000;
	if (milisave)
		prog->fps = (1000.0 / (float) (miliseconds - milisave));
	milisave = miliseconds;
	img.img = mlx_new_image(prog->mlx, WIN_W, WIN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.end);
	if (prog->keys & KEY_TOGMOUSE)
		updatemouse(prog);
	updateplayer(prog);
	raycast(prog, &img);
	printf("%d\n", prog->keys);
	mlx_put_image_to_window(prog->mlx, prog->win, img.img, 0, 0);
	mlx_destroy_image(prog->mlx, img.img);
	return (1);
}

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
			if (prog->map.data[i][++j] == 'N')
				return ((prog->player.rot = 0));
			if (prog->map.data[i][++j] == 'S')
				return ((prog->player.rot = 180));
			if (prog->map.data[i][++j] == 'E')
				return ((prog->player.rot = 90));
			if (prog->map.data[i][++j] == 'W')
				return ((prog->player.rot = 270));
		}
	}
	return (-1);
}

int	keypress(int key, t_prog *prog)
{
	if (key == 'w')
		prog->keys = prog->keys | KEY_UP;
	else if (key == 's')
		prog->keys = prog->keys | KEY_DOWN;
	else if (key == 'a')
		prog->keys = prog->keys | KEY_LEFT;
	else if (key == 'd')
		prog->keys = prog->keys | KEY_RIGHT;
	else if (key == 65363)
		prog->keys = prog->keys | KEY_ARRRIGHT;
	else if (key == 65361)
		prog->keys = prog->keys | KEY_ARRLEFT;
	/* else if (key == 'v' && !(prog->keys & KEY_TOGMOUSE))
		prog->keys = prog->keys | KEY_TOGMOUSE;
	else if (key == 'v' && (prog->keys & KEY_TOGMOUSE))
		prog->keys = prog->keys & ~(KEY_TOGMOUSE); */
	else if (key == 'v')
		prog->keys = prog->keys ^ KEY_TOGMOUSE;
	return (1);
}

int	keyrelease(int key, t_prog *prog)
{
	if (key == 'w')
		prog->keys = prog->keys & ~(KEY_UP);
	if (key == 's')
		prog->keys = prog->keys & ~(KEY_DOWN);
	if (key == 'a')
		prog->keys = prog->keys & ~(KEY_LEFT);
	if (key == 'd')
		prog->keys = prog->keys & ~(KEY_RIGHT);
	if (key == 65363)
		prog->keys = prog->keys & ~(KEY_ARRRIGHT);
	if (key == 65361)
		prog->keys = prog->keys & ~(KEY_ARRLEFT);
	return (1);
}

void	openimages(t_prog *prog){
	prog->map.NO.img = mlx_xpm_file_to_image(prog->mlx, "./bricks.xpm", &prog->map.NO.w, &prog->map.NO.h);
	prog->map.NO.addr = mlx_get_data_addr(prog->map.NO.img, &prog->map.NO.bpp, &prog->map.NO.ll, &prog->map.NO.end);
	prog->map.SO.img = mlx_xpm_file_to_image(prog->mlx, "./stone.xpm", &prog->map.SO.w, &prog->map.SO.h);
	prog->map.SO.addr = mlx_get_data_addr(prog->map.SO.img, &prog->map.SO.bpp, &prog->map.SO.ll, &prog->map.SO.end);
	prog->map.EA.img = mlx_xpm_file_to_image(prog->mlx, "./EA.xpm", &prog->map.EA.w, &prog->map.EA.h);
	prog->map.EA.addr = mlx_get_data_addr(prog->map.EA.img, &prog->map.EA.bpp, &prog->map.EA.ll, &prog->map.EA.end);
	prog->map.WE.img = mlx_xpm_file_to_image(prog->mlx, "./EA.xpm", &prog->map.WE.w, &prog->map.WE.h);
	prog->map.WE.addr = mlx_get_data_addr(prog->map.WE.img, &prog->map.WE.bpp, &prog->map.WE.ll, &prog->map.WE.end);
}

int	main(int argc, char **argv)
{
	t_prog	prog;

	if (argc != 2)
		return (write(2, "Error\nCub3D: Wrong number of args\n", 34) - 33);
	init_prog(&prog);
	if (!check_file_format(&prog, argv[1]))
	{
		free_prog(&prog);
		return (1);
	}
	prog.mlx = mlx_init();
	if (!prog.mlx)
	{
		free_prog(&prog);
		return (write(2, "Error\nCub3D: Cannot init mlx\n", 29) - 28);
	}
	prog.win = mlx_new_window(prog.mlx, WIN_W, WIN_H, "Hello World!");
	if (!prog.win)
	{
		free_prog(&prog);
		return (write(2, "Error\nCub3D: Cannot create window\n", 34) - 33);
	}
	if (!getmap(&prog, argv[1]))
	{
		free_prog(&prog);
		return (1);
	}
	int i;
	for (i = 0; prog.map.data[i]; i++)
		;
	prog.map.height = i;
	prog.map.width = ft_strlen(prog.map.data[0]);
	openimages(&prog);
	getplayer(&prog);
	prog.player.rot = 270;
	prog.keys = 0;
	mlx_mouse_hide(prog.mlx, prog.win);
	mlx_hook(prog.win, 2, 1L << 0, keypress, &prog);
	mlx_hook(prog.win, 3, 1L << 1, keyrelease, &prog);
	mlx_loop_hook(prog.mlx, loop, &prog);
	mlx_do_key_autorepeatoff(prog.mlx);
	mlx_loop(prog.mlx);
}
