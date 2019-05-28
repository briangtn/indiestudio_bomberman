/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** BombManagerSystem
*/

#include "BombManagerSystem.hpp"

indie::systems::BombManagerSystem::BombManagerSystem()
{

}

indie::systems::BombManagerSystem::~BombManagerSystem()
{

}

void indie::systems::BombManagerSystem::onAwake()
{

}

void indie::systems::BombManagerSystem::onStart()
{

}

void indie::systems::BombManagerSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    ECSWrapper ecs;

}

void indie::systems::BombManagerSystem::onTearDown()
{

}

void indie::systems::BombManagerSystem::createBomb(jf::components::ComponentHandler<components::Bomb> bomb,
jf::components::ComponentHandler<components::SoundComponent> sound,
jf::components::ComponentHandler<components::Particle> particle,
jf::components::ComponentHandler<components::Transform> tr)
{
    ECSWrapper ecs;

    auto bombEntity = ecs.entityManager.createEntity("bomb");
    auto bombTr = bombEntity->assignComponent<components::Transform, maths::Vector3D>({tr->getPosition().x, tr->getPosition().z, tr->getPosition().y});
    auto bombComponent = bombEntity->assignComponent<components::Bomb, int, float, components::BombType>(bomb->getStrength(), bomb->getTimeBeforeExplose(), bomb->getBombType());
    auto bombMesh = bombEntity->assignComponent<components::Mesh, std::string>(bombComponent->getTextureMesh());
    auto bombMat = bombEntity->assignComponent<components::Material, std::string>(bombComponent->getTexturePath());
    bombMat->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}