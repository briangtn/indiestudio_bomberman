/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** ParticleException
*/

#ifndef PARTICLEEXCEPTION_HPP_
#define PARTICLEEXCEPTION_HPP_

#include "Exceptions.hpp"
#include <exception>
#include <string>

namespace jf
{
    namespace exceptions
    {
        class IrrlichtParticleException : public ECSException {
            public:
                explicit IrrlichtParticleException(const std::string &err, const std::string &where = "");
        };
    }
}

#endif /* !PARTICLEEXCEPTION_HPP_ */
