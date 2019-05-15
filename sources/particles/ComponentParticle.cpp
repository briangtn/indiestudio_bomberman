/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** ComponentParticle
*/

#include "ComponentParticle.hpp"

jf::Particle::Particle(jf::entities::Entity &entity, std::string name)
    : Component(entity)
{
    ECSWrapper ecs;

    EMIT_CREATE(Particle);
    _particle =  ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager()->addParticleSystemSceneNode(false);
    _particleName = name;
    _affector = _particle->createFadeOutParticleAffector();
    _particle->addAffector(_affector);
    _affector->drop();
    _boxEmiterCreate = false;
    _affectorCreate = false;
    _particle->setVisible(false);
    _isVisible = false;
}

void jf::Particle::createBoxEmitter(jf::entities::Entity &entity, irr::core::aabbox3d<irr::f32> emiterSize,\
irr::core::vector3df initialDirection, std::pair<int, int> emitRate, std::pair<irr::video::SColor,\
irr::video::SColor> darkBrightColor, std::pair<int, int> minMaxAge, int angle,\
std::pair<irr::core::dimension2df, irr::core::dimension2df> minMaxsize)
{
    _emitter = _particle->createBoxEmitter(emiterSize, initialDirection,\
emitRate.first, emitRate.second, darkBrightColor.first, darkBrightColor.second, minMaxAge.first, minMaxAge.second,\
angle, minMaxsize.first, minMaxsize.second);
    _boxEmiterCreate = true;
}

void jf::Particle::createFadeOutParticle(irr::video::SColor color, int time)
{
    _affector = _particle->createFadeOutParticleAffector(color, time);
    _affectorCreate = true;
}

void jf::Particle::Activate()
{
    if (_affectorCreate == true)
        _particle->addAffector(_affector);
    else {
        _affector->drop();
        std::cout << "throw error" << std::endl;
    }
    if (_boxEmiterCreate == true)
        _particle->setEmitter(_emitter);
    else {
        _emitter->drop();
        std::cout << "throw error" << std::endl;
    }
    _particle->setVisible(true);
    _isVisible = true;
}

void jf::Particle::Deactivate()
{
    _particle->setVisible(false);
    _isVisible = false;
}

std::string jf::Particle::getTexturePath() const
{
    return _texturePath;
}

void jf::Particle::setTextureName(int layer, std::string texturePath)
{
    _texturePath = texturePath;
//    _particle->setMaterialTexture(layer, irr::video::SMaterial::setTexture(texturePath));
}

bool jf::Particle::getParticleVisible() const
{
    return _isVisible;
}

std::string jf::Particle::getName() const
{
    return _particleName;
}

void jf::Particle::setName(std::string newName)
{
    _particleName = newName;
}