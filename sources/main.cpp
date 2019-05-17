/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** main.cpp
*/

/* Created the 09/05/2019 at 21:39 by jfrabel */

#include <iostream>
#include "Camera.hpp"
#include "IrrlichtManagerSystem.hpp"
#include "IrrlichtManagerExceptions.hpp"
#include "IrrlichtKeyInputEvent.hpp"
#include "IrrlichtMouseInputEvent.hpp"
#include "ECSWrapper.hpp"
#include "ComponentParticle.hpp"
#include "Exceptions.hpp"

int runBomberman()
{
    ECSWrapper ecs;
    ecs.systemManager.addSystem<jf::systems::IrrlichtManagerSystem>();
    ecs.systemManager.startSystem<jf::systems::IrrlichtManagerSystem>();
    ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().activateJoysticks();
    ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().setFullScreenEnabled(false);

    auto cameraEntity = ecs.entityManager.createEntity("camera");
    auto cameraTr = cameraEntity->assignComponent<jf::components::Transform>();
    cameraTr->setPosition({0, 0, -20});
    cameraEntity->assignComponent<jf::components::Camera>();

    ecs.eventManager.addListener<jf::components::ComponentHandler<jf::components::Transform>, jf::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_Q>>(&cameraTr, [](auto *tr, auto e) {
        auto oldPos = (*tr)->getPosition();
        auto oldRot = (*tr)->getRotation();
        if (e.shiftActivated) {
            oldRot.y -= 1;
        } else {
            oldPos.x -= 1;
        }
        (*tr)->setPosition(oldPos);
        (*tr)->setRotation(oldRot);
    });
    ecs.eventManager.addListener<jf::components::ComponentHandler<jf::components::Transform>, jf::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_D>>(&cameraTr, [](auto *tr, auto e) {
        auto oldPos = (*tr)->getPosition();
        auto oldRot = (*tr)->getRotation();
        if (e.shiftActivated) {
            oldRot.y += 1;
        } else {
            oldPos.x += 1;
        }
        (*tr)->setPosition(oldPos);
        (*tr)->setRotation(oldRot);
    });
    ecs.eventManager.addListener<jf::components::ComponentHandler<jf::components::Transform>, jf::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_Z>>(&cameraTr, [](auto *tr, auto e) {
        auto oldPos = (*tr)->getPosition();
        if (e.shiftActivated) {
            oldPos.y += 1;
        } else {
            oldPos.z += 1;
        }
        (*tr)->setPosition(oldPos);
    });
    ecs.eventManager.addListener<jf::components::ComponentHandler<jf::components::Transform>, jf::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_S>>(&cameraTr, [](auto *tr, auto e) {
        auto oldPos = (*tr)->getPosition();
        if (e.shiftActivated) {
            oldPos.y -= 1;
        } else {
            oldPos.z -= 1;
        }
        (*tr)->setPosition(oldPos);
    });

    auto cubeEntity = ecs.entityManager.createEntity("cube");
    cubeEntity->assignComponent<jf::components::Transform>();
    cubeEntity->assignComponent<jf::components::Mesh, std::string>("cube.obj");

    auto cubeEntity2 = ecs.entityManager.createEntity("cube");
    auto tr = cubeEntity2->assignComponent<jf::components::Transform>();
    tr->setPosition({10, 10, 10});
    tr->setScale({10, 10, 2});
    tr->setRotation({0, 0, 45});
    cubeEntity2->assignComponent<jf::components::Mesh, std::string>("cube.obj");

    while (ecs.systemManager.getState<jf::systems::IrrlichtManagerSystem>() == jf::systems::AWAKING ||
           ecs.systemManager.getState<jf::systems::IrrlichtManagerSystem>() == jf::systems::STARTING ||
           ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().isWindowOpen()) {
        ecs.systemManager.tick();

        auto crot = tr->getRotation();
        tr->setRotation({crot.x + 1, crot.y + 1, crot.z + 1});

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