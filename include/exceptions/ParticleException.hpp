/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** ParticleException
*/

#ifndef PARTICLEEXCEPTION_HPP_
#define PARTICLEEXCEPTION_HPP_

#include <exception>
#include <string>
#include "Exceptions.hpp"

namespace indie {
    namespace exceptions {
        class IrrlichtParticleException : public jf::ECSException {
        public:
            explicit IrrlichtParticleException(const std::string &err, const std::string &where = "");
        };
    }
}

#endif /* !PARTICLEEXCEPTION_HPP_ */
