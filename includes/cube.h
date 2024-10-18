/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:56:16 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/18 23:52:44 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "fcntl.h"

typedef	struct s_map
{
	char	**map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F;
	int		C;
}	t_map;

typedef struct s_prog
{
	void	*mlx;
	void	*win;
	t_map	map;
}	t_prog;
