/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** AIController
*/

#ifndef AICONTROLLER_HPP_
#define AICONTROLLER_HPP_

#include "Component.hpp"
#include "maths/Vectors.hpp"
#include "ai/AStar.hpp"
#include "Bomb.hpp"

namespace indie {

    namespace components {

        class AIController : public jf::components::Component {
            public:
                AIController(jf::entities::Entity &entity);
                ~AIController();
                        
            public:
                typedef enum {
                    SEARCH,
                    FOCUS,
                    POWERUP,
                    SURVIVE,
                    TAUNT,
                    UNKNOWN
                } state;

                void setTargetVector(indie::maths::Vector3D assign);
                void setIsTaunting(bool assign);
                void setIsPlacingBombs(bool assign);
                void setState(state);
                void setNeedToTaunt(bool assign);
                void setNeedToUseBomb(bool assign);
                void setLastState(state assign);
                void setPreviousPos(std::pair<int, int>assign);
                void setFullNodePath(std::vector<ai::AStar::Node> fullPath);
                void setHasTarget(bool assign);
                void setHasBombWaitingToExplode(bool assign);

                std::vector<ai::AStar::Node> getFullNodePath() const;
                std::pair<int, int> getPreviousPos() const;
                bool getIsTaunting() const;
                bool getIsPlacingBomb() const;
                bool getHasBombWaitingToExplode() const;
                indie::maths::Vector3D getTarget() const;
                state getState() const;
                state getLastState() const;
                bool getNeedToTaunt() const;
                bool getNeedToUseBomb() const;
                bool getHasTarget() const;
                maths::Vector3D getFinalTarget(std::vector<ai::AStar::Node> fullPath) const;

                int getBombForce() const;
                void setBombForce(int bombForce);

                int getMaxBomb() const;
                void setMaxBomb(int maxBomb);

                PlayerType getPlayerType() const;
                void setPlayerType(PlayerType playerType);

                float getMovementSpeed() const;
                void setMovementSpeed(float movementSpeed);

                AIController &operator>>(std::ostream &file);

        private:
                indie::maths::Vector3D _target;
                std::pair<int, int> _previousPos;
                bool _isTaunting;
                bool _needToTaunt;
                bool _isPlacingBomb;
                bool _needToUseBomb;
                bool _hasTarget;
                state _state;
                state _lastState;
                std::vector<ai::AStar::Node> _fullNodePath;
                bool _hasBombWaitingToExplode;

                int _bombForce;
                int _maxBomb;

                PlayerType _playerType;

                float _movementSpeed;

                jf::internal::ID _endAnimationListenerEventId;
                jf::internal::ID _reachTargetListenerEventId;
                jf::internal::ID _bombExplosion;
        };
    }
}

#else

namespace indie {

    namespace components {
        class AIController;
    }
}

#endif /* !AICONTROLLER_HPP_ */