/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** GuiBase.cpp
*/

/* Created the 04/06/2019 at 15:05 by brian */

#include "Events.hpp"
#include "components/GUI/GuiBase.hpp"

indie::components::GUIBase::GUIBase(jf::entities::Entity &entity, int id)
    : Component(entity),
    _id(id)
{
    EMIT_CREATE(GUIBase);
}

indie::components::GUIBase::~GUIBase()
{
    EMIT_DELETE(GUIBase);
}

int indie::components::GUIBase::getId() const
{
    return _id;
}

void indie::components::GUIBase::setId(int id)
{
    _id = id;
}
