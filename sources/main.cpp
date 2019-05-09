/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** main.cpp
*/

/* Created the 09/05/2019 at 21:39 by jfrabel */

#include <IrrlichtRendererSystem.hpp>
#include "ECSWrapper.hpp"

int main()
{
    ECSWrapper ecs;
    ecs.systemManager.addSystem<jf::systems::IrrlichtRendererSystem>();
    ecs.systemManager.startSystem<jf::systems::IrrlichtRendererSystem>();

    while (ecs.systemManager.getState<jf::systems::IrrlichtRendererSystem>() != jf::systems::RUNNING ||
           ecs.systemManager.getSystem<jf::systems::IrrlichtRendererSystem>().isWindowOpen()) {
        ecs.systemManager.tick();
    }
    return 0;
}