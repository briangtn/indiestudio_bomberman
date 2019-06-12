/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** PpmImage.hpp
*/

//
// Created by romainfouyer on 5/27/19.
//

#ifndef INDIESTUDIO_PPMIMAGE_HPP
#define INDIESTUDIO_PPMIMAGE_HPP

#include <map>
#include <vector>

namespace indie {

    class PpmImage {
    public:
        PpmImage(unsigned int width, unsigned int height);

        void writeImage(const std::string &fileName);
        std::map<char, std::vector<unsigned char>> _rgb;
    private:
        unsigned int _width;
        unsigned int _height;
        unsigned int _totalSize;
    };

}


#endif //INDIESTUDIO_PPMIMAGE_HPP
