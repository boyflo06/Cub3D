/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/24 17:37:07 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

int	getmap(t_prog *prog, char *path)
{
	int		fd;
	char	*buff;
	char	*tmp;
	char	**arrtmp;

	prog->map.data = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	buff = get_next_line(fd);
	while (buff) {
		if (ft_strlen(buff) > 1)
		{
			if (ft_strrchr(buff, '\n') && ft_strrchr(buff, '\n')[1] == 0)
				tmp = ft_substr(buff, 0, ft_strlen(buff) - 1);
			else
				tmp = ft_strdup(buff);
			arrtmp = prog->map.data;
			prog->map.data = ft_strarrpush(arrtmp, tmp);
			free(arrtmp);
		}
		free(buff);
		buff = get_next_line(fd);
	}
	return (1);
}

double	degtorad(double deg)
{
	return (deg * (PI/180));
}

void	ft_pixelput(t_data *data, int x, int y, int color) {
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_putline(t_data *data, t_point p1, t_point p2, int color, int width) {
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	if (!width)
		return ;
	dx = abs(p2.x - p1.x);
	dy = abs(p2.y - p1.y);
	if (p1.x < p2.x)
		sx = 1;
	else
		sx = -1;
	if (p1.y < p2.y)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1) {
		for (int i = -width / 2; i <= width / 2; i++) {
			if (dx > dy) {
				ft_pixelput(data, p1.x, p1.y + i, color);
			} else {
				ft_pixelput(data, p1.x + i, p1.y, color);
			}
		}

		if (p1.x == p2.x && p1.y == p2.y)
			break;
		e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			p1.x += sx;
		}
		if (e2 < dx) {
			err += dx;
			p1.y += sy;
		}
	}
}

t_point	getvdistance(t_prog *prog, int rot)
{
	double	tmp;
	int		i;
	int		x;

	if (rot < 180 && rot > 0)
	{
		tmp = - (prog->player.y - ((prog->player.y >> 6) << 6)) / tan(degtorad((double) rot));
		if ((prog->player.y >> 6) - 1 >= 0 && ((prog->player.x + (int) tmp)) >> 6 >= 0 && prog->map.data[(prog->player.y >> 6) - 1][((prog->player.x + (int) tmp)) >> 6] == '1')
			return ((t_point) {(prog->player.x + tmp), (prog->player.y >> 6) << 6});
		i = (prog->player.y >> 6) - 2;
		x = prog->player.x + tmp - (64 / tan(degtorad((double) rot)));
		tmp = - (64 / tan(degtorad((double) rot)));
		while (i >= 0) {
			if (x >> 6 >= 0 && prog->map.data[i][x >> 6] == '1')
				return ((t_point) {x, (i + 1) << 6});
			i--;
			x += tmp;
		}
	}
	else if (rot > 180)
	{
		tmp = - ((prog->player.y - (((prog->player.y >> 6) + 1) << 6)) / tan(degtorad((double) rot)));
		if ((prog->player.y >> 6) + 1 >= 0 && ((prog->player.x + (int) tmp)) >> 6 >= 0 && prog->map.data[(prog->player.y >> 6) + 1][((prog->player.x + (int) tmp)) >> 6] == '1')
			return ((t_point) {(prog->player.x + tmp), ((prog->player.y >> 6) + 1) << 6});
		i = (prog->player.y >> 6) + 2;
		x = prog->player.x + tmp + (64 / tan(degtorad((double) rot)));
		tmp = + (64 / tan(degtorad((double) rot)));
		while (i < prog->map.height) {
			printf("{%d, %d}\n", x >> 6, i);
			if (x >> 6 >= 0 && prog->map.data[i][x >> 6] == '1')
				return ((t_point) {x, (i) << 6});
			i++;
			x += tmp;
		}
	}
	return ((t_point) {-1, -1});
}

