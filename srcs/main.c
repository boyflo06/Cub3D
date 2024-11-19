/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/19 13:01:55 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	itoargb(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
{
	return ((((int)255 - (int)a) << 24) | ((int)r << 16) | ((int)g << 8) | b);
}

char	**ft_strarrpush(char **arr, char *newstr)
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

void	openimages(t_prog *prog){
	prog->map.NO.img = mlx_xpm_file_to_image(prog->mlx, prog->map.NO_src, &prog->map.NO.w, &prog->map.NO.h);
	prog->map.NO.addr = mlx_get_data_addr(prog->map.NO.img, &prog->map.NO.bpp, &prog->map.NO.ll, &prog->map.NO.end);
	prog->map.SO.img = mlx_xpm_file_to_image(prog->mlx, prog->map.SO_src, &prog->map.SO.w, &prog->map.SO.h);
	prog->map.SO.addr = mlx_get_data_addr(prog->map.SO.img, &prog->map.SO.bpp, &prog->map.SO.ll, &prog->map.SO.end);
	prog->map.EA.img = mlx_xpm_file_to_image(prog->mlx, prog->map.EA_src, &prog->map.EA.w, &prog->map.EA.h);
	prog->map.EA.addr = mlx_get_data_addr(prog->map.EA.img, &prog->map.EA.bpp, &prog->map.EA.ll, &prog->map.EA.end);
	prog->map.WE.img = mlx_xpm_file_to_image(prog->mlx, prog->map.WE_src, &prog->map.WE.w, &prog->map.WE.h);
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
