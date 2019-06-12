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
        
                static void chooseState(jf::components::ComponentHandler<indie::components::AIController> component);
                static void AILogic(jf::entities::EntityHandler entity,
    jf::components::ComponentHandler<indie::components::AIController> component);
            protected:
            private:
                int _timePassed;
        };
    }
}

#endif /* !AISYSTEM_HPP_ */