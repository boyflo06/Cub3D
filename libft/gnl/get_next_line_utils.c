/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:12:28 by fghysbre          #+#    #+#             */
/*   Updated: 2023/12/05 14:22:52 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save_handler(char	*buffer)
{
	char	*save;

	save = NULL;
	if (nlchr(buffer))
		save = ft_strjoin(nlchr(buffer) + 1, "");
	if (!save)
		return (NULL);
	if (!save[0])
	{
		free(save);
		return (NULL);
	}
	return (save);
}

size_t	strln(const char *s, int isbuf)
{
	size_t	c;

	c = 0;
	while (s[c])
	{
		if (s[c] == '\n' && isbuf)
		{
			c++;
			break ;
		}
		c++;
	}
	return (c);
}

char	*save_handlerer(char *save)
{
	char	*temp;

	temp = ft_strjoin(nlchr(save) + 1, "");
	free(save);
	if (!(temp))
		return (NULL);
	if (!temp[0])
	{
		free(temp);
		return (NULL);
	}
	return (temp);
}

void	special_case_handler(char **save)
{
	if (*save)
	{
		free(*save);
		*save = NULL;
	}
}

void	*freem(char **s1, char **s2)
{
	if ((*s1))
	{
		free(*s1);
		*s1 = NULL;
	}
	if ((*s2))
	{
		free(*s2);
		*s2 = NULL;
	}
	return (NULL);
}
