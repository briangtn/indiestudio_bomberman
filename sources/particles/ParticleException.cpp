/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** ParticleException
*/

#include "ParticleException.hpp"

jf::exceptions::IrrlichtParticleException::IrrlichtParticleException(const std::string &err, const std::string &where)
    : ECSException(err, where)
{

}