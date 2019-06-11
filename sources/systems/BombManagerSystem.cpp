/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** BombManagerSystem
*/

#include "systems/BombManagerSystem.hpp"

indie::systems::BombManagerSystem::BombManagerSystem()
{
    for (unsigned int s = indie::components::PlayerType::P1 ; s <= indie::components::PlayerType::P4 ; ++s)
        _NumberBombPlace[static_cast<indie::components::PlayerType>(s)] = 0;
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
    indie::maths::Vector3D vectLimit(-3, 1, 3);
    static bool pass = true;

    ecs.entityManager.applyToEach<components::Bomb>(
    [elapsedTime, &toDelete, this, vectLimit](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Bomb> bomb) {
        ECSWrapper ecs;
        if (bomb->getTimeBeforeExplose() <= 0) {
            if (pass == true) {
                this->displayParticle(bomb->getBombType(), bomb->getStrength(), vectLimit);
                this->playSoundExplosion(bomb->getBombType(), pass);
                this->removeBombPlace(bomb->getPlayerType());
            }
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
    auto player = ecs.entityManager.getEntityByName("player");

    auto playerPos = player->getComponent<indie::components::Transform>();
    auto bombEntity = ecs.entityManager.createEntity("bomb");
    std::cout << "position x = " << (std::floor((playerPos->getPosition().x / 10.0f)) * 10.0f + 5) << " position y = " << (std::floor((playerPos->getPosition().z / 10.0f)) * 10.0f + 5) << std::endl;
    auto bombTr = bombEntity->assignComponent<components::Transform, maths::Vector3D>({(std::floor((playerPos->getPosition().x - 10 / 2) / 10) * 10.0f + 5), playerPos->getPosition().y, (std::floor((playerPos->getPosition().z - 10 / 2) / 10) * 10 + 5)});
    bombTr->setScale({8, 8, 8});
    auto bombComponent = bombEntity->assignComponent<components::Bomb, int, float, components::BombType, components::PlayerType>(bomb->getStrength(), bomb->getTimeBeforeExplose(), bomb->getBombType(), bomb->getPlayerType());
    auto bombMesh = bombEntity->assignComponent<components::Mesh, std::string>(bombComponent->getTextureMesh());
    auto bombMat = bombEntity->assignComponent<components::Material, std::string>(bombComponent->getTexturePath());
    bombMat->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

void indie::systems::BombManagerSystem::displayParticle(indie::components::BombType typeBomb, const int &strength, indie::maths::Vector3D posLimit)
{
    ECSWrapper ecs;

    auto componentParticle = ecs.entityManager.createEntity("particle");
    componentParticle->assignComponent<components::DestroyOnTime, float>(1);
    auto normalParticle = componentParticle->assignComponent<components::Particle, const std::string>("NormalBombParticle");
    auto playerPos = ecs.entityManager.getEntityByName("bomb")->getComponent<indie::components::Transform>();
    if (typeBomb == 0) {
        std::cout << "Normal Particle" << std::endl;
    }
    else if (typeBomb == 1) {
        normalParticle->setEmitterSize(irr::core::aabbox3d<irr::f32>(-0.5, -0.3, -0.5, 0.5, 0.3, 0.5));
        normalParticle->setInitialDirection(irr::core::vector3df(0.010f,0.04f,0.010f));
        normalParticle->setEmitRate(std::make_pair(10, 9));
        normalParticle->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 0, 0, 0), irr::video::SColor(0,255,255,0)));
        normalParticle->setMinMaxAge(std::make_pair(1, 1));
        normalParticle->setAngle(0);
        normalParticle->setMinMaxSize(std::make_pair(irr::core::dimension2df(0.7f, 1.0f), irr::core::dimension2df(1.0f, 1.0f)));
        normalParticle->setTexture(0, "../Assets/Particle/PNG/flame_02.png");
        normalParticle->initParticle();
        normalParticle->setPosition(irr::core::vector3df(playerPos->getPosition().x, playerPos->getPosition().y, playerPos->getPosition().z + 10));
    }
    else if (typeBomb == 2) {
        normalParticle->setEmitterSize(irr::core::aabbox3d<irr::f32>(-0.5, -0.3, -0.5, 0.5, 0.3, 0.5));
        normalParticle->setInitialDirection(irr::core::vector3df(0.010f,0.04f,0.010f));
        normalParticle->setEmitRate(std::make_pair(10, 9));
        normalParticle->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 0, 0, 0), irr::video::SColor(0, 0, 168, 255)));
        normalParticle->setMinMaxAge(std::make_pair(1, 1));
        normalParticle->setAngle(0);
        normalParticle->setMinMaxSize(std::make_pair(irr::core::dimension2df(0.7f, 1.0f), irr::core::dimension2df(1.0f, 1.0f)));
        normalParticle->setTexture(0, "../Assets/Particle/PNG/circle_05.png");
        normalParticle->initParticle();
        normalParticle->setPosition(irr::core::vector3df(playerPos->getPosition().x, playerPos->getPosition().y, playerPos->getPosition().z + 10));
    }
    else if (typeBomb == 3) {
        auto bombPos = ecs.entityManager.getEntityByName("bomb")->getComponent<indie::components::Transform>();
        normalParticle->setEmitterSize(irr::core::aabbox3d<irr::f32>(-6, -7, -8, 6, 7, 8));
        normalParticle->setInitialDirection(irr::core::vector3df(0.010f,0.04f,0.010f));
        normalParticle->setEmitRate(std::make_pair(10, 9));
        normalParticle->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 0, 0, 0), irr::video::SColor(0,255,255,0)));
        normalParticle->setMinMaxAge(std::make_pair(15, 15));
        normalParticle->setAngle(0);
        normalParticle->setMinMaxSize(std::make_pair(irr::core::dimension2df(7.0f, 7.0f), irr::core::dimension2df(1.0f, 1.0f)));
        normalParticle->setTexture(0, "../Assets/Particle/PNG/spark_01.png");
        normalParticle->initParticle();
        normalParticle->setPosition(irr::core::vector3df(bombPos->getPosition().x, bombPos->getPosition().y, bombPos->getPosition().z));
    }
    else if (typeBomb == 4) {
        normalParticle->setEmitterSize(irr::core::aabbox3d<irr::f32>(-15, -13, -15, 15, 13, 15));
        normalParticle->setInitialDirection(irr::core::vector3df(0.010f,0.04f,0.010f));
        normalParticle->setEmitRate(std::make_pair(10, 9));
        normalParticle->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 0, 0, 0), irr::video::SColor(0, 232, 65, 24)));
        normalParticle->setMinMaxAge(std::make_pair(1, 1));
        normalParticle->setAngle(0);
        normalParticle->setMinMaxSize(std::make_pair(irr::core::dimension2df(0.7f, 1.0f), irr::core::dimension2df(1.0f, 1.0f)));
        normalParticle->setTexture(0, "../Assets/Particle/PNG/symbol_01.png");
        normalParticle->initParticle();
        normalParticle->setPosition(irr::core::vector3df(playerPos->getPosition().x, playerPos->getPosition().y, playerPos->getPosition().z + 10));
    }
    else {
        std::cout << "throw error : unknown type bomb" << std::endl;
    }
}

