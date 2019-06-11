/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** AnimatorException.hpp
*/

/* Created the 28/05/2019 at 16:55 by jfrabel */

#ifndef INDIESTUDIO_ANIMATOREXCEPTION_HPP
#define INDIESTUDIO_ANIMATOREXCEPTION_HPP

#include <string>
#include "Exceptions.hpp"

namespace indie {
    namespace exceptions {
        class AnimatorException : public jf::ECSException {
        public:
            explicit AnimatorException(const std::string &err, const std::string &where = "");
        };
    }
}

#endif //INDIESTUDIO_ANIMATOREXCEPTION_HPP
