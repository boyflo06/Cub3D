/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:52:38 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/24 17:23:48 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cube.h"

int		assign_rgb(char *str);
char	*assign_file(char *str);
int		assign_textures(t_prog *prog, char *line);
int		assign_values_file(t_prog *prog, char *line);
int		check_textures_format(char *str);

#endif