void indie::systems::BombManagerSystem::playSoundExplosion(indie::components::BombType typeBomb, bool &pass)
{
    ECSWrapper ecs;

    pass = false;
    auto componentMusic = ecs.entityManager.createEntity("sound");
    if (typeBomb == 0) {
        auto soundBomb = componentMusic->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("../Sound/BombSound/ExplosionSoundNormalBomb.ogg", components::SoundComponent::SoundType::EFFECT);
        soundBomb->setIsPaused(false);
    }
    else if (typeBomb == 1) {
        auto soundBomb = componentMusic->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("../Sound/BombSound/ExplosionSoundFireBomb.ogg", components::SoundComponent::SoundType::EFFECT);
        soundBomb->setIsPaused(false);
    }
    else if (typeBomb == 2) {
        auto soundBomb = componentMusic->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("../Sound/BombSound/ExplosionSoundWaterBomb.ogg", components::SoundComponent::SoundType::EFFECT);
        soundBomb->setIsPaused(false);
    }
    else if (typeBomb == 3) {
        auto soundBomb = componentMusic->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("../Sound/BombSound/ExplosionSoundElectricBomb.ogg", components::SoundComponent::SoundType::EFFECT);
        soundBomb->setIsPaused(false);
    }
    else if (typeBomb == 4) {
        auto soundBomb = componentMusic->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("../Sound/BombSound/ExplosionSoundLoveBomb.ogg", components::SoundComponent::SoundType::EFFECT);
        soundBomb->setIsPaused(false);
    }
    else {
        std::cout << "throw error : unknown type bomb" << std::endl;
    }
}

void indie::systems::BombManagerSystem::setNumberBombPlace(const int &newNumberBombPlace,const indie::components::PlayerType &newPlayerType)
{
    for (int s = indie::components::PlayerType::P1 ; s <= indie::components::PlayerType::P4 ; ++s)
        if (s == newPlayerType)
            _NumberBombPlace[static_cast<indie::components::PlayerType>(s)] = newNumberBombPlace;
}

unsigned int indie::systems::BombManagerSystem::getNumberBombPlacer(const indie::components::PlayerType &playerType) const
{
    for (auto &it : _NumberBombPlace)
        if (it.first == playerType)
            return it.second;
}

void indie::systems::BombManagerSystem::addBombPlace(indie::components::PlayerType playerType)
{
    _NumberBombPlace[playerType] += 1;
}

void indie::systems::BombManagerSystem::removeBombPlace(indie::components::PlayerType playerType)
{
    if (_NumberBombPlace[playerType] == 0)
        return;
   _NumberBombPlace[playerType] -= 1;
}