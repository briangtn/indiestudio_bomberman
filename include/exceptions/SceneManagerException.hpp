/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** SceneManagerException.hpp
*/

/* Created the 22/05/2019 at 15:12 by jfrabel */

#ifndef INDIESTUDIO_SCENEMANAGEREXCEPTION_HPP
#define INDIESTUDIO_SCENEMANAGEREXCEPTION_HPP

#include <exception>
#include <string>
#include "Exceptions.hpp"

namespace indie {
    namespace exceptions {
        class SceneManagerException : public jf::ECSException {
        public:
            explicit SceneManagerException(const std::string &err, const std::string &where = "");
        };
    }
}

#endif //INDIESTUDIO_SCENEMANAGEREXCEPTION_HPP