t_point	gethdistance(t_prog *prog, int rot)
{
	double	tmp;
	int		i;
	int		y;

	if (rot > 270 || rot < 90)
	{
		if (rot == 0)
			tmp = 0;
		else
			tmp = - (prog->player.x - ((prog->player.x >> 6) << 6)) * tan(degtorad((double) rot));
		if ((prog->player.x >> 6) - 1 >= 0 && (prog->player.x >> 6) - 1 < prog->map.width && ((prog->player.y + (int) tmp)) >> 6 >= 0 && ((prog->player.y + (int) tmp)) >> 6 < prog->map.height && prog->map.data[(prog->player.y + (int) tmp) >> 6][(prog->player.x >> 6) - 1] == '1')
			return ((t_point) {(prog->player.x >> 6) << 6, prog->player.y + tmp});
		i = (prog->player.x >> 6) - 2;
		y = prog->player.y + tmp - (64 * tan(degtorad((double) rot)));
		tmp = - (64 * tan(degtorad((double) rot)));
		while (i >= 0) {
			if (y >> 6 >= 0 && y >> 6 < prog->map.height && prog->map.data[y >> 6][i] == '1')
				return ((t_point) {(i + 1) << 6, y});
			i--;
			y += tmp;
		}
	}
	if (rot > 90 && rot < 270)
	{
		tmp = - ((prog->player.x - (((prog->player.x >> 6) + 1) << 6)) * tan(degtorad((double) rot)));
		printf("{%d, %d}\n", (prog->player.x >> 6) - 1, (prog->player.y + (int) tmp) >> 6);
		if ((prog->player.x >> 6) + 1 >= 0 && (prog->player.x >> 6) + 1 < prog->map.width && ((prog->player.y + (int) tmp)) >> 6 >= 0 && ((prog->player.y + (int) tmp)) >> 6 < prog->map.height && prog->map.data[(prog->player.y + (int) tmp) >> 6][(prog->player.x >> 6) + 1] == '1')
			return ((t_point) {((prog->player.x >> 6) + 1) << 6, (prog->player.y + tmp)});
		i = (prog->player.x >> 6) + 2;
		y = prog->player.y + tmp + (64 * tan(degtorad((double) rot)));
		tmp = + (64 * tan(degtorad((double) rot)));
		while (i < prog->map.width) {
			//printf("{%d, %d}\n", x >> 6, i);
			if (y >> 6 >= 0 && y >> 6 < prog->map.height && prog->map.data[y >> 6][i] == '1')
				return ((t_point) {(i) << 6, y});
			i++;
			y += tmp;
		}
	}
	return ((t_point) {-1, -1});
}

int	getdistance(t_prog *prog, int rot, t_data *img)
{
	t_point	vdis;
	t_point	hdis;
	
	vdis = getvdistance(prog, rot);
	hdis = gethdistance(prog, rot);

	if (vdis.x != -1 && vdis.y != -1)
		ft_putline(img, (t_point) {prog->player.x, prog->player.y}, vdis, itoargb(255, 0, 230, 0), 5);
	if (hdis.x != -1 && hdis.y != -1)
		ft_putline(img, (t_point) {prog->player.x, prog->player.y}, hdis, itoargb(255, 230, 0, 0), 1);
	return (1);
}

/* int	raycast(t_prog *prog)
{
	t_data	img;
	img.img = mlx_new_image(prog->mlx, 1280, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.end);

	int		irot = prog->player.rot - 46;
	while (++irot <= prog->player.rot++) {
		int	getd = getdistance()
	}
} */

void	display2D(t_prog *prog, t_data *img) {
	for (int x = 0; x < 1280; x++) {
		for (int y = 0; y < 720; y++) {
			ft_pixelput(img, x, y, itoargb(255, 155, 155, 155));
		}
	}
	for (int y = 0; prog->map.data[y >> 6]; y++) {
		for (int x = 0; prog->map.data[y >> 6][x >> 6]; x++) {
			if (((y >> 6) << 6 == y) || (x >> 6) << 6 == x)
				continue;
			if (prog->map.data[y >> 6][x >> 6] == '1')
				ft_pixelput(img, x, y, itoargb(255, 200, 200, 200));
			else if (ft_strchr("0NSWE", prog->map.data[y >> 6][x >> 6]) && prog->map.data[y >> 6][x >> 6] != 0)
				ft_pixelput(img, x, y, itoargb(255, 100, 100, 100));
		}
	}
}

