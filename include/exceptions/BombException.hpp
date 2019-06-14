/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** BombException
*/

#ifndef BOMBEXCEPTION_HPP_
#define BOMBEXCEPTION_HPP_

#include <exception>
#include <string>
#include "Exceptions.hpp"

namespace indie {
    namespace exceptions {
        class BombException : public jf::ECSException {
        public:
            explicit BombException(const std::string &err, const std::string &where = "");
        };
    }
}

#endif /* !BOMBEXCEPTION_HPP_ */
