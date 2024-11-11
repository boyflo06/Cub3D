/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/08 16:34:23 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int argc, char **argv) {
	t_prog	prog;

	if (argc != 2)
		return (write(2, "Cub3D: Wrong number of args (1 needed)\n", 39) - 38);
	if (!initprog(&prog, argv[1]))
		return (write(2, "Cub3D: Fatal error while initialising\n", 38) - 37);
	mlx_mouse_hide(prog.mlx, prog.win);
	mlx_hook(prog.win, 2, 1L << 0, keypress, &prog);
	mlx_hook(prog.win, 3, 1L << 1, keyrelease, &prog);
	mlx_loop_hook(prog.mlx, loop, &prog);
	mlx_loop(prog.mlx);
}