t_point	getpointercoords(t_prog	*prog) {
	double	adj;
	double	opp;

	adj = -cos(degtorad(prog->player.rot)) * 20.0;
	opp = -sin(degtorad(prog->player.rot)) * 20.0;
	return ((t_point) {prog->player.x + adj, prog->player.y + opp});
}

void	displayplayer2D(t_prog *prog, t_data *img) {
	for (int x = prog->player.x - 2; x < prog->player.x + 2; x++) {
		for (int y = prog->player.y - 2; y < prog->player.y + 2; y++) {
			ft_pixelput(img, x, y, itoargb(255, 230, 230, 0));
		}
	}
	ft_putline(img, (t_point) {prog->player.x, prog->player.y}, getpointercoords(prog), itoargb(255, 230, 230, 0), 1);
}

/* int	displayRaycast2D(t_prog *prog, t_data *img) {
	double	tmp;
	int		rot;
	int		i;
	int		x;

	rot = prog->player.rot;
	if (rot < 180 && rot > 0)
	{
		tmp = - (prog->player.y - ((prog->player.y >> 6) << 6)) / tan(degtorad((double) rot));
		if ((prog->player.y >> 6) - 1 >= 0 && ((prog->player.x + (int) tmp)) >> 6 >= 0 && prog->map.data[(prog->player.y >> 6) - 1][((prog->player.x + (int) tmp)) >> 6] == '1')
			return (ft_putline(img, (t_point) {prog->player.x, prog->player.y}, (t_point) {(prog->player.x + tmp), (prog->player.y >> 6) << 6}, itoargb(255, 0, 0, 230), 1), 1);
		i = (prog->player.y >> 6) - 2;
		x = prog->player.x + tmp - (64 / tan(degtorad((double) rot)));
		tmp = - (64 / tan(degtorad((double) rot)));
		while (i >= 0) {
			if (x >> 6 >= 0 && prog->map.data[i][x >> 6] == '1')
				return (ft_putline(img, (t_point) {prog->player.x, prog->player.y}, (t_point) {x, (i + 1) << 6}, itoargb(255, 0, 0, 230), 1), 1);
			i--;
			x += tmp;
		}
	}
	else if (rot > 180)
	{
		tmp = - ((prog->player.y - (((prog->player.y >> 6) + 1) << 6)) / tan(degtorad((double) rot)));
		if ((prog->player.y >> 6) + 1 >= 0 && ((prog->player.x + (int) tmp)) >> 6 >= 0 && prog->map.data[(prog->player.y >> 6) + 1][((prog->player.x + (int) tmp)) >> 6] == '1')
			return (ft_putline(img, (t_point) {prog->player.x, prog->player.y}, (t_point) {(prog->player.x + tmp), ((prog->player.y >> 6) + 1) << 6}, itoargb(255, 0, 0, 230), 1), 1);
		i = (prog->player.y >> 6) + 2;
		x = prog->player.x + tmp + (64 / tan(degtorad((double) rot)));
		tmp = + (64 / tan(degtorad((double) rot)));
		while (i < prog->map.height) {
			printf("{%d, %d}\n", x >> 6, i);
			if (x >> 6 >= 0 && prog->map.data[i][x >> 6] == '1')
				return (ft_putline(img, (t_point) {prog->player.x, prog->player.y}, (t_point) {x, (i) << 6}, itoargb(255, 0, 0, 230), 1), 1);
			i++;
			x += tmp;
		}
	}
	return (1);
} */

