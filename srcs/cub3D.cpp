#include "cub3d.hpp"
#include "fixed.hpp"
#include "./minilibx/mlx.h"

int hit_walls(float i, float j, t_player *player)
{
    if (player->map[(int)i][(int)j] == '1')
        return 1;
    return 0;
}

void walk(t_player *player)
{
    float dist = 0.50f;
    if (player->move_right == 1)
    {
        if (player->map[(int)(player->x - sin(player->teta) * dist)][(int)(player->y + cos(player->teta) * dist)] != '1')
        {
            if (!hit_walls(player->x + -cos(player->teta) * dist, player->y + sin(player->teta) * dist, player))
            {
                player->y = player->y + sin(player->teta) * dist;
                player->x = player->x + -cos(player->teta) * dist;
            }
        }
    }
    if (player->move_left == 1)
    {
        if (player->map[(int)(player->x + sin(player->teta) * dist)][(int)(player->y - cos(player->teta) * dist)] != '1')
        {
            if (!hit_walls(player->x + cos(player->teta) * dist, player->y + -sin(player->teta) * dist, player))
            {
                player->y = player->y + -sin(player->teta) * dist;
                player->x = player->x + cos(player->teta) * dist;
            }
        }
    }
    if (player->move_up == 1)
    {
        if (player->map[(int)(player->x - sin(player->teta) * dist)][(int)(player->y - cos(player->teta) * dist)] != '1')
        {
            if (!hit_walls(player->x + -sin(player->teta) * dist, player->y +  -cos(player->teta) * dist, player))
            {
                player->y = player->y +  -cos(player->teta) * dist;
                player->x = player->x + -sin(player->teta) * dist;
            }
        }
    }
    if (player->move_down == 1)
    {
        if (player->map[(int)(player->x + sin(player->teta) * dist)][(int)(player->y + cos(player->teta) * dist)] != '1')
        {
            if (!hit_walls(player->x + sin(player->teta) * dist, player->y + cos(player->teta) * dist, player))
            {
                player->y = player->y + cos(player->teta) * dist;
                player->x = player->x + sin(player->teta) * dist;
            }
        }
    }
}

void camera(t_player *player, int key)
{
    if (key == 1)
    {
        if ((int)player->teta <= (int)-PI)
		    player->teta = PI;
	    player->teta = player->teta - ROTATION;
    }
    else
    {
        if ((int)player->teta >= (int)PI)
            player->teta = -PI;
        player->teta = player->teta + ROTATION;
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
    player->teta = PI / 4;
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
    player->w = 0.0f;
    player->h = 0.0f;
}

float raymarch(float i, float j, float angle, char **map, t_player *player)
{
    float d = 0.01f;
    while ((i + sin(angle) * d) < 11 && (j + cos(angle) * d) < 9 && map[(int)(i + sin(angle) * d)][(int)(j + cos(angle) * d)] != '1')
    {
        d += 0.01f;
    }
    player->w = i + sin(angle) * d;
    player->h = j + cos(angle) * d;
    return d * cos(fabs(angle - player->teta));
}

void texture(char *image, int i, int j, unsigned int color)
{
    image[(int)(((j * (WIDTH) * 4) + (i * 4)))] = color;
    image[(int)(((j * (WIDTH) * 4) + (i * 4) + 1))] = color / 256;
    image[(int)(((j * (WIDTH) * 4) + (i * 4) + 2))] = color / (256 * 256);
    image[(int)(((j * (WIDTH) * 4) + (i * 4) + 3))] = 1;
}

unsigned int	rgb3(unsigned int r, unsigned int g, unsigned int b)
{
	return (r * 256 * 256) + (g * 256) + b;
}

unsigned int	find_color(t_player *player)
{
    if (fabs((int)player->w - player->w) > 0.0 && fabs((int)player->w - player->w) < 0.01 && fabs((int)player->h - player->h) >= 0.01 && fabs((int)player->h - player->h) < 1.0)
	    return rgb3(0, 255, 255);
    if (fabs((int)player->h - player->h) > 0.0 && fabs((int)player->h - player->h) < 0.01 && fabs((int)player->w - player->w) >= 0.01 && fabs((int)player->w - player->w) < 1.0)
	    return rgb3(0, 102, 255);
    if (fabs((int)player->h - player->h) > 0.99 && fabs((int)player->h - player->h) <= 1.0 && fabs((int)player->w - player->w) > 0.01 && fabs((int)player->w - player->w) <= 1.0)
	    return rgb3(255, 153, 255);
    if (fabs((int)player->h - player->h) > 0.01 && fabs((int)player->h - player->h) <= 1.0 && fabs((int)player->w - player->w) > 0.99 && fabs((int)player->w - player->w) <= 1.0)
	    return rgb3(102, 255, 153);
    return rgb3(0, 0, 0);
}

void draw_walls(char *image, float distance, Fixed wall_height, char **map, t_player *player)
{
    int height_coord = 0;
    int width_coord = 0;
    wall_height = 0;

    while (width_coord < (int)WIDTH)
    {
        float teta(player->teta + FOV / 2 - width_coord * FOV / WIDTH);
        distance = raymarch(player->x, player->y, teta, map, player);
        wall_height = Fixed((WIDTH / 2) / distance);
        // printf("wall height %f\n", wall_height);
        while (height_coord < (int)(HEIGHT / 2 - wall_height.toFloat() / 2))
        {
            if (((int)(((height_coord * WIDTH * 4) + (width_coord * 4) + 3))) <= (WIDTH * HEIGHT * 4) && (int)(((height_coord * WIDTH * 4) + (width_coord * 4))) >= 0)
                texture(image, width_coord, height_coord, rgb3(0, 0, 0));
            height_coord++;
            // printf("a");
        }
        while (height_coord < (int)(HEIGHT / 2 + wall_height.toFloat() / 2))
        {
            if (((int)(((height_coord * WIDTH * 4) + (width_coord * 4) + 3))) <= (WIDTH * HEIGHT * 4) && (int)(((height_coord * WIDTH * 4) + (width_coord * 4))) >= 0)
                texture(image, width_coord, height_coord, find_color(player));
            height_coord++;
            // printf("b");
        }
        while (height_coord < (int)(HEIGHT))
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
    draw_walls(player->image, 0, Fixed(0), player->map, player);
    return 0;
}
