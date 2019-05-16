/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** ComponentParticle
*/

#include "ComponentParticle.hpp"

jf::components::Particle::Particle(jf::entities::Entity &entity, std::string name)
    : Component(entity)
{
    ECSWrapper ecs;

    EMIT_CREATE(Particle);
    _particle =  ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager()->addParticleSystemSceneNode(false);
    _particle->setName(name.c_str());
    _affector = _particle->createFadeOutParticleAffector();
    _particle->addAffector(_affector);
    _affector->drop();
    _boxEmiterCreate = false;
    _affectorCreate = false;
    _particle->setVisible(false);
    _isVisible = false;
}

void jf::components::Particle::createBoxEmitter(jf::entities::Entity &entity, irr::core::aabbox3d<irr::f32> emiterSize,\
irr::core::vector3df initialDirection, std::pair<int, int> emitRate, std::pair<irr::video::SColor,\
irr::video::SColor> darkBrightColor, std::pair<int, int> minMaxAge, int angle,\
std::pair<irr::core::dimension2df, irr::core::dimension2df> minMaxsize)
{
    _emitter = _particle->createBoxEmitter(emiterSize, initialDirection,\
emitRate.first, emitRate.second, darkBrightColor.first, darkBrightColor.second, minMaxAge.first, minMaxAge.second,\
angle, minMaxsize.first, minMaxsize.second);
    _boxEmiterCreate = true;
}

const irr::scene::IParticleEmitter *jf::components::Particle::getEmitter() const
{
    return _particle->getEmitter();
}

void jf::components::Particle::createFadeOutParticle(irr::video::SColor color, int time)
{
    _affector = _particle->createFadeOutParticleAffector(color, time);
    _affectorCreate = true;
}

void jf::components::Particle::Activate()
{
    if (_affectorCreate == true)
        _particle->addAffector(_affector);
    else
        _affector->drop();
    if (_boxEmiterCreate == true)
        _particle->setEmitter(_emitter);
    else {
        _emitter->drop();
        throw jf::exceptions::IrrlichtParticleException("Impossible to create a particle without emitter.", "jf::components::Particle::createFadeOutParticle");
    }
    if (_boxEmiterCreate == true) {
        _particle->setVisible(true);
        _particle->render();
        _isVisible = true;
    }
}

void jf::components::Particle::Deactivate()
{
    _particle->setVisible(false);
    _isVisible = false;
}

std::string jf::components::Particle::getTexturePath() const
{
    return _texturePath;
}

irr::core::vector3df jf::components::Particle::getPosition() const
{
    return _particle->getPosition();
}

void jf::components::Particle::setPosition(irr::core::vector3df newPos)
{
    _particle->setPosition(newPos);
}

irr::core::vector3df jf::components::Particle::getScale() const
{
    return _particle->getScale();
}

void jf::components::Particle::setScale(irr::core::vector3df newScale)
{
    _particle->setScale(newScale);
}

irr::core::vector3df jf::components::Particle::getRotation() const
{
    return _particle->getRotation();
}

void jf::components::Particle::setRotation(irr::core::vector3df newRotation)
{
    _particle->setRotation(newRotation);
}

void jf::components::Particle::setTexture(int layer, std::string texturePath)
{
    ECSWrapper ecs;

    _texturePath = texturePath;
    _particle->setMaterialTexture(layer, ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getVideoDriver()->getTexture(texturePath.c_str()));
}

bool jf::components::Particle::getParticleVisible() const
{
    return _isVisible;
}

std::string jf::components::Particle::getName() const
{
    return _particle->getName();
}

void jf::components::Particle::setName(std::string newName)
{
    _particle->setName(newName.c_str());
}