/* int	displayRaycast2D(t_prog *prog, t_data *img) {
	double	tmp;
	int		rot;
	int		i;
	int		y;

	rot = prog->player.rot;
	printf("%d\n", rot);
	if (rot > 270 || rot < 90)
	{
		if (rot == 0)
			tmp = 0;
		else
			tmp = - (prog->player.x - ((prog->player.x >> 6) << 6)) * tan(degtorad((double) rot));
		if ((prog->player.x >> 6) - 1 >= 0 && (prog->player.x >> 6) - 1 < prog->map.width && ((prog->player.y + (int) tmp)) >> 6 >= 0 && ((prog->player.y + (int) tmp)) >> 6 < prog->map.height && prog->map.data[(prog->player.y + (int) tmp) >> 6][(prog->player.x >> 6) - 1] == '1')
			return (ft_putline(img, (t_point) {prog->player.x, prog->player.y}, (t_point) {(prog->player.x >> 6) << 6, prog->player.y + tmp}, itoargb(255, 0, 0, 230), 1), 1);
		i = (prog->player.x >> 6) - 2;
		y = prog->player.y + tmp - (64 * tan(degtorad((double) rot)));
		tmp = - (64 * tan(degtorad((double) rot)));
		while (i >= 0) {
			if (y >> 6 >= 0 && y >> 6 < prog->map.height && prog->map.data[y >> 6][i] == '1')
				return (ft_putline(img, (t_point) {prog->player.x, prog->player.y}, (t_point) {(i + 1) << 6, y}, itoargb(255, 0, 0, 230), 1), 1);
			i--;
			y += tmp;
		}
	}
	if (rot > 90 && rot < 270)
	{
		tmp = - ((prog->player.x - (((prog->player.x >> 6) + 1) << 6)) * tan(degtorad((double) rot)));
		printf("{%d, %d}\n", (prog->player.x >> 6) - 1, (prog->player.y + (int) tmp) >> 6);
		if ((prog->player.x >> 6) + 1 >= 0 && (prog->player.x >> 6) + 1 < prog->map.width && ((prog->player.y + (int) tmp)) >> 6 >= 0 && ((prog->player.y + (int) tmp)) >> 6 < prog->map.height && prog->map.data[(prog->player.y + (int) tmp) >> 6][(prog->player.x >> 6) + 1] == '1')
			return (ft_putline(img, (t_point) {prog->player.x, prog->player.y}, (t_point) {((prog->player.x >> 6) + 1) << 6, (prog->player.y + tmp)}, itoargb(255, 0, 0, 230), 1), 1);
		i = (prog->player.x >> 6) + 2;
		y = prog->player.y + tmp + (64 * tan(degtorad((double) rot)));
		tmp = + (64 * tan(degtorad((double) rot)));
		while (i < prog->map.width) {
			//printf("{%d, %d}\n", x >> 6, i);
			if (y >> 6 >= 0 && y >> 6 < prog->map.height && prog->map.data[y >> 6][i] == '1')
				return (ft_putline(img, (t_point) {prog->player.x, prog->player.y}, (t_point) {(i) << 6, y}, itoargb(255, 0, 0, 230), 1), 1);
			i++;
			y += tmp;
		}
	}
	return (1);
} */

int	loop(t_prog	*prog) {
	t_data	img;
	img.img = mlx_new_image(prog->mlx, 1280, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.end);
	display2D(prog, &img);
	displayplayer2D(prog, &img);
	getdistance(prog, prog->player.rot, &img);
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

int	keypress(int key, t_prog *prog) {
	if (key == 65363)
	{
		prog->player.rot += 1;
		if (prog->player.rot > 359)
			prog->player.rot -= 360;
	}
	if (key == 65361)
	{
		prog->player.rot -= 1;
		if (prog->player.rot < 0)
			prog->player.rot += 360;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_prog	prog;

	if (argc != 2)
		return (write(2, "Cub3D: Wrong number of args (1 needed)\n", 39) - 38);
	prog.mlx = mlx_init();
	prog.win = mlx_new_window(prog.mlx, 1280, 720, "Hello World!");
	if (!prog.win)
		return (1);
	if (!getmap(&prog, argv[1]))
		return (1);
	int i;
	for (i = 0; prog.map.data[i]; i++)
		;
	prog.map.height = i;
	prog.map.width = ft_strlen(prog.map.data[0]);
	prog.player.x = 288;
	prog.player.y = 224;
	prog.player.rot = 0;
	getplayer(&prog);
	mlx_hook(prog.win, 2, 1L<<0, keypress, &prog);
	mlx_loop_hook(prog.mlx, loop, &prog);
	mlx_loop(prog.mlx);
}