#include "cub3d.h"

#define HEIGHT 800.0f
#define WIDTH 1000.0f
#define FOV 1.0471975512f
#define ROTATION 0.05f
# define MOVE_RIGHT 100
# define MOVE_LEFT 97
# define MOVE_UP 119
# define MOVE_DOWN 115
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

void walk(t_player *player)
{
    float dist = 0.25f;
    if (player->move_right == 1)
    {
        if (player->map[(int)(player->x - sin(player->teta) * dist)][(int)(player->y + cos(player->teta) * dist)] != '1')
        {
            player->y += sin(player->teta) * dist;
            player->x += -cos(player->teta) * dist;
        }
    }
    if (player->move_left == 1)
    {
        if (player->map[(int)(player->x + sin(player->teta) * dist)][(int)(player->y - cos(player->teta) * dist)] != '1')
        {
            player->y += -sin(player->teta) * dist;
            player->x += cos(player->teta) * dist;
        }
    }
    if (player->move_up == 1)
    {
        if (player->map[(int)(player->x - sin(player->teta) * dist)][(int)(player->y - cos(player->teta) * dist)] != '1')
        {
            player->y += -cos(player->teta) * dist;
            player->x += -sin(player->teta) * dist;
        }
    }
    if (player->move_down == 1)
    {
        if (player->map[(int)(player->x + sin(player->teta) * dist)][(int)(player->y + cos(player->teta) * dist)] != '1')
        {
            player->y += cos(player->teta) * dist;
            player->x += sin(player->teta) * dist;
        }
    }
}

void camera(t_player *player, int key)
{
    if (key == 1)
    {
        if ((int)player->teta <= (int)-M_PI)
		    player->teta = M_PI;
	    player->teta -= ROTATION;
    }
    else
    {
        if ((int)player->teta >= (int)M_PI)
            player->teta = -M_PI;
        player->teta += ROTATION;
    }
}

int		key_press(int keycode, t_player *player)
{
	if (keycode == RIGHT_ARROW)
		player->camera_right = 1;
	if (keycode == LEFT_ARROW)
		player->camera_left = 1;
	if (keycode == MOVE_UP)
		player->move_up = 1;
	if (keycode == MOVE_DOWN)
		player->move_down = 1;
	if (keycode == MOVE_RIGHT)
		player->move_right = 1;
	if (keycode == MOVE_LEFT)
		player->move_left = 1;
	return (0);
}

int		key_release(int keycode, t_player *player)
{
	if (keycode == RIGHT_ARROW)
		player->camera_right = 0;
	if (keycode == LEFT_ARROW)
		player->camera_left = 0;
	if (keycode == MOVE_UP)
		player->move_up = 0;
	if (keycode == MOVE_DOWN)
		player->move_down = 0;
	if (keycode == MOVE_RIGHT)
		player->move_right = 0;
	if (keycode == MOVE_LEFT)
		player->move_left = 0;
	return (0);
}

void init_struct_player(t_player *player)
{
    player->x = 7.0f;
    player->y = 7.0f;
    player->teta = M_PI / 4;
    player->move_right = 0;
    player->move_left = 0;
    player->move_up = 0;
    player->move_down = 0;
    player->camera_left = 0;
    player->camera_right = 0;
    player->image = NULL;
    player->map = NULL;
    player->mlx_ptr =  NULL;
    player->mlx_win = NULL;
    player->img_ptr = NULL;
}

float raymarch(float i, float j, float angle, char **map, t_player *player)
{
    float d = 0.01;
    while ((int)(i + sin(angle) * d) < 11 && (int)(j + cos(angle) * d) < 9 && map[(int)(i + sin(angle) * d)][(int)(j + cos(angle) * d)] != '1')
    {
        d += 0.01;
    }
    return d * cos(fabs(angle - player->teta));
}

void texture(char *image, float i, float j, unsigned int color)
{
    image[(int)(((j * (WIDTH) * 4) + (i * 4)))] = color;
}

