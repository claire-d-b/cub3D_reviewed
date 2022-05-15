#ifndef FIXED_H
#define FIXED_H

#include <iostream>
#include <cmath>

class Fixed
{
    private:
        int _n;
        static const int _f;
        float pow_rebuild(float nb, float pow) const;
    public:
        Fixed( void );
        Fixed( const Fixed& rhs );
        Fixed( const int n);
        Fixed( const float n);
        ~Fixed();
        const Fixed & operator=( Fixed const & rhs);
        int getRawBits(void) const;
        void setRawBits(int const raw);
        float toFloat(void) const;
        int toInt(void) const;
        int operator<(Fixed const & rhs);
        int operator>(Fixed const & rhs);
        int operator<=(Fixed const & rhs);
        int operator>=(Fixed const & rhs);
        int operator==(Fixed const & rhs);
        int operator!=(Fixed const & rhs);
        Fixed operator+(Fixed const & rhs);
        Fixed operator-(Fixed const & rhs);
        Fixed operator*(Fixed const & rhs);
        Fixed operator/(Fixed const & rhs);
        Fixed& operator++( void );
        Fixed operator++(int inc);
        Fixed& operator--( void );
        Fixed operator--(int inc);
        static const Fixed& min(Fixed const & a, Fixed const & b);
        static const Fixed& max(Fixed const & a, Fixed const & b);
        static Fixed& min(Fixed & a, Fixed & b);
        static Fixed& max(Fixed & a, Fixed & b);
};

std::ostream & operator<<(std::ostream & o, Fixed const & rhs);
Fixed fxabs(Fixed const & rhs);

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

void walk(t_player *player);
void camera(t_player *player, int key);
int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
void init_struct_player(t_player *player);
Fixed raymarch(Fixed i, Fixed j, Fixed angle, char **map, t_player *player);
void texture(char *image, int i, int j, unsigned int color);
unsigned int	rgb3(unsigned int r, unsigned int g, unsigned int b);
unsigned int	find_color(t_player *player);
void draw_walls(char *image, Fixed distance, Fixed wall_height, char **map, t_player *player);
int moves(t_player *player);

#endif