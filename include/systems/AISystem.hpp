/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** AISystem
*/

#ifndef AISYSTEM_HPP_
#define AISYSTEM_HPP_

#include "System.hpp"

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
            protected:
            private:
                int _timePassed;
        };
    }
}

#endif /* !AISYSTEM_HPP_ */