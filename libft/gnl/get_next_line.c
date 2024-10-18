/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:12:25 by fghysbre          #+#    #+#             */
/*   Updated: 2023/12/05 14:23:27 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc((strln(s1, 0) + strln(s2, 1) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i] && ++j != -1)
		res[j] = s1[i];
	i = -1;
	while (s2[++i] && ++j != -1)
	{
		res[j] = s2[i];
		if (s2[i] == '\n')
			break ;
	}
	res[++j] = '\0';
	return (res);
}

char	*nlchr(const char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\n')
			return ((char *)s + i);
	}
	if (s[i] == '\n')
		return ((char *)s + i);
	return ((void *)0);
}

char	*buffer_handler(char *res, char *buffer, char **save, ssize_t buflen)
{
	char	*temp;

	buffer[buflen] = '\0';
	if (*save)
	{
		if (res)
			free(res);
		res = ft_strjoin(*save, "\0");
		free(*save);
		*save = NULL;
	}
	if (!res)
		temp = ft_strjoin("\0", buffer);
	else
		temp = ft_strjoin(res, buffer);
	if (res)
		free(res);
	res = temp;
	return (res);
}

char	*get_next_liner(int fd, char *buffer, char **save)
{
	char		*res;
	ssize_t		buflen;

	res = NULL;
	if (*save && nlchr(*save))
	{
		res = ft_strjoin("", *save);
		*save = save_handlerer(*save);
		if (!res || !save)
			return (freem(&res, save));
		return (res);
	}
	buflen = read(fd, buffer, BUFFER_SIZE);
	while (buflen > 0 || *save)
	{
		res = buffer_handler(res, buffer, save, buflen);
		if (!res)
			return (NULL);
		*save = save_handler(buffer);
		if (nlchr(buffer))
			break ;
		buflen = read(fd, buffer, BUFFER_SIZE);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	char		*res;
	char		*buffer;
	static char	*save = NULL;

	if (read(fd, 0, 0) < 0)
		return (special_case_handler(&save), NULL);
	if (fd < 0 || BUFFER_SIZE < 1 || fd >= 2147483647)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		if (save)
		{
			free(save);
			save = NULL;
		}
		return (NULL);
	}
	res = get_next_liner(fd, buffer, &save);
	free(buffer);
	return (res);
}
/* 
#include <fcntl.h> //rem this
#include <stdio.h> //rem this
#include <stdlib.h> //rem this


int	main(void)
{
	int		fd;
	char	*res;

	fd = open("files/mult_nlx5.txt", O_RDWR);
	res = get_next_line(fd);
	while (res)
	{
		printf("%s", res);
		free(res);
		res = get_next_line(fd);
	}
	printf("%s", res);
	free(res);
	// system("leaks a.out");
	return (0);
}
 */