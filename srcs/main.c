/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/13 19:50:23 by mleonet          ###   ########.fr       */
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

void	assign_values_file(t_prog *prog, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		prog->map.NO_src = ft_strdup(line + 2);
	else if (ft_strncmp(line, "SO", 2) == 0)
		prog->map.SO_src = ft_strdup(line + 2);
	else if (ft_strncmp(line, "WE", 2) == 0)
		prog->map.WE_src = ft_strdup(line + 2);
	else if (ft_strncmp(line, "EA", 2) == 0)
		prog->map.EA_src = ft_strdup(line + 2);
	else if (ft_strncmp(line, "F", 1) == 0)
		prog->map.F = assign_rgb(line + 1);
	else if (ft_strncmp(line, "C", 1) == 0)
		prog->map.C = assign_rgb(line + 1);
}

int	check_file_content(t_prog *prog)
{
	if (!prog->map.NO_src || !prog->map.SO_src || !prog->map.WE_src
		|| !prog->map.EA_src || !prog->map.F || !prog->map.C)
	{
		free_prog(prog);
		return (0);
	}
	prog->map.NO_src = rem_spaces(prog->map.NO_src);
	prog->map.SO_src = rem_spaces(prog->map.SO_src);
	prog->map.WE_src = rem_spaces(prog->map.WE_src);
	prog->map.EA_src = rem_spaces(prog->map.EA_src);
	return (1);
}

int	check_file_format(t_prog *prog, char *path)
{
	int		fd;
	char	*line;

	if (check_file_name(path) == 0)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		assign_values_file(prog, line);
		free(line);
		line = get_next_line(fd);
	}
	if (!check_file_content(prog))
		return (0);
	return (1);
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

float	dist(float ax, float ay, float bx, float by) {
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
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

	x = (ray->screen_x - (WIN_W / 480)) - 1;
	slheight = ray->lheight;
	if (ray->lheight > WIN_H)
		ray->lheight = WIN_H;
	//printf("%f: %f\n",ray->rot, ray->dist);
	while (x <= ray->screen_x + (WIN_W / 480))
	{
		y = (WIN_H / 2) - ((int) ray->lheight / 2);
		while (x >= 0 && x < WIN_W && y <= (WIN_H / 2) + ((int) ray->lheight / 2))
		{
			if (ray->side == 1 && ray->rot > PI / 2 && ray->rot < 3 * PI / 2)
				ft_pixelput(img, x, y, getpixelcolor(&prog->map.EA, (int) (((float) (fmod(ray->point.y, 64) * prog->map.EA.w) / 64.f)),  (int) ((float) ((float) (y - ((WIN_H / 2) - ((int) ray->lheight / 2)) + ((slheight - ray->lheight) / 2)) / (float) slheight) * prog->map.EA.h)));
			else if (ray->side == 1 && (ray->rot < PI / 2 || ray->rot > 3 * PI / 2))
				ft_pixelput(img, x, y, getpixelcolor(&prog->map.WE, (int) (((float) (fmod(ray->point.y, 64) * prog->map.WE.w) / 64.f)),  (int) ((float) ((float) (y - ((WIN_H / 2) - ((int) ray->lheight / 2)) + ((slheight - ray->lheight) / 2)) / (float) slheight) * prog->map.WE.h)));
			else if (ray->side == 0 && ray->rot < PI)
				ft_pixelput(img, x, y, getpixelcolor(&prog->map.NO, (int) (((float) (fmod(ray->point.x, 64) * prog->map.NO.w) / 64.f)),  (int) ((float) ((float) (y - ((WIN_H / 2) - ( ray->lheight / 2.0)) + ((slheight - ray->lheight) / 2.0)) / (float) slheight) * prog->map.NO.h)));
			else if (ray->side == 0 && ray->rot > PI)
				ft_pixelput(img, x, y, getpixelcolor(&prog->map.SO, (int) (((float) (fmod(ray->point.x, 64) * prog->map.SO.w) / 64.f)),  (int) ((float) ((float) (y - ((WIN_H / 2) - ((int) ray->lheight / 2)) + ((slheight - ray->lheight) / 2)) / (float) slheight) * prog->map.SO.h)));
			// else
			// 	ft_pixelput(img, x, y, itoargb(255, 0, 230, 0));
			y++;
		}
		x++;
	}
	return (1);
}

t_ray	errorray()
{
	t_ray	res;
	
	res.dist = 1000000;
	return (res);
}

void	setvarsh(t_prog *prog, double ra, t_ray *ray, t_point *off)
{
	float aTan;
	
	aTan = -1/tan(ra);
	ray->dist = 1000000;
	ray->point.x = prog->player.x;
	ray->point.y = prog->player.y;
	ray->side = 0;
	if (ra > PI) {
		ray->point.y = (((int) prog->player.y >> 6) << 6) - 0.0001;
		ray->point.x = (prog->player.y - ray->point.y) * aTan + prog->player.x;
		off->y = -64;
		off->x = -off->y * aTan;
	} if (ra < PI) {
		ray->point.y = (((int) prog->player.y >> 6) << 6) + 64;
		ray->point.x = (prog->player.y - ray->point.y) * aTan + prog->player.x;
		off->y = 64;
		off->x = -off->y * aTan;
	} 
}

