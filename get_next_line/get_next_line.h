#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

#include <unistd.h>
#include <stdlib.h>

int		get_next_line(char **line);

#endif
