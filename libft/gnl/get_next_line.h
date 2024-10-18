/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:11:34 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/18 23:50:13 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "stdlib.h"
# include "unistd.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t	strln(const char *s, int isbuf);
char	*ft_strjoin(char *s1, char *s2);
char	*nlchr(const char *s);
char	*buffer_handler(char *res, char *buffer, char **save, ssize_t buflen);
char	*save_handler(char *buffer);
char	*save_handlerer(char *save);
void	special_case_handler(char **save);
void	*freem(char **s1, char **s2);

#endif