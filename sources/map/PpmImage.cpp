/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** PpmImage.cpp
*/

//
// Created by romainfouyer on 5/27/19.
//

#include "map/PpmImage.hpp"
#include <fstream>

indie::PpmImage::PpmImage(unsigned int width, unsigned int height)
: _width(width), _height(height), _totalSize(width * height)
{
    _rgb['r'].resize(_totalSize);
    _rgb['g'].resize(_totalSize);
    _rgb['b'].resize(_totalSize);
}

void indie::PpmImage::writeImage(const std::string &fileName)
{
    std::ofstream image(fileName, std::ios::out | std::ios::binary);
    char rpixel = 0;
    char bpixel = 0;
    char gpixel = 0;

    if (!image.is_open()) {
        // TODO sent exception if image not opened
        return;
    }
    image << "P6" << std::endl << _width << " " << _height << std::endl << 255 << std::endl;
    for (unsigned int i = 0; i < _totalSize; i++) {
        rpixel = _rgb['r'][i];
        gpixel = _rgb['g'][i];
        bpixel = _rgb['b'][i];
        image.write(&rpixel, 1);
        image.write(&gpixel, 1);
        image.write(&bpixel, 1);
    }
    image.close();
}