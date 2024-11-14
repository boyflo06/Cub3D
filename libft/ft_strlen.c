/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:45:59 by fghysbre          #+#    #+#             */
/*   Updated: 2024/11/14 23:28:41 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	if (!s)
		return (0);
	while (s[c])
		c++;
	return (c);
}

// Test Main

/*
#include <string.h>

int	main(void)
{
	printf("Length of 'segmentation fault' : %d (%d) \n",
		ft_strlen("segmentation fault"), strlen("segmentation fault"));
	printf("Length of '' : %d (%d) \n",
		ft_strlen(""), strlen(""));
	char str[] = {'f', 'o', 'o'};
	printf("Length of non null terminated str : %d (%d) \n",
		ft_strlen(str), strlen(str));
}
*/