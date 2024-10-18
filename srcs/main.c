/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/18 23:53:50 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

int	main(void) {
	t_prog	prog;

	prog.mlx = mlx_init();
	prog.win = mlx_new_window(prog.mlx, 1280, 720, "Hello World!");
	if (!prog.win)
		return (1);
	mlx_loop(prog.mlx);
}