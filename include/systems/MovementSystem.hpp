/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** MovementSystem.hpp
*/

/* Created the 24/05/2019 at 13:53 by jfrabel */

#ifndef INDIESTUDIO_MOVEMENTSYSTEM_HPP
#define INDIESTUDIO_MOVEMENTSYSTEM_HPP

#include "System.hpp"
#include "ai/AiView.hpp"
#include "components/MoveToTarget.hpp"
#include "ai/AStar.hpp"

namespace indie {

    namespace systems {

        class MovementSystem : public jf::systems::ISystem {
        public:
            MovementSystem();
            ~MovementSystem() override ;

        public:
            void onAwake() override;
            void onStart() override;
            void onUpdate(const std::chrono::nanoseconds &elapsedTime) override;
            void onStop() override;
            void onTearDown() override;

        public:
            const maths::Vector2D &getMapSize() const;
            void setMapSize(const maths::Vector2D &mapSize);

        private:
            void updateRotator(const std::chrono::nanoseconds &elapsedTime) const;
            void updateHoverer(const std::chrono::nanoseconds &elapsedTime) const;
            void updatePlayerMovement(const std::chrono::nanoseconds &elapsedTime) const;
            void updateMoveToTargetMovement(const std::chrono::nanoseconds &elapsedTime);

            void recomputeCaches();

        private:
            using NodePath = std::stack<ai::AStar::Node>;
            using MoveToTargetPathsCache = std::list<std::tuple<jf::components::ComponentHandler<components::MoveToTarget>, jf::components::ComponentHandler<components::Transform>, NodePath>>;

        private:
            static constexpr float recomputeCacheDeltaTime = 0.5f;
            static constexpr float nodeValidatedInRadius = 2.0f;

        private:
            maths::Vector2D _mapSize;
            ai::AIView::AICellViewGrid _viewGridCache;
            MoveToTargetPathsCache _pathsCache;
            float _timeBeforeCacheComputation;
        };
    }
}

#endif //INDIESTUDIO_MOVEMENTSYSTEM_HPP
