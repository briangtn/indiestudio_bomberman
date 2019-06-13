/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** AISystem
*/

#ifndef AISYSTEM_HPP_
#define AISYSTEM_HPP_

#include "System.hpp"
#include "components/AIController.hpp"
#include "ai/AiView.hpp"

namespace indie {
    
    namespace systems {

        class AISystem : public jf::systems::ISystem {
            public:
                AISystem();
                ~AISystem() override;
            
            public:
                void onAwake() override;
                void onStart() override;
                void onUpdate(const std::chrono::nanoseconds &elapsedTime) override;
                void onStop() override;
                void onTearDown() override;

                int getTimePassed() const;
                void setTimePassed(int assign);

                static std::vector<int> getPlayerPos(ai::AIView::AICellViewGrid grid);
                static void chooseState(jf::components::ComponentHandler<indie::components::AIController> &component,
                jf::entities::EntityHandler &entity,
                std::vector<jf::entities::EntityHandler> &bonuses,
                std::vector<jf::entities::EntityHandler> &players);
                static void AILogic(jf::entities::EntityHandler entity,
                    jf::components::ComponentHandler<indie::components::AIController> component);
                static void randomHandling(indie::components::AIController::state &state,
                    std::vector<jf::entities::EntityHandler> bonuses, 
                    std::vector<jf::entities::EntityHandler> players);
                
                static void focusLogic();
                static void tauntLogic(jf::components::ComponentHandler<indie::components::AIController> &component);
                static void powerupLogic(jf::components::ComponentHandler<indie::components::AIController> &component,
                                        jf::entities::EntityHandler &bonuses, jf::entities::EntityHandler &entity);
                static void searchLogic();

                static void askNewTarget(jf::components::ComponentHandler<indie::components::AIController> &component,
                                          jf::entities::EntityHandler &bonuses, jf::entities::EntityHandler entity);
                static bool hasMoved(jf::entities::EntityHandler entity, 
                    jf::components::ComponentHandler<indie::components::AIController> component);

            private:
                int _timePassed;
        };
    }
}

#endif /* !AISYSTEM_HPP_ */