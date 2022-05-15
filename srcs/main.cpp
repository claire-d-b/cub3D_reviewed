#include "cub3d.hpp"
#include "fixed.hpp"
#include "./minilibx/mlx.h"
// #include <GL/glut.h>

// int main (int ac, char **av)
// {
//     (void)ac;
//     (void)av;
//     char *line;
//     int fd = 0;
//     int i = 0;
//     int x = 0;
//     t_player player;

//     init_struct_player(&player);
//     if (!(fd = open("map.cub", O_RDONLY)))
//         return 1;
//     if (!(player.map = (char **)malloc(sizeof(char*) * 255)))   
//         return 1;
//     while ((i = get_next_line(fd, &line)))
//     {
//         player.map[x] = strdup(line);
//         printf("%s\n", line);
//         x++;
//     }
//     player.map[x] = strdup(line);
//     player.map[++x] = NULL;
//     const char *title = "CUB";
//     int bpp = 0;
//     int size_line = 0;
//     int endian = 0;
//     // glutInit(&ac, av);
//     // glutInitWindowSize(WIDTH, HEIGHT);
//     // glutCreateWindow("CUB3D");
//     // player_img = glClear(GL_COLOR_BUFFER_BIT);
//     if (!(player.mlx_ptr = mlx_init()))
//         return 1;
//     if (!(player.mlx_win = mlx_new_window(player.mlx_ptr, WIDTH, HEIGHT, const_cast<char *>(title))))
//         return 1;
//     if (!(player.img_ptr = mlx_new_image(player.mlx_ptr, WIDTH, HEIGHT)))
//         return 1;
//     if (!(player.image = mlx_get_data_addr(player.img_ptr, &bpp, &size_line, &endian)))
//         return 1;
//     // draw_walls(player.image, 0, 0, player.map, &player);
//     // mlx_put_image_to_window(mlx_ptr, mlx_win, img_ptr, 0, 0);
//     mlx_hook(player.mlx_win, 02, 1L << 0, (int (*)())(key_press), &player);
// 	mlx_hook(player.mlx_win, 03, 1L << 1, (int (*)())(key_release), &player);
// 	// mlx_hook(player.ids.mlx_win, 15, 1L << 16, &minimise, player);
// 	// mlx_hook(player.ids.mlx_win, 17, 1L << 17, &exit_game, player);
//     mlx_loop_hook(player.mlx_ptr, (int (*)())(moves), &player);
//     mlx_loop(player.mlx_ptr);
//     // draw_walls(player.image, 0, 0, player.map, &player);
//     return 0;
// }

int main (int ac, char **av)
{
    (void)ac;
    (void)av;
    char *line;
    int fd = 0;
    int i = 0;
    int x = 0;
    t_player player;

    init_struct_player(&player);
    if (!(fd = open("map.cub", O_RDONLY)))
        return 1;
    if (!(player.map = new char*[255]))
        return 1;
    while ((i = get_next_line(fd, &line)))
    {
        player.map[x] = strdup(line);
        printf("%s\n", line);
        x++;
    }
    player.map[x] = strdup(line);
    player.map[++x] = NULL;
    const char *title = "CUB";
    int bpp = 0;
    int size_line = 0;
    int endian = 0;
    // glutInit(&ac, av);
    // glutInitWindowSize(WIDTH, HEIGHT);
    // glutCreateWindow("CUB3D");
    // player_img = glClear(GL_COLOR_BUFFER_BIT);
    if (!(player.mlx_ptr = mlx_init()))
        return 1;
    if (!(player.mlx_win = mlx_new_window(player.mlx_ptr, WIDTH, HEIGHT, const_cast<char *>(title))))
        return 1;
    if (!(player.img_ptr = mlx_new_image(player.mlx_ptr, WIDTH, HEIGHT)))
        return 1;
    if (!(player.image = mlx_get_data_addr(player.img_ptr, &bpp, &size_line, &endian)))
        return 1;
    // draw_walls(player.image, 0, 0, player.map, &player);
    // mlx_put_image_to_window(mlx_ptr, mlx_win, img_ptr, 0, 0);
    mlx_hook(player.mlx_win, 02, 1L << 0, (int (*)())(&key_press), &player);
	mlx_hook(player.mlx_win, 03, 1L << 1, (int (*)())(&key_release), &player);
	// mlx_hook(player.ids.mlx_win, 15, 1L << 16, &minimise, player);
	// mlx_hook(player.ids.mlx_win, 17, 1L << 17, &exit_game, player);
    mlx_loop_hook(player.mlx_ptr, (int (*)())(&moves), &player);
    mlx_loop(player.mlx_ptr);
    // draw_walls(player.image, 0, 0, player.map, &player);
    return 0;
}