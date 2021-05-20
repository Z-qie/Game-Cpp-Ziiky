#pragma once

#include <algorithm>
#include "header.h"
#include "Utils.h"

// debug ================================================================
void utils_debug(std::string msg) {
    std::cout << msg << std::endl;
};
//math ==================================================================
int utils_get_sign(int x) {
    return (int)(x > 0) - (x < 0);
}

int utils_rand(int lower, int upper) {
    if (upper < lower) {
        int tmp = lower;
        lower = upper;
        upper = tmp;
    }
    int ans = std::rand() % (upper - lower + 1) + lower;
    return ans;
}

//int utils_clamp(int v, int min, int max) {
//    return ((v) > (max) ? (max) : (v) < (min) ? (min) : (v));
//}

float utils_lerp(float from, float to, float by)
{// I dont want to use expensive double as return value at all in this game
    return from * (1 - by) + to * by;
}

int utils_ping_pong(int time, int length) {
    int L = 2 * length;
    int T = time % L;

    if (0 <= T && T < length)
        return T;
    else
        return L - T;
}

//Vec2 utils_lerp_vec(Vec2 from, Vec2 to, float by)
//{
//    int retX = utils_lerp(from.x, to.x, by);
//    int retY = utils_lerp(from.y, to.y, by);
//    return Vec2{ retX, retY };
//}

// transform ============================================================
int utils_index(int x, int y, int width) {
    return x + y * width;
}

double utils_angle_btw_vecs(const Vec2& center, const Vec2& to) {
    //double dot = center.x * to.x + center.y * to.y; // dot product
    //double det = center.x * to.y - center.y * to.x; // determinant
    return (1.5) * M_PI - atan2(to.y - center.y, to.x - center.x);
}

Vec2 utils_rotate_by_centre(const Vec2& center, const Vec2& source, double angle) {
    Vec2 offset = source - center;

    /* return Vec2{
        - (int)(sin(angle) * offset.x + cos(angle) * offset.y),
        - (int)(cos(angle) * offset.x - sin(angle) * offset.y)
     };*/
    return Vec2{
      (int)(sin(angle) * offset.y + cos(angle) * offset.x),
      (int)(cos(angle) * offset.y - sin(angle) * offset.x)
    };
}

//Vec2 utils_normalize(Vec2 from, Vec2 to) {
//
//}

Vec2 utils_offset_by_direction(double distance, const Vec2& unNormalizedDir) {
    // I found a faster method to normalize vector
    //https://www.h3xed.com/programming/fast-unit-vector-calculation-for-2d-games
            // Get absolute value of each vector
    int ax = abs(unNormalizedDir.x);
    int ay = abs(unNormalizedDir.y);
    
    double notZero = static_cast <double>(std::max(ax, ay));
    if (notZero != 0) {
        double ratio = 1 / notZero;
        //double ratio = 1 / static_cast <double>(std::max(ax, ay));
        ratio = ratio * (1.29289 - (ax + ay) * ratio * 0.29289);

        return Vec2{
           static_cast<int>(unNormalizedDir.x * distance * ratio),
           static_cast<int>(unNormalizedDir.y * distance * ratio)
        };
    }
    else {
        //std::cout << 0 << std::endl;
        return Vec2{0,0};
    }
}

std::string utils_getTimeStr(int seconds) {
    int minutes = seconds / 60;
    seconds -= minutes * 60;
    char buf[128]{ 0 };
    sprintf(buf, "%02d:%02d", minutes, seconds);
    return std::string(buf);
}

int utils_dist_square(const Vec2& sourceA, const Vec2& sourceB) {
    return (sourceA.x - sourceB.x) * (sourceA.x - sourceB.x) + (sourceA.y - sourceB.y) * (sourceA.y - sourceB.y);
}

// containter ============================================================

template<typename T>
bool utils_contains(const std::list<T>& listOfElements, const T& element)
{
    // Find the iterator if element in list
    auto it = std::find(listOfElements.begin(), listOfElements.end(), element);
    //return if iterator points to end or not. It points to end then it means element
    // does not exists in list
    return it != listOfElements.end();
}
