/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** BombManagerSystem
*/

#include "systems/BombManagerSystem.hpp"
#include "components/AIController.hpp"
#include "input/InputManager.hpp"
#include "exceptions/BombException.hpp"
#include "components/PlayerAlive.hpp"

indie::systems::BombManagerSystem::BombManagerSystem()
{
    for (unsigned int s = indie::components::PlayerType::P1 ; s <= indie::components::PlayerType::P4 ; ++s)
        _numberBombPlace[static_cast<indie::components::PlayerType>(s)] = 0;
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
    float elapsedTimeAsSeconds = elapsedTime.count() / 1000000000.0f;

    ecs.entityManager.applyToEach<components::PlayerController>(
        [&, elapsedTimeAsSeconds](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::PlayerController> pc) {

            if (pc->isPlacingBomb()) {
                pc->setBombPlacementTime(pc->getBombPlacementTime() - elapsedTimeAsSeconds);
                if (pc->getBombPlacementTime() <= 0.0f) {
                    pc->setBombPlacementTime(0.0f);
                    pc->setIsPlacingBomb(false);
                }
            }

            if (indie::InputManager::IsKeyPressed(pc->getBombPlacementButton()) && !pc->isPlacingBomb()) {
                pc->setIsPlacingBomb(true);
                createBomb(entity);
                pc->setBombPlacementTime(pc->getBombPlacementDuration());
                auto animator = entity->getComponent<components::Animator>();
                if (animator.isValid()) {
                    animator->setCurrentAnimation(pc->getBombPlacementAnimation());
                }
            }
        }
    );

    ecs.entityManager.applyToEach<components::Bomb>(
    [&elapsedTimeAsSeconds, &toDelete, this](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Bomb> bomb) {
        ECSWrapper ecs;
        if (bomb->getTimeBeforeExplode() <= 0) {
            if (pass == true) {
                this->displayParticle(bomb->getBombType(), indie::maths::Vector3D(bomb->getEntity()->getComponent<indie::components::Transform>()->getPosition()));
                this->handleCollide(bomb);                
                this->playSoundExplosion(bomb->getBombType(), pass);
                this->removeBombPlace(bomb->getPlayerType());
            }
            toDelete.emplace_back(bomb->getEntity()->getID());
        } else {
            this->shakeBomb(bomb);
            bomb->setTimeBeforeExplode(bomb->getTimeBeforeExplode() - elapsedTimeAsSeconds);
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

void indie::systems::BombManagerSystem::createBomb(jf::entities::EntityHandler playerEntity)
{
    ECSWrapper ecs;

    auto playerController = playerEntity->getComponent<indie::components::PlayerController>();
    auto aiController = playerEntity->getComponent<indie::components::AIController>();
    auto playerPos = playerEntity->getComponent<indie::components::Transform>();
    auto componentPlaceBomb = ecs.entityManager.createEntity("soundPlaceBomb");
    auto placeBombSound = componentPlaceBomb->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("../Sound/BombSound/PlaceBombSound.ogg", components::SoundComponent::SoundType::EFFECT);
    components::PlayerType ptype;
    int bombForce;
    int maxBomb;

    placeBombSound->setIsPaused(true);
    if (playerController.isValid()) {
        ptype = playerController->getPlayerType();
        bombForce = playerController->getBombForce();
        maxBomb = playerController->getMaxBomb();
    } else if (aiController.isValid()) {
        ptype = aiController->getPlayerType();
        bombForce = aiController->getBombForce();
        maxBomb = aiController->getMaxBomb();
    } else {
        return;
    }
    if (!(getNumberBombPlace(ptype) < maxBomb && checkBombPlace(playerPos->getPosition()) == true))
        return;
    auto bombEntity = ecs.entityManager.createEntity("bomb");
    placeBombSound->setIsPaused(false);
    auto bombTr = bombEntity->assignComponent<components::Transform, maths::Vector3D>({(std::floor((playerPos->getPosition().x - 10.0f / 2.0f) / 10.0f) * 10 + 10), playerPos->getPosition().y, (std::floor((playerPos->getPosition().z - 10.0f / 2.0f) / 10.0f) * 10 + 10)});
    bombTr->setScale({8, 8, 8});
    auto bombComponent = bombEntity->assignComponent<components::Bomb, int, float, components::BombType, components::PlayerType>(bombForce, 3, indie::components::NORMAL, ptype);
    auto bombMesh = bombEntity->assignComponent<components::Mesh, std::string>(bombComponent->getTextureMesh());
    auto bombMat = bombEntity->assignComponent<components::Material, std::string>(bombComponent->getTexturePath());
    bombEntity->assignComponent<indie::components::BoxCollider, indie::maths::Vector3D, indie::maths::Vector3D>({0.5f, 0.5f, 0.5f}, {0, 0, 0}, indie::BOMB_LAYER);
    bombMat->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    addBombPlace(ptype);
    componentPlaceBomb->assignComponent<components::DestroyOnTime, float>(1);
}

void indie::systems::BombManagerSystem::displayParticle(indie::components::BombType typeBomb, indie::maths::Vector3D vect)
{
    ECSWrapper ecs;

    auto componentParticle = ecs.entityManager.createEntity("particle");
    componentParticle->assignComponent<components::DestroyOnTime, float>(1);
    auto normalParticle = componentParticle->assignComponent<components::Particle, const std::string>("NormalBombParticle");
    if (typeBomb == 0) {
        normalParticle->setEmitterSize(irr::core::aabbox3d<irr::f32>(-6, -7, -8, 6, 7, 8));
        normalParticle->setInitialDirection(irr::core::vector3df(0.010f,0.04f,0.010f));
        normalParticle->setEmitRate(std::make_pair(10, 9));
        normalParticle->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 255, 90, 0), irr::video::SColor(0, 255, 90, 0)));
        normalParticle->setMinMaxAge(std::make_pair(15, 15));
        normalParticle->setAngle(0);
        normalParticle->setMinMaxSize(std::make_pair(irr::core::dimension2df(7.0f, 7.0f), irr::core::dimension2df(1.0f, 1.0f)));
        normalParticle->setTexture(0, "bomb_normal_particle_texture");
        normalParticle->initParticle();
        normalParticle->setPosition(irr::core::vector3df(vect.x, vect.y, vect.z));
    }
    else if (typeBomb == 1) {
        normalParticle->setEmitterSize(irr::core::aabbox3d<irr::f32>(-6, -7, -8, 6, 7, 8));
        normalParticle->setInitialDirection(irr::core::vector3df(0.010f,0.04f,0.010f));
        normalParticle->setEmitRate(std::make_pair(10, 9));
        normalParticle->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 0, 0, 0), irr::video::SColor(0,255,255,0)));
        normalParticle->setMinMaxAge(std::make_pair(15, 15));
        normalParticle->setAngle(0);
        normalParticle->setMinMaxSize(std::make_pair(irr::core::dimension2df(7.0f, 7.0f), irr::core::dimension2df(1.0f, 1.0f)));
        normalParticle->setTexture(0, "bomb_fire_particle_texture");
        normalParticle->initParticle();
        normalParticle->setPosition(irr::core::vector3df(vect.x, vect.y, vect.z));
    }
    else if (typeBomb == 2) {
        normalParticle->setEmitterSize(irr::core::aabbox3d<irr::f32>(-6, -7, -8, 6, 7, 8));
        normalParticle->setInitialDirection(irr::core::vector3df(0.010f,0.04f,0.010f));
        normalParticle->setEmitRate(std::make_pair(10, 9));
        normalParticle->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 0, 0, 0), irr::video::SColor(0, 0, 168, 255)));
        normalParticle->setMinMaxAge(std::make_pair(15, 15));
        normalParticle->setAngle(0);
        normalParticle->setMinMaxSize(std::make_pair(irr::core::dimension2df(7.0f, 7.0f), irr::core::dimension2df(1.0f, 1.0f)));
        normalParticle->setTexture(0, "bomb_water_particle_texture");
        normalParticle->initParticle();
        normalParticle->setPosition(irr::core::vector3df(vect.x, vect.y, vect.z));
    }
    else if (typeBomb == 3) {
        normalParticle->setEmitterSize(irr::core::aabbox3d<irr::f32>(-6, -7, -8, 6, 7, 8));
        normalParticle->setInitialDirection(irr::core::vector3df(0.010f,0.04f,0.010f));
        normalParticle->setEmitRate(std::make_pair(10, 9));
        normalParticle->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 0, 0, 0), irr::video::SColor(0,255,255,0)));
        normalParticle->setMinMaxAge(std::make_pair(15, 15));
        normalParticle->setAngle(0);
        normalParticle->setMinMaxSize(std::make_pair(irr::core::dimension2df(7.0f, 7.0f), irr::core::dimension2df(1.0f, 1.0f)));
        normalParticle->setTexture(0, "bomb_plasma_particle_texure");
        normalParticle->initParticle();
        normalParticle->setPosition(irr::core::vector3df(vect.x, vect.y, vect.z));
    }
    else if (typeBomb == 4) {
        normalParticle->setEmitterSize(irr::core::aabbox3d<irr::f32>(-6, -7, -8, 6, 7, 8));
        normalParticle->setInitialDirection(irr::core::vector3df(0.010f,0.04f,0.010f));
        normalParticle->setEmitRate(std::make_pair(10, 9));
        normalParticle->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 0, 0, 0), irr::video::SColor(0, 232, 65, 24)));
        normalParticle->setMinMaxAge(std::make_pair(15, 15));
        normalParticle->setAngle(0);
        normalParticle->setMinMaxSize(std::make_pair(irr::core::dimension2df(7.0f, 7.0f), irr::core::dimension2df(1.0f, 1.0f)));
        normalParticle->setTexture(0, "bomb_sexy_particle_texure");
        normalParticle->initParticle();
        normalParticle->setPosition(irr::core::vector3df(vect.x, vect.y, vect.z));
    }
    else
        throw indie::exceptions::BombException("Unknown Type Bomb.", "indie::systems::BombManagerSystem::DisplayParticle");
}

