/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** ParticleComponent
*/

#include "IrrlichtParticleComponent.hpp"

jf::IrrlichtParticleComponent::IrrlichtParticleComponent(entities::Entity &entity)
    : Component(entity)
{
    EMIT_CREATE(IrrlichtParticleComponent);
}