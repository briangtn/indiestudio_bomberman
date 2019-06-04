/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** ImageException.cpp
*/

//
// Created by romainfouyer on 6/4/19.
//

#ifndef INDIESTUDIO_IMAGEEXCEPTION_HPP
#define INDIESTUDIO_IMAGEEXCEPTION_HPP

#include <exception>
#include <string>

namespace indie {
    class ImageException : public std::exception {
    public:
        ImageException(const std::string &what);

        const char *what() const noexcept override;

    protected:
        std::string _what;
    };
}


#endif //INDIESTUDIO_IMAGEEXCEPTION_HPP
