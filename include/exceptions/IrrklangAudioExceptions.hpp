/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrlichtAudioExceptions.hpp
*/

/* Created the 22/05/2019 at 18:41 by jbulteau */

#ifndef INDIESTUDIO_IRRKLANGAUDIOEXCEPTIONS_HPP
#define INDIESTUDIO_IRRKLANGAUDIOEXCEPTIONS_HPP

#include "Exceptions.hpp"

namespace indie {

    namespace exceptions {

        class IrrklangAudioException : public jf::ECSException {
        public:
            explicit IrrklangAudioException(const std::string &err, const std::string &where = "");
        };

        class IrrklangAudioDeviceException : public IrrklangAudioException {
        public:
            explicit IrrklangAudioDeviceException(const std::string &err, const std::string &where = "");
        };
    }
}

#endif //INDIESTUDIO_IRRKLANGAUDIOEXCEPTIONS_HPP
