#pragma once

#include <list>
#include <type_traits>
#include <string>
#include <iomanip>   // std::setw & std::setfill
#include <iostream>

// debug ================================================================
void utils_debug(std::string msg);

// transform ============================================================
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
struct Vec2 {
    int x;
    int y;

    Vec2() :x(0), y(0) {};
    Vec2(int x, int y) :x(x), y(y) {};

    // oevrloaded by numeral type
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    Vec2 operator*(T rhs) const {
        return Vec2(static_cast<int>(x * rhs), static_cast<int>(y * rhs));
    }
    Vec2 operator+(const Vec2& rhs) const {
        return Vec2(x + rhs.x, y + rhs.y);
    }
    Vec2 operator-(const Vec2& rhs) const {
        return Vec2(x - rhs.x, y - rhs.y);
    }

};

struct PosPair {
    Vec2 a;
    Vec2 b;

    PosPair() {};
    PosPair(Vec2 a, Vec2 b) : a(a), b(b) { };
};

int utils_index(int x, int y, int width);
double utils_angle_btw_vecs(const Vec2& center, const Vec2& to);
Vec2 utils_rotate_by_centre(const Vec2& center, const Vec2& source, double angle);
//Vec2 utils_normalize(Vec2 from, Vec2 to);
Vec2 utils_offset_by_direction(double distance, const Vec2& unNormalizedDir);
int utils_dist_square(const Vec2& sourceA, const Vec2& sourceB);

//math ==================================================================
#define utils_clamp(v, min, max) ((v) > (max) ? (max) : (v) < (min) ? (min) : (v))

template<typename T>
T utils_clamp_g(T v, T min, T max)
{
    return ((v) > (max) ? (max) : (v) < (min) ? (min) : (v));
}

int utils_get_sign(int x);
int utils_rand(int lower, int upper);
float utils_lerp(float from, float to, float by);
//Vec2 utils_lerp_vec(Vec2 from, Vec2 to, float by);
int utils_ping_pong(int time, int length);
std::string utils_getTimeStr(int seconds);


// containter ============================================================
template<typename T>
bool utils_contains(std::list<T>& listOfElements, const T& element);
//template<typename T>
//bool utils_contains(const std::list<T, std::allocator<T>>& listOfElements, const T& element);
