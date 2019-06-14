/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** BonusSystem.cpp
*/

/* Created the 05/06/2019 at 21:59 by jfrabel */

#include "components/PlayerController.hpp"
#include "components/Transform.hpp"
#include "components/Rotator.hpp"
#include "components/Hoverer.hpp"
#include "components/Mesh.hpp"
#include "components/BoxCollider.hpp"
#include "ECSWrapper.hpp"
#include "systems/BonusSystem.hpp"
#include "events/AskingForBonusSpawnEvent.hpp"
#include "components/AIController.hpp"
#include "components/DestroyOnTime.hpp"

const std::map<indie::components::BonusType, indie::systems::BonusSystem::BonusFunction> indie::systems::BonusSystem::_bonusAffectorMap = {
    {components::BONUS_T_BOMB_UP, BonusSystem::BombUpAffector},
    {components::BONUS_T_FIRE_UP, BonusSystem::FireUpAffector},
    {components::BONUS_T_SPEED_UP, BonusSystem::SpeedUpAffector},
    {components::BONUS_T_WALL_PASS, BonusSystem::WallPassAffector},
};

const std::map<indie::components::BonusType, float> indie::systems::BonusSystem::_bonusDistributionRate = {
    {components::BONUS_T_BOMB_UP, 15.0f},
    {components::BONUS_T_FIRE_UP, 15.0f},
    {components::BONUS_T_SPEED_UP, 15.0f},
    {components::BONUS_T_WALL_PASS, 2.5f},
};

const std::map<indie::components::BonusType, std::pair<std::string, std::string>> indie::systems::BonusSystem::_bonusModelMap = {
    {components::BONUS_T_BOMB_UP, {"../test_assets/Items/bombUpItem.b3d", "../test_assets/Items/itemTex.png"}},
    {components::BONUS_T_FIRE_UP, {"../test_assets/Items/fireUpItem.b3d", "../test_assets/Items/itemTex.png"}},
    {components::BONUS_T_SPEED_UP, {"../test_assets/Items/speedUpItem.b3d", "../test_assets/Items/itemTex.png"}},
    {components::BONUS_T_WALL_PASS, {"../test_assets/Items/wallPassItem.b3d", "../test_assets/Items/itemTex.png"}},
};

indie::systems::BonusSystem::BonusSystem()
    : _bonusSpawnerDestroyedEventListenerID(),
      _re(time(nullptr)),
      _distribution(0.0f, 100.0f)
{

}

indie::systems::BonusSystem::~BonusSystem()
{

}

void indie::systems::BonusSystem::onAwake()
{

}

void indie::systems::BonusSystem::onStart()
{
    ECSWrapper ecs;
    _bonusSpawnerDestroyedEventListenerID = ecs.eventManager.addListener<BonusSystem, events::AskingForBonusSpawnEvent>(
        this,
        [](BonusSystem *system, events::AskingForBonusSpawnEvent e) {
            components::BonusType bonusType = e.optionalBonusType;
            if (e.spawnType == components::BonusSpawner::BONUS_SPAWNER_T_RANDOM)
                bonusType = system->getRandomType();
            if (bonusType != components::BONUS_T_NB)
                system->spawnNewPowerUp(bonusType, e.eventPosition, {10, 10, 10});
        }
    );
}

void indie::systems::BonusSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    ECSWrapper ecs;
    ecs.entityManager.applyToEach<components::BonusEffector, components::BoxCollider>(
        [ecs](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::BonusEffector> bonus, jf::components::ComponentHandler<components::BoxCollider> collider) {
            auto collisions = collider->getCollisions(true);
            components::BonusType type;
            for (auto &collision : collisions) {
                type = bonus->getType();
                if (_bonusAffectorMap.find(type) != _bonusAffectorMap.end() && _bonusAffectorMap.at(type)(collision, bonus)) {
                    ecs.entityManager.safeDeleteEntity(entity->getID());
                    return;
                }
            }
        }
    );
}

void indie::systems::BonusSystem::onStop()
{
    ECSWrapper ecs;
    ecs.eventManager.removeListener(_bonusSpawnerDestroyedEventListenerID);
}

void indie::systems::BonusSystem::onTearDown()
{

}

jf::entities::EntityHandler indie::systems::BonusSystem::spawnNewPowerUp(
    indie::components::BonusType bonusType,
    const maths::Vector3D &pos,
    const maths::Vector3D &scale)
{
    ECSWrapper ecs;
    auto newPowerUp = ecs.entityManager.createEntity("powerUp");
    newPowerUp->assignComponent<components::Transform, maths::Vector3D, maths::Vector3D, maths::Vector3D>(pos, {0, 0, 0}, scale);
    newPowerUp->assignComponent<components::BoxCollider, maths::Vector3D, maths::Vector3D, uint64_t>({0.5, 0.5, 0.5}, {0, 0, 0}, 0);
    newPowerUp->assignComponent<components::Rotator, maths::Vector3D>({0, 45, 0});
    newPowerUp->assignComponent<components::Hoverer, maths::Vector3D, maths::Vector3D>({0, 0.75, 0}, {0, 0.25f * scale.y, 0});
    newPowerUp->assignComponent<components::BonusEffector, components::BonusType>(bonusType);
    newPowerUp->assignComponent<components::Mesh, std::string>(_bonusModelMap.at(bonusType).first);
    auto mat = newPowerUp->assignComponent<indie::components::Material, std::string>(_bonusModelMap.at(bonusType).second);
    mat->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
    mat->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    return newPowerUp;
}

