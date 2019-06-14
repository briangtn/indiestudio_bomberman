/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** DynamicCamera.cpp
*/

/* Created the 12/06/2019 at 22:30 by jfrabel */

#include "Events.hpp"
#include "components/DynamicCamera.hpp"

indie::components::DynamicCamera::DynamicCamera(jf::entities::Entity &entity)
    : Component(entity), _movementSpeed(30.0f), _blockBorders(2)
{
    EMIT_CREATE(DynamicCamera);
}

indie::components::DynamicCamera::~DynamicCamera()
{
    EMIT_DELETE(DynamicCamera);
}

float indie::components::DynamicCamera::getMovementSpeed() const
{
    return _movementSpeed;
}

void indie::components::DynamicCamera::setMovementSpeed(float movementSpeed)
{
    _movementSpeed = movementSpeed;
}

int indie::components::DynamicCamera::getBlockBorders() const
{
    return _blockBorders;
}

void indie::components::DynamicCamera::setBlockBorders(int blockBorders)
{
    _blockBorders = blockBorders;
}

indie::components::DynamicCamera &indie::components::DynamicCamera::operator>>(std::ostream &file)
{
    file << R"(        <component type="DynamicCamera">)" << std::endl;
    file << R"(            <argument name="movementSpeed" value=")" << _movementSpeed << R"("/>)" << std::endl;
    file << R"(            <argument name="blockBorders" value=")" << _blockBorders << R"("/>)" << std::endl;
    file << R"(        </component>)" << std::endl;
    return *this;
}