void indie::systems::BombManagerSystem::playSoundExplosion(indie::components::BombType typeBomb, bool &pass)
{
    ECSWrapper ecs;

    pass = false;
    auto componentMusic = ecs.entityManager.createEntity("sound");
    std::string soundPath = "";
    if (typeBomb == 0) {
        soundPath = "bomb_normal_sound";
    } else if (typeBomb == 1) {
        soundPath = "bomb_fire_sound";
    } else if (typeBomb == 2) {
        soundPath = "bomb_water_sound";
    }
    else if (typeBomb == 3) {
        soundPath = "bomb_plasma_sound";
    }
    else if (typeBomb == 4) {
        soundPath = "bomb_sexy_sound";
    }
    else
        throw indie::exceptions::BombException("Unknow Type Bomb.", "indie::systems::BombManagerSystem::playSoundExplosion");
    if (soundPath == "")
        throw indie::exceptions::BombException("Unknow sound Path.", "indie::systems::BombManagerSystem::playSoundExplosion");
    auto soundBomb = componentMusic->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>(soundPath, components::SoundComponent::SoundType::EFFECT);
    soundBomb->setIsPaused(false);
    componentMusic->assignComponent<components::DestroyOnTime>();
}

void indie::systems::BombManagerSystem::setNumberBombPlace(const int &newNumberBombPlace,const indie::components::PlayerType &newPlayerType)
{
    for (int s = indie::components::PlayerType::P1 ; s <= indie::components::PlayerType::P4 ; ++s)
        if (s == newPlayerType)
            _numberBombPlace[static_cast<indie::components::PlayerType>(s)] = newNumberBombPlace;
}

