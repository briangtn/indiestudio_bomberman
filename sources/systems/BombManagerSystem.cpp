/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** BombManagerSystem
*/

#include "systems/BombManagerSystem.hpp"

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
    std::vector<jf::internal::ID> toDelete;    
    static bool pass = true;

    ecs.entityManager.applyToEach<components::Bomb>(
    [elapsedTime, &toDelete, this](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Bomb> bomb) {
        ECSWrapper ecs;
        if (bomb->getTimeBeforeExplose() <= 0) {
            if (pass == true)
                this->playSoundExplosion(bomb->getBombType(), pass);
            toDelete.emplace_back(bomb->getEntity()->getID());
        } else {
            bomb->setTimeBeforeExplose(bomb->getTimeBeforeExplose() - elapsedTime.count() / 1000000000.0f);
        }
        });
    pass = true;
    for (auto &id : toDelete)
        ecs.entityManager.deleteEntity(id);
}

void indie::systems::BombManagerSystem::onTearDown()
{

}

void indie::systems::BombManagerSystem::onStop()
{
    
}

void indie::systems::BombManagerSystem::createBomb(jf::components::ComponentHandler<components::Bomb> bomb,
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

void indie::systems::BombManagerSystem::displayParticle(indie::components::BombType typeBomb, const int &strength, const indie::maths::Vector3D &posLimit)
{

}

void indie::systems::BombManagerSystem::playSoundExplosion(indie::components::BombType typeBomb, bool &pass)
{
    ECSWrapper ecs;

    pass = false;
    auto componentMusic = ecs.entityManager.createEntity("sound");
    if (typeBomb == 0) {
        auto soundBomb = componentMusic->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("./Sound/BombSound/ExplosionSoundNormalBomb.ogg", components::SoundComponent::SoundType::EFFECT);
        soundBomb->setShouldBePlayed(true);
    }
    else if (typeBomb == 1) {
        auto soundBomb = componentMusic->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("./Sound/BombSound/ExplosionSoundFireBomb.ogg", components::SoundComponent::SoundType::EFFECT);
        soundBomb->setShouldBePlayed(true);
    }
    else if (typeBomb == 2) {
        auto soundBomb = componentMusic->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("./Sound/BombSound/ExplosionSoundWaterBomb.ogg", components::SoundComponent::SoundType::EFFECT);
        soundBomb->setShouldBePlayed(true);
    }
    else if (typeBomb == 3) {
        auto soundBomb = componentMusic->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("./Sound/BombSound/ExplosionSoundElectricBomb.ogg", components::SoundComponent::SoundType::EFFECT);
        soundBomb->setShouldBePlayed(true);
    }
    else if (typeBomb == 4) {
        auto soundBomb = componentMusic->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("./Sound/BombSound/ExplosionSoundLoveBomb.ogg", components::SoundComponent::SoundType::EFFECT);
        soundBomb->setShouldBePlayed(true);
    }
    else {
        std::cout << "throw error : unknown type bomb" << std::endl;
    }
}