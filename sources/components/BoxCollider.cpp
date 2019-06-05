/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** BoxCollider.cpp
*/

/* Created the 28/05/2019 at 19:56 by jfrabel */

#include <ECSWrapper.hpp>
#include <components/Transform.hpp>
#include <maths/Geometry3D.hpp>
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

bool indie::components::BoxCollider::hasCollisions(bool ignoreLayer)
{
    return !getCollisions(ignoreLayer).empty();
}

std::vector<jf::entities::EntityHandler> indie::components::BoxCollider::getCollisions(bool ignoreLayer)
{
    ECSWrapper ecs;

    std::vector<jf::entities::EntityHandler> colliding;

    auto entitiesWithCollider = ecs.entityManager.getEntitiesWith<BoxCollider>();

    auto playerTr = getEntity()->getComponent<components::Transform>();
    maths::Vector3D playerPosition;
    maths::Vector3D playerScale = {1, 1, 1};
    maths::Vector3D playerRotation;
    if (playerTr.isValid()) {
        playerPosition = playerTr->getPosition();
        playerScale = playerTr->getScale();
        playerRotation = playerTr->getRotation();
    }
    maths::OBB playerOBB(playerPosition + _offset, playerScale * _size, maths::Matrix3::Rotation(playerRotation.x, playerRotation.y, playerRotation.z));

    for (auto &entity : entitiesWithCollider) {
        if (entity->getID() == this->getEntity()->getID())
            continue;

        auto collider = entity->getComponent<components::BoxCollider>();

        if (ignoreLayer || !(collider->getLayer() & _layer))
            continue;

        auto tr = entity->getComponent<components::Transform>();

        maths::Vector3D position;
        maths::Vector3D scale = {1, 1, 1};
        maths::Vector3D rotation;
        if (tr.isValid()) {
            position = tr->getPosition();
            scale = tr->getScale();
            rotation = tr->getRotation();
        }
        maths::OBB obb(position + collider->getOffset(), scale * collider->getSize(), maths::Matrix3::Rotation(rotation.x, rotation.y, rotation.z));

        if (obb.collides(playerOBB))
            colliding.push_back(entity);
    }
    return colliding;
}