unsigned int indie::systems::BombManagerSystem::getNumberBombPlace(const indie::components::PlayerType &playerType) const
{
    for (auto &it : _numberBombPlace)
        if (it.first == playerType)
            return it.second;
    return 0;
}

void indie::systems::BombManagerSystem::addBombPlace(indie::components::PlayerType playerType)
{
    _numberBombPlace[playerType] += 1;
}

void indie::systems::BombManagerSystem::removeBombPlace(indie::components::PlayerType playerType)
{
    if (_numberBombPlace[playerType] == 0)
        return;
   _numberBombPlace[playerType] -= 1;
}

void indie::systems::BombManagerSystem::shakeBomb(jf::components::ComponentHandler<indie::components::Bomb> bomb)
{

}

void indie::systems::BombManagerSystem::handleCollide(jf::components::ComponentHandler<indie::components::Bomb> bomb)
{
    ECSWrapper ecs;
    auto bombTr = bomb->getEntity()->getComponent<indie::components::Transform>();
    indie::maths::Vector3D initialVect = {bombTr->getPosition().x, bombTr->getPosition().y, bombTr->getPosition().z};
    indie::maths::Vector3D vect = initialVect;

    /* check pos bomb side */

    checkIsCollide(initialVect);

    /* check in right side */
    for (int i = 0 ; i < bomb->getStrength() ; ++i) {
        vect.x  = vect.x - 10;
        auto col = checkIsCollide(vect);
        if (col == 1)
            break;
        else if (col == 2) {
            this->displayParticle(bomb->getBombType(), vect);
            break;
        }
        else
            this->displayParticle(bomb->getBombType(), vect);
    } 

    vect = initialVect;

    /* check in left side */
    for (int i = 0 ; i < bomb->getStrength() ; ++i) {
        vect.x = vect.x + 10;
        auto col = checkIsCollide(vect);
        if (col == 1)
            break;
        else if (col == 2) {
            this->displayParticle(bomb->getBombType(), vect);
            break;
        }
        else
            this->displayParticle(bomb->getBombType(), vect);
    }

    vect = initialVect;

    /* check in up side */
    for (int i = 0 ; i < bomb->getStrength() ; ++i) {
        vect.z = vect.z - 10;
        auto col = checkIsCollide(vect);
        if (col == 1)
            break;
        else if (col == 2) {
            this->displayParticle(bomb->getBombType(), vect);
            break;
        }
        else
            this->displayParticle(bomb->getBombType(), vect);
    }

    vect = initialVect;

    /* check in down side */
    for (int i = 0 ; i < bomb->getStrength() ; ++i) {
        vect.z = vect.z + 10;
        auto col = checkIsCollide(vect);
        if (col == 1)
            break;
        else if (col == 2) {
            this->displayParticle(bomb->getBombType(), vect);
            break;
        }
        else
            this->displayParticle(bomb->getBombType(), vect);
    }
}

