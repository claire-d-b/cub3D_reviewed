#ifndef CUB3D_H
#define CUB3D_H

#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

# define HEIGHT 800.0f
# define WIDTH 1000.0f
# define FOV 1.0471975512f
# define ROTATION 0.05f
# define MOVE_RIGHT 100
# define MOVE_LEFT 97
# define MOVE_UP 119
# define MOVE_DOWN 115
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define PI 3.14159265358979323846f

int				get_next_line(int fd, char **line);
int		find_n(char *buf, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlen(char *str);
char	*join_a_free(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);

#endif