/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** ParticleException
*/

#include "exceptions/ParticleException.hpp"

indie::exceptions::IrrlichtParticleException::IrrlichtParticleException(const std::string &err, const std::string &where)
    : ECSException(err, where)
{

}