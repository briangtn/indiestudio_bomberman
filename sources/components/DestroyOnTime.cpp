/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** DestroyOnTime
*/

#include "components/DestroyOnTime.hpp"

indie::components::DestroyOnTime::DestroyOnTime(jf::entities::Entity &entity)
    :   Component(entity)
{
    EMIT_CREATE(DestroyOnTime);
}

indie::components::DestroyOnTime::~DestroyOnTime()
{
    EMIT_DELETE(DestroyOnTime);
}

float indie::components::DestroyOnTime::getTimeBeforeDestroy() const
{
    return _timeBeforeDestroy;
}

void indie::components::DestroyOnTime::setTimeBeforeDestroy(const float &newTimeBeforeDestroy)
{
    _timeBeforeDestroy = newTimeBeforeDestroy;
}