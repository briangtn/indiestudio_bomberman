/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** DestroyOnTime
*/

#include "components/DestroyOnTime.hpp"

indie::components::DestroyOnTime::DestroyOnTime(jf::entities::Entity &entity, float time)
    :   Component(entity), _timeBeforeDestroy(time)
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

indie::components::DestroyOnTime &indie::components::DestroyOnTime::operator>>(std::ostream &file)
{
    file << R"(        <component type="Destroy">)" << std::endl;
    file << R"(            <argument name="time" value=")" << _timeBeforeDestroy << R"("/>)" << std::endl;
    file << "        </component>" << std::endl;
    return *this;
}
