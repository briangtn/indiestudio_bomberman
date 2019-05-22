/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** main.cpp
*/

/* Created the 09/05/2019 at 21:39 by jfrabel */

#include <iostream>
#include "components/Material.hpp"
#include "components/Camera.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
#include "exceptions/IrrlichtManagerExceptions.hpp"
#include "events/IrrlichtKeyInputEvent.hpp"
#include "events/IrrlichtMouseInputEvent.hpp"
#include "ECSWrapper.hpp"
#include "components/ComponentParticle.hpp"
#include "Exceptions.hpp"

int runBomberman()
{
    ECSWrapper ecs;
    ecs.systemManager.addSystem<indie::systems::IrrlichtManagerSystem>();
    ecs.systemManager.startSystem<indie::systems::IrrlichtManagerSystem>();
    ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().activateJoysticks();
    ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().setFullScreenEnabled(false);

    auto cameraEntity = ecs.entityManager.createEntity("camera");
    auto cameraTr = cameraEntity->assignComponent<indie::components::Transform>();
    cameraTr->setPosition({0, 0, -20});
    cameraEntity->assignComponent<indie::components::Camera>();

    ecs.eventManager.addListener<jf::components::ComponentHandler<indie::components::Transform>, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_Q>>(&cameraTr, [](auto *tr, auto e) {
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
    ecs.eventManager.addListener<jf::components::ComponentHandler<indie::components::Transform>, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_D>>(&cameraTr, [](auto *tr, auto e) {
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
    ecs.eventManager.addListener<jf::components::ComponentHandler<indie::components::Transform>, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_Z>>(&cameraTr, [](auto *tr, auto e) {
        auto oldPos = (*tr)->getPosition();
        if (e.shiftActivated) {
            oldPos.y += 1;
        } else {
            oldPos.z += 1;
        }
        (*tr)->setPosition(oldPos);
    });
    ecs.eventManager.addListener<jf::components::ComponentHandler<indie::components::Transform>, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_S>>(&cameraTr, [](auto *tr, auto e) {
        auto oldPos = (*tr)->getPosition();
        if (e.shiftActivated) {
            oldPos.y -= 1;
        } else {
            oldPos.z -= 1;
        }
        (*tr)->setPosition(oldPos);
    });

    auto plEntity = ecs.entityManager.createEntity("pointLight");
    auto plTr = plEntity->assignComponent<indie::components::Transform>();
    plTr->setPosition({-1, -1, -1});
    plEntity->assignComponent<indie::components::PointLight>();

    auto cubeEntity = ecs.entityManager.createEntity("cube");
    auto tr2 = cubeEntity->assignComponent<indie::components::Transform>();
    cubeEntity->assignComponent<indie::components::Mesh, std::string>("../test_assets/cube.obj");
    auto mat = cubeEntity->assignComponent<indie::components::Material, std::string>("../test_assets/cube_texture.png");
    mat->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
    mat->setMaterialFlag(irr::video::EMF_LIGHTING, false);

    auto cubeEntity2 = ecs.entityManager.createEntity("cube");
    auto tr = cubeEntity2->assignComponent<indie::components::Transform>();
    tr->setPosition({10, 10, 10});
    tr->setScale({10, 10, 2});
    tr->setRotation({0, 0, 45});
    cubeEntity2->assignComponent<indie::components::Mesh, std::string>("../test_assets/cube.obj");
    auto mat2 = cubeEntity2->assignComponent<indie::components::Material, std::string>("../test_assets/cube_texture.png");
    mat2->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    mat2->setMaterialFlag(irr::video::EMF_WIREFRAME, true);

    auto particleSystemEntity = ecs.entityManager.createEntity("particleSystem");
    particleSystemEntity->assignComponent<indie::components::Transform, indie::maths::Vector3D>({0, 1, 0});
    auto sys = particleSystemEntity->assignComponent<indie::components::Particle, std::string>("p1");
    sys->setTexture(0, "../test_assets/particle_default.png");
    sys->setAngle(0);
    sys->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 255, 0, 0), irr::video::SColor(0, 0, 0, 255)));
    sys->setEmiterSize(irr::core::aabbox3df(-7, 0, -7, 7, 1, 7));
    sys->setEmitRate(std::make_pair(40, 80));
    sys->setFadeColor(irr::video::SColor(0, 0, 255, 0));
    sys->setFadeTime(1000);
    sys->setMinMaxAge(std::make_pair(800, 2000));
    sys->setMinMaxSize(std::make_pair(irr::core::dimension2d<irr::f32>(1, 1), irr::core::dimension2d<irr::f32>(2, 2)));
    sys->setInitialDirection(irr::core::vector3df(0.0f, 0.06f, 0.0f));

    while (ecs.systemManager.getState<indie::systems::IrrlichtManagerSystem>() == jf::systems::AWAKING ||
           ecs.systemManager.getState<indie::systems::IrrlichtManagerSystem>() == jf::systems::STARTING ||
           ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().isWindowOpen()) {
        ecs.systemManager.tick();

        auto crot = tr2->getRotation();
        tr2->setRotation({crot.x + 1, crot.y + 1, crot.z + 1});

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