/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** Bombe
*/

#ifndef BOMBE_HPP_
#define BOMBE_HPP_

#include <iostream>
#include <irrlicht.h>
#include "Component.hpp"
#include "ComponentCreatedEvent.hpp"
#include "ECSWrapper.hpp"
#include "systems/IrrlichtManagerSystem.hpp" 


namespace indie {
    namespace components {
        class Bombe : public jf::components::Component {
        public:

            /* Bombe Constructor */

            Bombe();

            /* Bombe Destructor */

            ~Bombe();

            protected:
            private:
        };
    }
}

#endif /* !BOMBE_HPP_ */
