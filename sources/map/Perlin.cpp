/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Perlin.cpp
*/

//
// Created by romainfouyer on 5/27/19.
//

#include <random>
#include <algorithm>
#include <iostream>
#include "map/Perlin.hpp"

indie::Perlin::Perlin(unsigned int seed)
{
    _permutationVector.resize(256);
    for (unsigned int i = 0; i < 256; i++) {
        _permutationVector[i] = i;
    }
    std::default_random_engine engine(seed);
    std::shuffle(_permutationVector.begin(), _permutationVector.end(), engine);
    _permutationVector.insert(_permutationVector.end(), _permutationVector.begin(), _permutationVector.end());
}

float indie::Perlin::noise(float x, float y, float z)
{
    int xx = static_cast<int>(floor(x)) & 255;
    int yy = static_cast<int>(floor(y)) & 255;
    int zz = static_cast<int>(floor(z)) & 255;
    float u = 0;
    float v = 0;
    float w = 0;
    int a = 0;
    int aa = 0;
    int ab = 0;
    int b = 0;
    int ba = 0;
    int bb = 0;
    float arg1 = 0;
    float arg2 = 0;
    float res = 0;

    x = x - floor(x);
    y = y - floor(y);
    z = z - floor(z);
    u = fade(x);
    v = fade(y);
    w = fade(z);
    a = _permutationVector[xx] + yy;
    aa = _permutationVector[a] + zz;
    ab = _permutationVector[a + 1] + zz;
    b = _permutationVector[xx + 1] + yy;
    ba = _permutationVector[b] + zz;
    bb = _permutationVector[b + 1] + zz;
    arg1 = lerp(v, lerp(u, grad(_permutationVector[aa], x, y, z), grad(_permutationVector[ba], x-1, y, z)), lerp(u, grad(_permutationVector[ab], x, y-1, z), grad(_permutationVector[bb], x-1, y-1, z)));
    arg2 = lerp(v, lerp(u, grad(_permutationVector[aa + 1], x, y, z-1), grad(_permutationVector[ba + 1], x-1, y, z-1)), lerp(u, grad(_permutationVector[ab + 1], x, y-1, z-1), grad(_permutationVector[bb + 1], x - 1, y - 1, z - 1)));
    res = lerp(w,
            arg1,
            arg2);
    return (res + 1) / 2;
}

float indie::Perlin::fade(float t)
{
    float res = t * t * t * (t * (t * 6 - 15) + 10);

    return res;
}

float indie::Perlin::grad(int h, float x, float y, float z)
{
    int hash = h & 15;
    float u = 0;
    float v = 0;
    float res = 0;

    if (hash < 8) u = x;
    else u = y;

    if (hash < 4) v = y;
    else {
        if (hash == 12 || hash == 14) v = x;
        else v = z;
    }

    if ((hash & 1) == 0) res += u;
    else res += (-u);

    if ((hash & 2) == 0) res += v;
    else res += (-v);

    return res;
}

float indie::Perlin::lerp(float t, float a, float b)
{
    float res = a + t * (b - a);

    return res;
}