t_ray	raycasth(t_prog *prog, double ra)
{
	t_ray	res;
	t_point	off;
	int		mx;
	int		my;

	setvarsh(prog, ra, &res, &off);
	if (ra == 0 || ra == PI)
		return (errorray());
	while (1) {
		mx = (int) res.point.x >> 6; my = (int) res.point.y >> 6;
		if ((mx < 0 || mx >= prog->map.width || my < 0 || my >= prog->map.height))
			break ;
		if (prog->map.data[my][mx] == '1') {
			res.dist = dist(prog->player.x, prog->player.y, res.point.x, res.point.y);
			return (res);
		} else {
			res.point.x += off.x; res.point.y += off.y;
		}
	}
	return (errorray());
}

void	setvarsv(t_prog *prog, double ra, t_ray *ray, t_point *off)
{
	float nTan;
	
	nTan = -tan(ra);
	ray->dist = 1000000;
	ray->point.x = prog->player.x;
	ray->point.y = prog->player.y;
	ray->side = 1;
	if (ra > PI / 2 && ra < 3 * PI / 2) {
		ray->point.x = (((int) prog->player.x >> 6) << 6) - 0.0001;
		ray->point.y = (prog->player.x - ray->point.x) * nTan + prog->player.y;
		off->x = -64;
		off->y = -off->x * nTan;
	} if (ra < PI / 2 || ra > 3 * PI / 2) {
		ray->point.x = (((int) prog->player.x >> 6) << 6) + 64;
		ray->point.y = (prog->player.x - ray->point.x) * nTan + prog->player.y;
		off->x = 64;
		off->y = -off->x * nTan;
	}
}

t_ray	raycastv(t_prog *prog, double ra)
{
	t_ray	res;
	t_point	off;
	int		mx;
	int		my;

	setvarsv(prog, ra, &res, &off);
	if (ra == PI / 2 || ra == 3 * PI / 2)
		return (errorray());
	while (1) {
		mx = (int) res.point.x >> 6; my = (int) res.point.y >> 6;
		if ((mx < 0 || mx >= prog->map.width || my < 0 || my >= prog->map.height))
			break ;
		if (prog->map.data[my][mx] == '1') {
			res.dist = dist(prog->player.x, prog->player.y, res.point.x, res.point.y);
			return (res);
		}
		else {
			res.point.x += off.x; res.point.y += off.y;
		}
	}
	return (errorray());
}

void	raycpy(t_ray *dst, t_ray *src)
{
	dst->point.x = src->point.x;
	dst->point.y = src->point.y;
	dst->dist = src->dist;
	dst->side = src->dist;
}

void	raycast(t_prog *prog, t_data *img) {
	int		r;
	double	ra;
	t_ray	rayv;
	t_ray	rayh;
	
	ra = degtorad(prog->player.rot) - (DEG * 30);
	if (ra < 0) 
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	for (r = 0; r < 240; r++) {
		rayh = raycasth(prog, ra);
		rayv = raycastv(prog, ra);
		
		if (rayh.dist < rayv.dist) {rayv = rayh;}
		float	ca = degtorad(prog->player.rot) - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		rayv.dist = rayv.dist * cos(ca);
		rayv.lheight = (64 * WIN_H) / rayv.dist;
		rayv.screen_x = r * 5.333333333;
		rayv.rot = ra;
		displayray(prog, img, &rayv);

		ra += DEG / 4;
		if (ra < 0) 
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
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
		prog->player.rot += 1;
	if ((prog->keys >> 4) % 2)
		prog->player.rot -= 1;
	if (prog->player.rot > 359)
		prog->player.rot -= 360;
	if (prog->player.rot < 0)
		prog->player.rot += 360;
	dx = cos(degtorad(prog->player.rot)) * 2.5;
	dy = sin(degtorad(prog->player.rot)) * 2.5;
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
	t_data	img;

	img.img = mlx_new_image(prog->mlx, WIN_W, WIN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.end);
	if (prog->keys & KEY_TOGMOUSE)
		updatemouse(prog);
	updateplayer(prog);
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
	printf("%d\n", prog->keys);
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
	else if (key == 'v' && !(prog->keys & KEY_TOGMOUSE))
		prog->keys = prog->keys | KEY_TOGMOUSE;
	else if (key == 'v' && (prog->keys & KEY_TOGMOUSE))
		prog->keys = prog->keys & ~(KEY_TOGMOUSE);
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
		return (write(2, "Cub3D: Wrong number of args (1 needed)\n", 39) - 38);
	if (!check_file_format(&prog, argv[1]))
		return (write(2, "Cub3D: Wrong file format\n", 26) - 25);
	prog.mlx = mlx_init();
	prog.win = mlx_new_window(prog.mlx, WIN_W, WIN_H, "Hello World!");
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
	prog.player.ix = (int) prog.player.x;
	prog.player.iy = (int) prog.player.y;
	prog.player.rot = 270;
	prog.keys = 0;
	mlx_mouse_hide(prog.mlx, prog.win);
	mlx_hook(prog.win, 2, 1L << 0, keypress, &prog);
	mlx_hook(prog.win, 3, 1L << 1, keyrelease, &prog);
	mlx_loop_hook(prog.mlx, loop, &prog);
	mlx_loop(prog.mlx);
}
