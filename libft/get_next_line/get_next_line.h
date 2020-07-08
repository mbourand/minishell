#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

int			get_next_line(int fd, char **line);
size_t		gnllenuntil(const char *s, char c);
char		*gnldupuntil(const char *s1, char c);
char		*gnljoinuntil(char *s1, char const *s2, char c);

#endif