int indie::systems::BombManagerSystem::checkIsCollide(indie::maths::Vector3D vect)
{
    ECSWrapper ecs;

    auto entitiesWithCollider = ecs.entityManager.getEntitiesWith<components::BoxCollider>();

    indie::maths::Vector3D positionHitBox = {vect.x, vect.y, vect.z};
    indie::maths::Vector3D scaleHitBox = {3, 3, 3};
    indie::maths::Vector3D rotationHitBox = {0, 0, 0};

    indie::maths::OBB hitBoxOBB(positionHitBox, scaleHitBox, indie::maths::Matrix3::Rotation(rotationHitBox.x, rotationHitBox.y, rotationHitBox.z));

    int ret = 0;

    for (auto &entity : entitiesWithCollider) {

        auto collider = entity->getComponent<components::BoxCollider>();
        
        auto tr = entity->getComponent<components::Transform>();

        indie::maths::Vector3D position;
        indie::maths::Vector3D scale = {1, 1, 1};
        indie::maths::Vector3D rotation;

        if (tr.isValid()) {
            position = tr->getPosition();
            scale = tr->getScale();
            rotation = tr->getRotation();
        }

        indie::maths::OBB obb(position + collider->getOffset(), scale * collider->getSize(), maths::Matrix3::Rotation(rotation.x, rotation.y, rotation.z));

        if (obb.collides(hitBoxOBB)) {
            if ((collider->getLayer() & UNBREAKABLE_BLOCK_LAYER) && !(collider->getLayer() & ~UNBREAKABLE_BLOCK_LAYER))
                ret = ret != 1 ? 1 : ret;
            else if (((collider->getLayer() & BOMB_LAYER) && !(collider->getLayer() & ~BOMB_LAYER))) {
                collider->getEntity()->getComponent<indie::components::Bomb>()->setTimeBeforeExplode(0);
                ret = ret == 0 ? 2 : ret;
            } else if ((collider->getLayer() & BREAKABLE_BLOCK_LAYER) && !(collider->getLayer() & ~BREAKABLE_BLOCK_LAYER)) {
                ecs.entityManager.safeDeleteEntity(entity->getID());
                ecs.eventManager.emit<indie::events::AskingForBonusSpawnEvent>({position, components::BonusSpawner::BONUS_SPAWNER_T_RANDOM, components::BONUS_T_NB});
                auto componentBoxMusic = ecs.entityManager.createEntity("soundBox");
                auto BoxSound = componentBoxMusic->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("../Sound/BoxSound/BoxBreakSound.ogg", components::SoundComponent::SoundType::EFFECT);
                BoxSound->setIsPaused(false);
                componentBoxMusic->assignComponent<components::DestroyOnTime, float>(5);
                ret = ret == 0 ? 2 : ret;
            } else if ((collider->getLayer() & PLAYER_LAYER)) {
                auto componentDeathMusic = ecs.entityManager.createEntity("soundDeath");
                auto DeathSound = componentDeathMusic->assignComponent<components::SoundComponent, std::string, components::SoundComponent::SoundType>("../Sound/PlayerSound/DeathPlayerSound.ogg", components::SoundComponent::SoundType::EFFECT);
                DeathSound->setIsPaused(false);
                componentDeathMusic->assignComponent<components::DestroyOnTime, float>(3);
                auto playerLiveComponent = entity->getComponent<components::PlayerAlive>();
                if (playerLiveComponent.isValid()) {
                    playerLiveComponent->setLives(playerLiveComponent->getLives() - 1);
                } else {
                    std::cerr << "Player " << entity->getName() << " was hit by a bomb but has no component PlayerAlive" << std::endl;
                }
            } else {
                ecs.entityManager.safeDeleteEntity(entity->getID());
            }
        }
    }
    return ret;
}

