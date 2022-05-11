#ifndef CUB3D_H
#define CUB3D_H

#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../srcs/minilibx/mlx.h"

int				get_next_line(int fd, char **line);
int		find_n(char *buf, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlen(char *str);
char	*join_a_free(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);


typedef struct  s_player {
    float x;
    float y;
    float teta;
    int move_right;
    int move_left;
    int move_up;
    int move_down;
    int camera_left;
    int camera_right;
    char *image;
    char **map;
    void *mlx_ptr;
    void *mlx_win;
    void *img_ptr;
    float w;
    float h;
}       t_player;

#endif