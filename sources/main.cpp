/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** main.cpp
*/

/* Created the 09/05/2019 at 21:39 by jfrabel */

#include <iostream>
#include "IrrlichtManagerSystem.hpp"
#include "IrrlichtManagerExceptions.hpp"
#include "IrrlichtKeyInputEvent.hpp"
#include "IrrlichtMouseInputEvent.hpp"
#include "ECSWrapper.hpp"
#include "Exceptions.hpp"

int runBomberman()
{
    ECSWrapper ecs;
    ecs.systemManager.addSystem<jf::systems::IrrlichtManagerSystem>();
    ecs.systemManager.startSystem<jf::systems::IrrlichtManagerSystem>();
    ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().activateJoysticks();

    while (ecs.systemManager.getState<jf::systems::IrrlichtManagerSystem>() == jf::systems::AWAKING ||
           ecs.systemManager.getState<jf::systems::IrrlichtManagerSystem>() == jf::systems::STARTING ||
           ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().isWindowOpen()) {
        ecs.systemManager.tick();
        auto errors = ecs.systemManager.getErrors();
        if (!errors.empty()) {
            for (auto &err : errors) {
                std::cerr << "[ERROR] " << err.error << std::endl;
            }
            return 84;
        }
    }
    return 0;
}

int main()
{
    try {
        return runBomberman();
    } catch (const jf::ECSException &e) {
        std::cerr << "An error occurred while running the game: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "A standard error occurred while running the game: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while running the game." << std::endl;
    }
    return 84;
}