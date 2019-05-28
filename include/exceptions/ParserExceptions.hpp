/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** ParserExceptions.hpp
*/

/* Created the 27/05/2019 at 16:36 by jbulteau */

#ifndef INDIESTUDIO_PARSEREXCEPTIONS_HPP
#define INDIESTUDIO_PARSEREXCEPTIONS_HPP

#include "Exceptions.hpp"

namespace indie {

    namespace exceptions {

        class ParserException : public jf::ECSException {
        public:
            explicit ParserException(const std::string &err, const std::string &where = "");
        };

        class ParserDeviceException : public ParserException {
        public:
            explicit ParserDeviceException(const std::string &err, const std::string &where = "");
        };

        class ParserInvalidFileException : public ParserException {
        public:
            explicit ParserInvalidFileException(const std::string &err, const std::string &where = "");
        };
    }
}

#endif //INDIESTUDIO_PARSEREXCEPTIONS_HPP
