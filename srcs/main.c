/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/23 16:13:09 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int argc, char **argv)
{
	t_prog	prog;

	if (argc != 2)
		return (write(2, "Error\nCub3D: Wrong number of args\n", 34) - 33);
	if (initprog(&prog, argv[1]) < 1)
		return (1);
	prog.img.img = mlx_new_image(prog.mlx, WIN_W, WIN_H);
	if (!prog.img.img)
		return (free_prog(&prog), 1);
	prog.img.addr = mlx_get_data_addr(prog.img.img, &prog.img.bpp,
			&prog.img.ll, &prog.img.end);
	mlx_mouse_hide(prog.mlx, prog.win);
	mlx_hook(prog.win, 2, 1L << 0, keypress, &prog);
	mlx_hook(prog.win, 3, 1L << 1, keyrelease, &prog);
	mlx_hook(prog.win, 17, 1L << 0, destroy, &prog);
	mlx_loop_hook(prog.mlx, loop, &prog);
	mlx_do_key_autorepeatoff(prog.mlx);
	mlx_loop(prog.mlx);
}
