/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:15:16 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/31 17:15:16 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int			get_next_line(int fd, char **line);
size_t		gnllenuntil(const char *s, char c);
char		*gnldupuntil(const char *s1, char c);
char		*gnljoinuntil(char *s1, char const *s2, char c);

#endif
