/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** BoxCollider.cpp
*/

/* Created the 28/05/2019 at 19:56 by jfrabel */

#include "Events.hpp"
#include "components/BoxCollider.hpp"

indie::components::BoxCollider::BoxCollider(
    jf::entities::Entity &entity,
    indie::maths::Vector3D size,
    indie::maths::Vector3D offset,
    uint64_t layer)
    : Component(entity),
      _size(size),
      _offset(offset),
      _layer(layer)
{
    EMIT_CREATE(BoxCollider);
}

indie::components::BoxCollider::~BoxCollider()
{
    EMIT_DELETE(BoxCollider);
}

const indie::maths::Vector3D &indie::components::BoxCollider::getSize() const
{
    return _size;
}

void indie::components::BoxCollider::setSize(const indie::maths::Vector3D &size)
{
    _size = size;
}

const indie::maths::Vector3D &indie::components::BoxCollider::getOffset() const
{
    return _offset;
}

void indie::components::BoxCollider::setOffset(const indie::maths::Vector3D &offset)
{
    _offset = offset;
}

uint64_t indie::components::BoxCollider::getLayer() const
{
    return _layer;
}

void indie::components::BoxCollider::setLayer(uint64_t layer)
{
    _layer = layer;
}
