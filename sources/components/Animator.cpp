/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Animator.cpp
*/

/* Created the 28/05/2019 at 16:30 by jfrabel */

#include <components/Mesh.hpp>
#include "Events.hpp"
#include "components/Animator.hpp"
#include "exceptions/AnimatorException.hpp"

indie::components::Animator::Animator(jf::entities::Entity &entity)
    : Component(entity),
      _currentAnimation(""),
      _animationJustChanged(false),
      _animations()
{
    EMIT_CREATE(Animator);
}

indie::components::Animator::Animator(
    jf::entities::Entity &entity,
    const std::string &name,
    const indie::components::Animator::Animation &anim)
    : Component(entity),
      _currentAnimation(name),
      _animationJustChanged(true),
      _animations()
{
    _animations.emplace(std::make_pair(name, anim));
    setCurrentAnimation(name);
    EMIT_CREATE(Animator);
}

indie::components::Animator::Animator(
    jf::entities::Entity &entity,
    const std::map<std::string, indie::components::Animator::Animation> &animations)
    : Component(entity),
      _currentAnimation(""),
      _animationJustChanged(false),
      _animations(animations)
{
    if (!_animations.empty()) {
        setCurrentAnimation(_animations.begin()->first);
    }
    EMIT_CREATE(Animator);
}

indie::components::Animator::~Animator()
{
    EMIT_DELETE(Animator);
    auto mesh = getEntity()->getComponent<components::Mesh>();
    if (mesh.isValid() && mesh->getAnimatedMeshNode() != nullptr) {
        mesh->getAnimatedMeshNode()->setAnimationEndCallback(nullptr);
    }
}

void indie::components::Animator::addAnimation(const std::string &name, const indie::components::Animator::Animation &anim)
{
    _animations.emplace(std::make_pair(name, anim));
}

void indie::components::Animator::addAnimations(const std::map<std::string, indie::components::Animator::Animation> &animations)
{
    for (const auto &animation : animations) {
        _animations.emplace(std::make_pair(animation.first, animation.second));
    }
}

void indie::components::Animator::removeAnimation(const std::string &name)
{
    _animations.erase(name);
}

void indie::components::Animator::removeAnimations(const std::vector<std::string> &names)
{
    for (auto &name : names) {
        _animations.erase(name);
    }
}

bool indie::components::Animator::doesAnimationExist(const std::string &name) const
{
    return _animations.find(name) != _animations.end();
}

void indie::components::Animator::setCurrentAnimation(const std::string &name)
{
    _currentAnimation = name;
    _animationJustChanged = true;
}

const std::string &indie::components::Animator::getCurrentAnimation() const
{
    return _currentAnimation;
}

const indie::components::Animator::Animation &indie::components::Animator::getCurrentAnimationData() const
{
    if (!doesAnimationExist(_currentAnimation))
        throw exceptions::AnimatorException(_currentAnimation + " does not exist");
    return _animations.at(_currentAnimation);
}

bool indie::components::Animator::hasAnimationChanged() const
{
    return _animationJustChanged;
}

void indie::components::Animator::resetAnimationChanged()
{
    _animationJustChanged = false;
}

void indie::components::Animator::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode *node)
{
    if (!doesAnimationExist(_currentAnimation))
        throw exceptions::AnimatorException(_currentAnimation + " does not exist");
    auto &data = _animations.at(_currentAnimation);
    if (!data.loop && !data.transition.empty()) {
        setCurrentAnimation(data.transition);
    }
}