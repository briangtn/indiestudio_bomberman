/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** MoveToTarget.cpp
*/

/* Created the 12/06/2019 at 11:32 by jfrabel */

#include "components/MoveToTarget.hpp"

indie::components::MoveToTarget::MoveToTarget(jf::entities::Entity &entity)
    : Component(entity), _target(), _followTarget(false)
{

}

const indie::maths::Vector3D &indie::components::MoveToTarget::getTarget() const
{
    return _target;
}

void indie::components::MoveToTarget::setTarget(const indie::maths::Vector3D &target)
{
    _target = target;
}

bool indie::components::MoveToTarget::isFollowTarget() const
{
    return _followTarget;
}

void indie::components::MoveToTarget::setFollowTarget(bool followTarget)
{
    _followTarget = followTarget;
}
