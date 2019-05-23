/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrlichtManagerExceptions.hpp
*/

/* Created the 10/05/2019 at 11:09 by jfrabel */

#ifndef INDIESTUDIO_IRRLICHTMANAGEREXCEPTIONS_HPP
#define INDIESTUDIO_IRRLICHTMANAGEREXCEPTIONS_HPP

#include <exception>
#include <string>
#include "Exceptions.hpp"

namespace indie {

    namespace exceptions {

        class IrrlichtManagerException : public jf::ECSException {
        public:
            explicit IrrlichtManagerException(const std::string &err, const std::string &where = "");
        };

        class IrrlichtManagerDeviceException : public IrrlichtManagerException {
        public:
            explicit IrrlichtManagerDeviceException(const std::string &err, const std::string &where = "");
        };

        class IrrlichtManagerVideoDriverException : public IrrlichtManagerException {
        public:
            explicit IrrlichtManagerVideoDriverException(const std::string &err, const std::string &where = "");
        };

        class IrrlichtManagerSceneManagerException : public IrrlichtManagerException {
        public:
            explicit IrrlichtManagerSceneManagerException(const std::string &err, const std::string &where = "");
        };

        class IrrlichtManagerGUIEnvironmentException : public IrrlichtManagerException {
        public:
            explicit IrrlichtManagerGUIEnvironmentException(const std::string &err, const std::string &where = "");
        };
    }
}

#endif //INDIESTUDIO_IRRLICHTMANAGEREXCEPTIONS_HPP
