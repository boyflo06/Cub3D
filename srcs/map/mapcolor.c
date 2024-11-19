/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcolor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:23:19 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/18 15:26:31 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

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
