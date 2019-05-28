/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Animator.hpp
*/

/* Created the 28/05/2019 at 16:30 by jfrabel */

#ifndef INDIESTUDIO_ANIMATOR_HPP
#define INDIESTUDIO_ANIMATOR_HPP

#include <map>
#include <memory>
#include <string>
#include <irrlicht.h>
#include "Component.hpp"

namespace indie {

    namespace components {

        class Animator : public jf::components::Component, public irr::scene::IAnimationEndCallBack {
        public:
            struct Animation {
                Animation(irr::u32 start_, irr::u32 end_, irr::u32 speed_, bool loop_, const std::string &transition_)
                : start(start_), end(end_), speed(speed_), loop(loop_), transition(transition_) {}
                irr::u32 start;
                irr::u32 end;
                irr::u32 speed;
                bool loop;
                std::string transition;
            };

        public:
            explicit Animator(jf::entities::Entity &entity);
            Animator(jf::entities::Entity &entity, const std::string &name, const Animation &anim);
            Animator(jf::entities::Entity &entity, const std::map<std::string, Animation> &animations);
            ~Animator() override;

            void addAnimation(const std::string &name, const Animation &anim);
            void addAnimations(const std::map<std::string, Animation> &animations);
            void removeAnimation(const std::string &name);
            void removeAnimations(const std::vector<std::string> &names);

            bool doesAnimationExist(const std::string &name) const;
            bool hasAnimationChanged() const;

            void resetAnimationChanged();

            void setCurrentAnimation(const std::string &name);
            const std::string &getCurrentAnimation() const;
            const Animation &getCurrentAnimationData() const;

            void OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode *node) override;

        private:
            std::string _currentAnimation;
            bool _animationJustChanged;
            std::map<std::string, Animation> _animations;
        };
    }
}

#endif //INDIESTUDIO_ANIMATOR_HPP
