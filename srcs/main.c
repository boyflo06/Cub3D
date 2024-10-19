/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/20 00:37:23 by fghysbre         ###   ########.fr       */
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

double	degtorad(double deg) {
	return (deg * (PI/180));
}

int	getvdistance(t_prog *prog, int rot) {
	double	tmp;
	if (rot < 180)
	{
		tmp = (prog->player.y - ((prog->player.y >> 6) << 6)) / tan(degtorad((double) rot));
		if (prog->map.data[(prog->player.y >> 6) - 1][((prog->player.x + (int) tmp) >> 6)])
			return ();
	}
}

int	gethdistance(t_prog *prog, int rot) {
	
}

int	getdistance(t_prog *prog, int rot) {
	int	vdis;
	int	hdis;
	if (rot > 360)
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
	for (int i = 0; prog.map.data[i]; i++)
		printf("%s\n", prog.map.data[i]);
	prog.player.x = 288;
	prog.player.y = 224;
	prog.player.rot = 0;
	raycast()
	mlx_loop(prog.mlx);
}