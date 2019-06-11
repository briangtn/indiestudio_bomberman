/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Perlin.hpp
*/

//
// Created by romainfouyer on 5/27/19.
//

#ifndef INDIESTUDIO_PERLIN_HPP
#define INDIESTUDIO_PERLIN_HPP

#include <vector>

namespace indie {

    class Perlin {
    public:
        Perlin(unsigned int seed);

        float noise(float x, float y, float z);
    private:
        float fade(float t);
        float lerp(float t, float a, float b);
        float grad(int h, float x, float y, float z);

        std::vector<unsigned int> _permutationVector;
    };
}


#endif //INDIESTUDIO_PERLIN_HPP