bool indie::systems::BombManagerSystem::checkBombPlace(indie::maths::Vector3D vect)
{
    ECSWrapper ecs;

    auto entitiesWithCollider = ecs.entityManager.getEntitiesWith<components::BoxCollider>();

    indie::maths::Vector3D positionHitBox = {vect.x, vect.y, vect.z};
    indie::maths::Vector3D scaleHitBox = {0, 0, 0};
    indie::maths::Vector3D rotationHitBox = {0, 0, 0};

    indie::maths::OBB hitBoxOBB(positionHitBox, scaleHitBox, indie::maths::Matrix3::Rotation(rotationHitBox.x, rotationHitBox.y, rotationHitBox.z));

    for (auto &entity : entitiesWithCollider) {

        auto collider = entity->getComponent<components::BoxCollider>();
        
        auto tr = entity->getComponent<components::Transform>();

        indie::maths::Vector3D position;
        indie::maths::Vector3D scale = {1, 1, 1};
        indie::maths::Vector3D rotation;

        if (tr.isValid()) {
            position = tr->getPosition();
            scale = tr->getScale();
            rotation = tr->getRotation();
        }

        indie::maths::OBB obb(position + collider->getOffset(), scale * collider->getSize(), maths::Matrix3::Rotation(rotation.x, rotation.y, rotation.z));

        if (obb.collides(hitBoxOBB)) {
            if ((collider->getLayer() & BOMB_LAYER) && !(collider->getLayer() & ~BOMB_LAYER))
                return false;
            else if (collider->getLayer() & BREAKABLE_BLOCK_LAYER && !(collider->getLayer() & ~BREAKABLE_BLOCK_LAYER))
                return false;
        }
    }
    return true;
}