unsigned int	rgb3(unsigned int r, unsigned int g, unsigned int b)
{
	return (r * 256 * 256) + (g * 256) + b;
}

void draw_walls(char *image, float distance, float wall_height, char **map, t_player *player)
{
    float height_coord = 0;
    float width_coord = 0;
    wall_height = 0;

    while (width_coord < WIDTH)
    {
        float teta = player->teta + FOV / 2 - width_coord * FOV / WIDTH;
        distance = raymarch(player->x, player->y, teta, map, player);
        wall_height = (WIDTH / 4) / distance;
        while (height_coord < HEIGHT / 2 - wall_height / 2)
        {
            if (((int)(((height_coord * WIDTH * 4) + (width_coord * 4) + 3))) <= (WIDTH * HEIGHT * 4) && (int)(((height_coord * WIDTH * 4) + (width_coord * 4))) >= 0)
                texture(image, width_coord, height_coord, rgb3(0, 0, 0));
            height_coord++;
        }
        while (height_coord < HEIGHT / 2 + wall_height / 2)
        {
            if (((int)(((height_coord * WIDTH * 4) + (width_coord * 4) + 3))) <= (WIDTH * HEIGHT * 4) && (int)(((height_coord * WIDTH * 4) + (width_coord * 4))) >= 0)
                texture(image, width_coord, height_coord, rgb3(255, 255, 255));
            height_coord++;
        }
        while (height_coord < HEIGHT)
        {
            if (((int)(((height_coord * WIDTH * 4) + (width_coord * 4) + 3))) <= (WIDTH * HEIGHT * 4) && (int)(((height_coord * WIDTH * 4) + (width_coord * 4))) >= 0)
                texture(image, width_coord, height_coord, rgb3(0, 0, 0));
            height_coord++;
        }
        height_coord = 0;
        width_coord++;
    }
    mlx_put_image_to_window(player->mlx_ptr, player->mlx_win, player->img_ptr, 0, 0);
}

int moves(t_player *player)
{
    if (player->move_right || player->move_left || player->move_up || player->move_down)
        walk(player);
    if (player->camera_left)
        camera(player, 0);
    if (player->camera_right)
        camera(player, 1);
    draw_walls(player->image, 0, 0, player->map, player);
    return 0;
}

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
    if (!(player.map = malloc(sizeof(char*) * 255)))   
        return 1;
    while ((i = get_next_line(fd, &line)))
    {
        player.map[x] = strdup(line);
        printf("%s\n", line);
        x++;
    }
    player.map[x] = strdup(line);
    player.map[++x] = NULL;
    char *title = "CUB";
    int bpp = 0;
    int size_line = 0;
    int endian = 0;
    if (!(player.mlx_ptr = mlx_init()))
        return 1;
    if (!(player.mlx_win = mlx_new_window(player.mlx_ptr, WIDTH, HEIGHT, title)))
        return 1;
    if (!(player.img_ptr = mlx_new_image(player.mlx_ptr, WIDTH, HEIGHT)))
        return 1;
    if (!(player.image = mlx_get_data_addr(player.img_ptr, &bpp, &size_line, &endian)))
        return 1;
    // draw_walls(player.image, 0, 0, player.map, &player);
    // mlx_put_image_to_window(mlx_ptr, mlx_win, img_ptr, 0, 0);
    mlx_hook(player.mlx_win, 02, 1L << 0, &key_press, &player);
	mlx_hook(player.mlx_win, 03, 1L << 1, &key_release, &player);
	// mlx_hook(player->ids.mlx_win, 15, 1L << 16, &minimise, player);
	// mlx_hook(player->ids.mlx_win, 17, 1L << 17, &exit_game, player);
    mlx_loop_hook(player.mlx_ptr, &moves, &player);
    mlx_loop(player.mlx_ptr);
    // draw_walls(player.image, 0, 0, player.map, &player);
    return 0;
}