bool indie::systems::BonusSystem::BombUpAffector(
    jf::entities::EntityHandler affectTo,
    jf::components::ComponentHandler<indie::components::BonusEffector> &effector)
{
    ECSWrapper ecs;
    auto pc = affectTo->getComponent<components::PlayerController>();
    auto aic = affectTo->getComponent<components::AIController>();
    auto componentSound = ecs.entityManager.createEntity("soundBonus");
    componentSound->assignComponent<components::DestroyOnTime, float>(10);
    auto getBonusSound = componentSound->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("../Sound/BonusSound/BonusBombSound.ogg", components::SoundComponent::SoundType::EFFECT);
    

    getBonusSound->setIsPaused(true);
    if (pc.isValid()) {
        getBonusSound->setIsPaused(false);
        pc->setMaxBomb(pc->getMaxBomb() + _maxBombAdded);
        return true;
    } else if (aic.isValid()) {
        getBonusSound->setIsPaused(false);
        aic->setMaxBomb(aic->getMaxBomb() + _maxBombAdded);
        return true;
    }
    return false;
}

bool indie::systems::BonusSystem::FireUpAffector(
    jf::entities::EntityHandler affectTo,
    jf::components::ComponentHandler<indie::components::BonusEffector> &effector)
{
    ECSWrapper ecs;
    auto pc = affectTo->getComponent<components::PlayerController>();
    auto aic = affectTo->getComponent<components::AIController>();
    auto componentSound = ecs.entityManager.createEntity("soundBonus");
    componentSound->assignComponent<components::DestroyOnTime, float>(10);
    auto getBonusSound = componentSound->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("../Sound/BonusSound/BonusFireUpSound.ogg", components::SoundComponent::SoundType::EFFECT);

    getBonusSound->setIsPaused(true);
    if (pc.isValid() && pc->getBombForce() < _maxFireUp) {
        getBonusSound->setIsPaused(false);
        pc->setBombForce(pc->getBombForce() + _bombTileAdded);
        return true;
    } else if (aic.isValid() && aic->getBombForce() < _maxFireUp) {
        getBonusSound->setIsPaused(false);
        aic->setBombForce(aic->getBombForce() + _bombTileAdded);
        return true;
    }
    return false;
}

bool indie::systems::BonusSystem::SpeedUpAffector(
    jf::entities::EntityHandler affectTo,
    jf::components::ComponentHandler<indie::components::BonusEffector> &effector)
{
    ECSWrapper ecs;
    auto pc = affectTo->getComponent<components::PlayerController>();
    auto aic = affectTo->getComponent<components::AIController>();
    auto componentSound = ecs.entityManager.createEntity("soundBonus");
    componentSound->assignComponent<components::DestroyOnTime, float>(10);
    auto getBonusSound = componentSound->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("../Sound/BonusSound/BonusSpeedSound.ogg", components::SoundComponent::SoundType::EFFECT);

    getBonusSound->setIsPaused(true);
    if (pc.isValid() && pc->getMovementSpeed() < _maxSpeed) {
        getBonusSound->setIsPaused(false);
        pc->setMovementSpeed(pc->getMovementSpeed() + _speedAdded);
        return true;
    } else if (aic.isValid() && aic->getMovementSpeed() < _maxSpeed) {
        getBonusSound->setIsPaused(false);
        aic->setMovementSpeed(aic->getMovementSpeed() + _speedAdded);
        return true;
    }
    return false;
}

bool indie::systems::BonusSystem::WallPassAffector(
    jf::entities::EntityHandler affectTo,
    jf::components::ComponentHandler<indie::components::BonusEffector> &effector)
{
    ECSWrapper ecs;
    auto pc = affectTo->getComponent<components::PlayerController>();
    auto aic = affectTo->getComponent<components::AIController>();
    auto collider = affectTo->getComponent<components::BoxCollider>();
    auto componentSound = ecs.entityManager.createEntity("soundBonus");
    componentSound->assignComponent<components::DestroyOnTime, float>(10);
    auto getBonusSound = componentSound->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("../Sound/BonusSound/BonusWallPassSound.ogg", components::SoundComponent::SoundType::EFFECT);

    getBonusSound->setIsPaused(true);
    if (pc.isValid() && collider.isValid()) {
        getBonusSound->setIsPaused(false);
        collider->setLayer(collider->getLayer() & ~BREAKABLE_BLOCK_LAYER);
        return true;
    } else if (aic.isValid() && collider.isValid()) {
        getBonusSound->setIsPaused(false);
        collider->setLayer(collider->getLayer() & ~BREAKABLE_BLOCK_LAYER);
        return true;
    }
    return false;
}

indie::components::BonusType indie::systems::BonusSystem::getRandomType()
{
    float randomNb = _distribution(_re);
    float currMin = 0.0f;
    float currMax = 0.0f;
    for (auto &distrib : _bonusDistributionRate) {
        currMax += distrib.second;
        if (randomNb >= currMin && randomNb < currMax)
            return distrib.first;
        currMin = currMax;
    }
    return components::BONUS_T_NB;
}
