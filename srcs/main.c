/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@stduent.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/30 16:47:05 by fghysbre         ###   ########.fr       */
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
	while (buff)
	{
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
	return (deg * (PI / 180));
}
/*
int	getvdistance(t_prog *prog, int rot)
{
	double	tmp;
	if (rot < 180)
	{
		tmp = (prog->player.y - ((prog->player.y >> 6) << 6)) / tan(degtorad((double) rot));
		if (prog->map.data[(prog->player.y >> 6) - 1][((prog->player.x + (int) tmp) >> 6)] == '1')
			return (());
	}
}

int	gethdistance(t_prog *prog, int rot)
{
	
}

int	getdistance(t_prog *prog, int rot)
{
	int	vdis;
	int	hdis;
	if (rot >= 360)
		rot -= 360;
	if (rot < 0)
		rot += 360;
	
	vdis = getvdistance(prog, rot);
	hdis = gethdistance(prog, rot);
}

int	raycast(t_prog *prog)
{
	t_data	img;
	img.img = mlx_new_image(prog->mlx, 1280, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.end);

	int		irot = prog->player.rot - 46;
	while (++irot <= prog->player.rot++) {
		int	getd = getdistance()
	}
} */

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
	while (1)
	{
		for (int i = -width / 2; i <= width / 2; i++)
		{
			if (dx > dy)
				ft_pixelput(data, p1.x, p1.y + i, color);
			else
				ft_pixelput(data, p1.x + i, p1.y, color);
		}
		if (p1.x == p2.x && p1.y == p2.y)
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

t_point	getvdistance(t_prog *prog, double rot)
{
	double	tmp;
	int		i;
	int		x;

	if (rot < 180 && rot > 0)
	{
		tmp = - (prog->player.y - ((prog->player.y >> 6) << 6)) / tan(degtorad((double) rot));
		//printf("v %d %d, %d %d\n", ((prog->player.x + (int) tmp)) >> 6, (prog->player.y >> 6) - 1, (prog->player.x + (int) tmp), (prog->player.y >> 6) << 6);
		if ((prog->player.y >> 6) - 1 >= 0 && ((prog->player.x + (int) tmp)) >> 6 >= 0 && (prog->map.data[(prog->player.y >> 6) - 1][((prog->player.x + (int) tmp)) >> 6] == '1' ||
			(prog->map.data[(prog->player.y >> 6) - 1][((prog->player.x + (int) tmp + 1)) >> 6] == '1' && !((prog->player.x + (int) tmp) % 64)) || (prog->map.data[(prog->player.y >> 6) - 1][((prog->player.x + (int) tmp - 1)) >> 6] == '1' && !((prog->player.x + (int) tmp) % 64))))
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
		//printf("v %d %d, %d %d\n", ((prog->player.x + (int) tmp)) >> 6, (prog->player.y >> 6) + 1, (prog->player.x + (int) tmp), (prog->player.y >> 6) << 6);
		if ((prog->player.y >> 6) + 1 >= 0 && ((prog->player.x + (int) tmp)) >> 6 >= 0 && (prog->map.data[(prog->player.y >> 6) + 1][((prog->player.x + (int) tmp)) >> 6] == '1' ||
			(prog->map.data[(prog->player.y >> 6) + 1][((prog->player.x + (int) tmp + 1)) >> 6] == '1' && !((prog->player.x + (int) tmp) % 64)) || (prog->map.data[(prog->player.y >> 6) + 1][((prog->player.x + (int) tmp - 1)) >> 6] == '1' && !((prog->player.x + (int) tmp) % 64))))
			return ((t_point) {(prog->player.x + tmp), ((prog->player.y >> 6) + 1) << 6});
		i = (prog->player.y >> 6) + 2;
		x = prog->player.x + tmp + (64 / tan(degtorad((double) rot)));
		tmp = + (64 / tan(degtorad((double) rot)));
		while (i < prog->map.height) {
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
		//printf("h %d %d, %d %d\n", (prog->player.x >> 6) - 1, (prog->player.y + (int) tmp) >> 6, (prog->player.x >> 6) << 6, (prog->player.y + (int) tmp));
		if ((prog->player.x >> 6) - 1 >= 0 && (prog->player.x >> 6) - 1 < prog->map.width && ((prog->player.y + (int) tmp)) >> 6 >= 0 && ((prog->player.y + (int) tmp)) >> 6 < prog->map.height && (prog->map.data[(prog->player.y + (int) tmp) >> 6][(prog->player.x >> 6) - 1] == '1' ||
			(prog->map.data[(prog->player.y + (int) tmp + 1) >> 6][(prog->player.x >> 6) - 1] == '1' && !((prog->player.y + (int) tmp) % 64)) || (prog->map.data[(prog->player.y + (int) tmp - 1) >> 6][(prog->player.x >> 6) - 1] == '1' && !((prog->player.y + (int) tmp) % 64))))
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
		//printf("h %d %d, %d %d\n", (prog->player.x >> 6) + 1, (prog->player.y + (int) tmp) >> 6, (prog->player.x >> 6) << 6, (prog->player.y + (int) tmp));
		if ((prog->player.x >> 6) + 1 >= 0 && (prog->player.x >> 6) + 1 < prog->map.width && ((prog->player.y + (int) tmp)) >> 6 >= 0 && ((prog->player.y + (int) tmp)) >> 6 < prog->map.height && (prog->map.data[(prog->player.y + (int) tmp) >> 6][(prog->player.x >> 6) + 1] == '1' ||
			(prog->map.data[(prog->player.y + (int) tmp + 1) >> 6][(prog->player.x >> 6) + 1] == '1' && !((prog->player.y + (int) tmp) % 64)) || (prog->map.data[(prog->player.y + (int) tmp - 1) >> 6][(prog->player.x >> 6) + 1] == '1' && !((prog->player.y + (int) tmp) % 64))))
			return ((t_point) {((prog->player.x >> 6) + 1) << 6, (prog->player.y + tmp)});
		i = (prog->player.x >> 6) + 2;
		y = prog->player.y + tmp + (64 * tan(degtorad((double) rot)));
		tmp = + (64 * tan(degtorad((double) rot)));
		while (i < prog->map.width) {
			if (y >> 6 >= 0 && y >> 6 < prog->map.height && prog->map.data[y >> 6][i] == '1')
				return ((t_point) {(i) << 6, y});
			i++;
			y += tmp;
		}
	}
	return ((t_point) {-1, -1});
}


int	getdistance(t_prog *prog, t_ray *ray/* , t_data *img */)
{
	t_point	vpoint;
	t_point	hpoint;
	unsigned int		vdis;
	unsigned int		hdis;

	vpoint = getvdistance(prog, ray->rot);
	hpoint = gethdistance(prog, ray->rot);

	vdis = pow(prog->player.x - vpoint.x, 2) + pow(prog->player.y - vpoint.y, 2);
	hdis = pow(prog->player.x - hpoint.x, 2) + pow(prog->player.y - hpoint.y, 2);

	if (vpoint.x != -1 && vpoint.y != -1 && (vdis <= hdis || (hpoint.x == -1 && hpoint.y == -1)))
	{
		//ft_putline(img, (t_point) {prog->player.x, prog->player.y}, vpoint, itoargb(255, 230, 0, 0), 1);
		ray->point = vpoint;
		ray->side = 0;
		return (vdis);
	}
	else if (hpoint.x != -1 && hpoint.y != -1 && (vdis > hdis || (vpoint.x == -1 && vpoint.y == -1)))
	{
		//ft_putline(img, (t_point) {prog->player.x, prog->player.y}, hpoint, itoargb(255, 230, 0, 0), 1);
		ray->point = hpoint;
		ray->side = 1;
		return (hdis);
	}
	return (-1);
}

int	getpixelcolor(t_data *data, int	x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

int	displayray(t_prog *prog, t_data *img, t_ray *ray)
{
	int		y;
	int		x;
	float	slheight;

	x = ray->screen_x - (1280 / 240) - 1;
	slheight = ray->lheight;
	if (ray->lheight > 720)
		ray->lheight = 720;
	if (ray->screen_x == 0)
		printf("%f\n", ray->rot);
	while (x <= ray->screen_x + (1280 / 240))
	{
		y = 360 - ((int) ray->lheight / 2);
		while (x >= 0 && x < 1280 && y <= 360 + ((int) ray->lheight / 2))
		{
			if (ray->side == 1 && ray->rot > 90 && ray->rot < 270)
				ft_pixelput(img, x, y, getpixelcolor(&prog->map.EA, (int) (((float) ((ray->point.y - ((ray->point.y >> 6) << 6))) / 64.f) * 256),  (int) ((float) ((float) (y - (360 - ((int) ray->lheight / 2)) + ((slheight - ray->lheight) / 2)) / (float) slheight) * 256.f)));
			else if (ray->side == 1 && (ray->rot < 90 || ray->rot > 270))
				ft_pixelput(img, x, y, getpixelcolor(&prog->map.WE, (int) (((float) ((ray->point.y - ((ray->point.y >> 6) << 6))) / 64.f) * 256),  (int) ((float) ((float) (y - (360 - ((int) ray->lheight / 2)) + ((slheight - ray->lheight) / 2)) / (float) slheight) * 256.f)));
			else if (ray->side == 0 && ray->rot < 180)
				ft_pixelput(img, x, y, getpixelcolor(&prog->map.NO, (int) (((float) ((ray->point.x - ((ray->point.x >> 6) << 6))) / 64.f) * 256),  (int) ((float) ((float) (y - (360 - ((int) ray->lheight / 2)) + ((slheight - ray->lheight) / 2)) / (float) slheight) * 256.f)));
			else if (ray->side == 0 && ray->rot > 180)
				ft_pixelput(img, x, y, getpixelcolor(&prog->map.SO, (int) (((float) ((ray->point.x - ((ray->point.x >> 6) << 6))) / 64.f) * 256),  (int) ((float) ((float) (y - (360 - ((int) ray->lheight / 2)) + ((slheight - ray->lheight) / 2)) / (float) slheight) * 256.f)));
			else
				ft_pixelput(img, x, y, itoargb(255, 0, 230, 0));
			y++;
		}
		x++;
	}
	return (1);
}

int	raycast(t_prog *prog, t_data *img)
{
	t_ray	ray;
	float	rot;

	rot = prog->player.rot - 30;
		//getdistance(prog, irot, img);
	/* if (rot == prog->player.rot - 30)
		printf("%f %i\n", rot, prog->player.rot + 30); */
	printf("rot: %f\n", rot);
	while (rot <= (float) (prog->player.rot + 30)) {
		ray.rot = rot;
		if (ray.rot > 359.0)
			ray.rot -= 360.0;
		else if (ray.rot < 0.0)
			ray.rot += 360.0;
		printf("%f\n", ray.rot);
		ray.dist = getdistance(prog, &ray);
		ray.lheight = 720 / ((sqrt(ray.dist) / 64) * cos(degtorad(ray.rot - (float) prog->player.rot)));
		ray.screen_x = ((float) ((rot - (float) prog->player.rot) + 30.0) / 60) * 1280;
		/* if (rot == prog->player.rot - 30)
			printf("%f\n", ray.rot); */
		displayray(prog, img, &ray);
		rot += 0.5;
	}
	return (1);
}


void	display2D(t_prog *prog, t_data *img) {
	for (int x = 0; x < 1280; x++) {
		for (int y = 0; y < 720; y++) {
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
	ft_putline(img, (t_point) {prog->player.x, prog->player.y},
		getpointercoords(prog), itoargb(255, 230, 230, 0), 1);
}

int	loop(t_prog	*prog)
{
	t_data	img;

	img.img = mlx_new_image(prog->mlx, 1280, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.end);
	//display2D(prog, &img);
	//displayplayer2D(prog, &img);
	raycast(prog, &img);
	/* for (float i = prog->player.rot - 30; i <= prog->player.rot + 30; i += 0.5)
	{
		int	tmp = getdistance(prog, i, &img);
		printf("%f: %d\n", i, tmp);
		if (tmp == -1)
			printf("Error at angle: %f\n", i);
	} */
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
	if (key == 65363)
	{
		prog->player.rot += 1;
		if (prog->player.rot > 359)
			prog->player.rot -= 360;
	}
	else if (key == 65361)
	{
		prog->player.rot -= 1;
		if (prog->player.rot < 0)
			prog->player.rot += 360;
	}
	else if (key == 119)
	{
		prog->player.exactx -= cos(degtorad((double) prog->player.rot)) * 3;
		prog->player.exacty -= sin(degtorad((double) prog->player.rot)) * 3;
	}
	prog->player.x = prog->player.exactx;
	prog->player.y = prog->player.exacty;
	return (1);
}

void	openimages(t_prog *prog){
	int	w;
	int	h;
	prog->map.NO.img = mlx_xpm_file_to_image(prog->mlx, "./NO.xpm", &w, &h);
	prog->map.NO.addr = mlx_get_data_addr(prog->map.NO.img, &prog->map.NO.bpp, &prog->map.NO.ll, &prog->map.NO.end);
	prog->map.SO.img = mlx_xpm_file_to_image(prog->mlx, "./SO.xpm", &w, &h);
	prog->map.SO.addr = mlx_get_data_addr(prog->map.SO.img, &prog->map.SO.bpp, &prog->map.SO.ll, &prog->map.SO.end);
	prog->map.EA.img = mlx_xpm_file_to_image(prog->mlx, "./EA.xpm", &w, &h);
	prog->map.EA.addr = mlx_get_data_addr(prog->map.EA.img, &prog->map.EA.bpp, &prog->map.EA.ll, &prog->map.EA.end);
	prog->map.WE.img = mlx_xpm_file_to_image(prog->mlx, "./WE.xpm", &w, &h);
	prog->map.WE.addr = mlx_get_data_addr(prog->map.WE.img, &prog->map.WE.bpp, &prog->map.WE.ll, &prog->map.WE.end);
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
	openimages(&prog);
	getplayer(&prog);
	prog.player.rot = 45;
	prog.player.exactx = prog.player.x;
	prog.player.exacty = prog.player.y;
	mlx_hook(prog.win, 2, 1L << 0, keypress, &prog);
	mlx_loop_hook(prog.mlx, loop, &prog);
	mlx_loop(prog.mlx);
}
