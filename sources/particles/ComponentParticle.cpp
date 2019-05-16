/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** ComponentParticle
*/

#include "ComponentParticle.hpp"

jf::components::Particle::Particle(jf::entities::Entity &entity, const std::string &name)
    : Component(entity),
      _boxEmiterCreated(false),
      _affectorCreated(false),
      _isVisible(false),
      _particle(nullptr),
      _emitter(nullptr),
      _affector(nullptr),
      _texturePath(),
      _name(name)
{
    EMIT_CREATE(Particle);
}

jf::components::Particle::~Particle()
{
    EMIT_DELETE(Particle);
    _affector->drop();
    _emitter->drop();
    _particle->drop();
}

void jf::components::Particle::initParticle()
{
    if (_particle != nullptr)
        return; //TODO throw
    ECSWrapper ecs;
    auto sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
    if (sceneManager == nullptr)
        return; //TODO Throw
    _particle = sceneManager->addParticleSystemSceneNode(false);
    if (_particle == nullptr)
        return; //TODO throw
    _particle->setName(_name.c_str());
    _affector = _particle->createFadeOutParticleAffector();
    if (_affector == nullptr)
        return; //TODO throw
    _particle->addAffector(_affector);
    _particle->setVisible(_isVisible);
}

bool jf::components::Particle::isInit() const
{
    return _particle && _affector;
}

void jf::components::Particle::createBoxEmitter(irr::core::aabbox3d<irr::f32> emiterSize,\
irr::core::vector3df initialDirection, std::pair<int, int> emitRate, std::pair<irr::video::SColor,\
irr::video::SColor> darkBrightColor, std::pair<int, int> minMaxAge, int angle,\
std::pair<irr::core::dimension2df, irr::core::dimension2df> minMaxsize)
{
    if (_particle == nullptr)
        return; //TODO throw
    _emitter = _particle->createBoxEmitter(emiterSize, initialDirection,\
emitRate.first, emitRate.second, darkBrightColor.first, darkBrightColor.second, minMaxAge.first, minMaxAge.second,\
angle, minMaxsize.first, minMaxsize.second);
    if (_emitter == nullptr)
        return; //TODO throw
    _boxEmiterCreated = true;
}

const irr::scene::IParticleEmitter *jf::components::Particle::getEmitter() const
{
    return _emitter;
}

void jf::components::Particle::createFadeOutParticle(irr::video::SColor color, int time)
{
    if (_particle == nullptr)
        return; //TODO throw
    _affector = _particle->createFadeOutParticleAffector(color, time);
    if (_affector == nullptr)
        return; //TODO throw
    _affectorCreated = true;
}

void jf::components::Particle::activate()
{
    if (_affectorCreated == true)
        _particle->addAffector(_affector);
    else {
        if (_affector != nullptr) {
            _affector->drop();
            _affector = nullptr;
        }
    }
    if (_boxEmiterCreated == true)
        _particle->setEmitter(_emitter);
    else {
        if (_emitter != nullptr) {
            _emitter->drop();
            _emitter = nullptr;
        }
        throw jf::exceptions::IrrlichtParticleException("Impossible to print a particle without emitter.", "jf::components::Particle::createFadeOutParticle");
    }
    if (_boxEmiterCreated == true) {
        if (_particle != nullptr) {
            _isVisible = true;
            _particle->setVisible(_isVisible);
            _particle->render();
        }
    }
}

void jf::components::Particle::deactivate()
{
    if (_particle == nullptr)
        return; //TODO trhow
    _isVisible = false;
    _particle->setVisible(_isVisible);
}

std::string jf::components::Particle::getTexturePath() const
{
    return _texturePath;
}

irr::core::vector3df jf::components::Particle::getPosition() const
{
    if (_particle == nullptr)
        throw ; //TODO fix
    return _particle->getPosition();
}

void jf::components::Particle::setPosition(const irr::core::vector3df &newPos)
{
    if (_particle == nullptr)
        throw ; //TODO fix
    _particle->setPosition(newPos);
}

irr::core::vector3df jf::components::Particle::getScale() const
{
    if (_particle == nullptr)
        throw ; //TODO fix
    return _particle->getScale();
}

void jf::components::Particle::setScale(const irr::core::vector3df &newScale)
{
    if (_particle == nullptr)
        throw ; //TODO fix
    _particle->setScale(newScale);
}

irr::core::vector3df jf::components::Particle::getRotation() const
{
    if (_particle == nullptr)
        throw ; //TODO fix
    return _particle->getRotation();
}

void jf::components::Particle::setRotation(const irr::core::vector3df &newRotation)
{
    if (_particle == nullptr)
        throw ; //TODO fix
    _particle->setRotation(newRotation);
}

void jf::components::Particle::setTexture(int layer, const std::string &texturePath)
{
    ECSWrapper ecs;

    _texturePath = texturePath;
    if (_particle != nullptr) {
        auto videoDriver = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getVideoDriver();
        if (videoDriver != nullptr)
            _particle->setMaterialTexture(layer, videoDriver->getTexture(texturePath.c_str()));
    }
}

bool jf::components::Particle::getIsVisible() const
{
    return _isVisible;
}

std::string jf::components::Particle::getName() const
{
    return _name;
}

void jf::components::Particle::setName(const std::string &newName)
{
    _name = newName;
    if (_particle != nullptr)
        _particle->setName(_name.c_str());
}