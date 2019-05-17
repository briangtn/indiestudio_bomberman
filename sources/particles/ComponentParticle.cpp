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
      _name(name),
      _emiterSizeInitialize(false),
      _initialDirectionInitialize(false),
      _emitRateInitialize(false),
      _darkBrightColorInitialize(false),
      _minMaxAgeInitialize(false),
      _angleInitialize(false),
      _minMaxSizeInitialize(false),
      _fadeColorInitialize(false),
      _fadeTimeInitialize(false)
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

bool jf::components::Particle::isEmitterInit() const
{
    if (_emiterSizeInitialize == true && _initialDirectionInitialize == true &&\
_emitRateInitialize == true && _darkBrightColorInitialize == true &&\
_minMaxAgeInitialize == true && _angleInitialize == true && _minMaxSizeInitialize == true)
        return true;
    else
        return false;
}

bool jf::components::Particle::isAffectorInit() const
{
    if (_fadeColorInitialize == true && _fadeTimeInitialize == true)
        return true;
    else
        return false;
}

void jf::components::Particle::initParticle()
{
    if (_particle != nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::initParticle");
    ECSWrapper ecs;
    auto sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
    if (sceneManager == nullptr)
        throw jf::exceptions::IrrlichtParticleException("sceneManager not init.", "jf::components::Particle::initParticle");
    _particle = sceneManager->addParticleSystemSceneNode(false);
    if (_particle == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::initParticle");
    _particle->setName(_name.c_str());
    _affector = _particle->createFadeOutParticleAffector();
    if (_affector == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Affector not init.", "jf::components::Particle::initParticle");
    _particle->addAffector(_affector);
    _particle->setVisible(_isVisible);
    if (isEmitterInit() == true)
        createBoxEmitter();
    else
        throw jf::exceptions::IrrlichtParticleException("Emitter Not Init Can't init Particle.", "jf::components::Particle::initParticle");
    if (isAffectorInit() == true)
        createFadeOutParticle();
    else
        throw jf::exceptions::IrrlichtParticleException("Affector Not inir Can't init Particle.", "jf::components::Particle::initParticle");
}

bool jf::components::Particle::isInit() const
{
    return _particle && _affector;
}

void jf::components::Particle::createBoxEmitter()
{
    if (_particle == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::createBoxEmitter");    
    _emitter = _particle->createBoxEmitter(_emiterSize, _initialDirection,\
_emitRate.first, _emitRate.second, _darkBrightColor.first, _darkBrightColor.second, _minMaxAge.first, _minMaxAge.second,\
_angle, _minMaxSize.first, _minMaxSize.second);
    if (_emitter == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Emitter not init.", "jf::components::Particle::createBoxEmitter");
    _boxEmiterCreated = true;
}

const irr::scene::IParticleEmitter *jf::components::Particle::getEmitter() const
{
    return _emitter;
}

irr::core::aabbox3d<irr::f32> jf::components::Particle::getEmiterSize() const
{
    return _emiterSize;
}

void jf::components::Particle::setEmiterSize(const irr::core::aabbox3d<irr::f32> &newEmiterSize)
{
    _emiterSize = newEmiterSize;
    _emiterSizeInitialize = true;
}

irr::core::vector3df jf::components::Particle::getInitialDirection() const
{
    return _initialDirection;
}

void jf::components::Particle::setInitialDirection(const irr::core::vector3df &newInitialDirection)
{
    _initialDirection = newInitialDirection;
    _initialDirectionInitialize = true;
}

 std::pair<int, int> jf::components::Particle::getEmitRate() const
 {
     return _emitRate;
 }

 void jf::components::Particle::setEmitRate(const std::pair<int, int> &newEmitRate)
 {
     _emitRate = newEmitRate;
     _emitRateInitialize = true;
 }

std::pair<irr::video::SColor, irr::video::SColor> jf::components::Particle::getDarkBrightColor() const
{
    return _darkBrightColor;
}

void jf::components::Particle::setDarkBrightColor(const std::pair<irr::video::SColor, irr::video::SColor> &newDarkBrightColor)
{
    _darkBrightColor = newDarkBrightColor;
    _darkBrightColorInitialize = true;
}

std::pair<int, int> jf::components::Particle::getMinMaxAge() const
{
    return _minMaxAge;
}

void jf::components::Particle::setMinMaxAge(const std::pair<int, int> &newMinMaxAge)
{
    _minMaxAge = newMinMaxAge;
    _minMaxAgeInitialize = true;
}

 int jf::components::Particle::getAngle() const
 {
     return _angle;
 }

 void jf::components::Particle::setAngle(const int &newAngle)
 {
     _angle = newAngle;
     _angleInitialize = true;
 }

std::pair<irr::core::dimension2df, irr::core::dimension2df> jf::components::Particle::getMinMaxSize() const
{
    return _minMaxSize;
}

void jf::components::Particle::setMinMaxSize(const std::pair<irr::core::dimension2df, irr::core::dimension2df> &newMinMaxSize)
{
    _minMaxSize = _minMaxSize;
    _minMaxSizeInitialize = true;
}

 void jf::components::Particle::createFadeOutParticle()
{
    if (_particle == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::createFadeOutParticle");
    _affector = _particle->createFadeOutParticleAffector(_fadeColor, _fadeTime);
    if (_affector == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Affector not init.", "jf::components::Particle::createFadeOutParticle");
    _affectorCreated = true;
}

irr::video::SColor jf::components::Particle::getFadeColor() const
{
    return _fadeColor;
}

void jf::components::Particle::setFadeColor(const irr::video::SColor &newFadeColor)
{
    _fadeColor = newFadeColor;
    _fadeColorInitialize = true;
}

int jf::components::Particle::getFadeTime() const
{
    return _fadeTime;
}

void jf::components::Particle::setFadeTime(const int &newFadeTime)
{
    _fadeTime = newFadeTime;
    _fadeTimeInitialize = true;
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
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::deactivate");    
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
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::getPosition");    
    return _particle->getPosition();
}

void jf::components::Particle::setPosition(const irr::core::vector3df &newPos)
{
    if (_particle == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::setPosition");
    _particle->setPosition(newPos);
}

irr::core::vector3df jf::components::Particle::getScale() const
{
    if (_particle == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::getScale");
    return _particle->getScale();
}

void jf::components::Particle::setScale(const irr::core::vector3df &newScale)
{
    if (_particle == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::setScale");
    _particle->setScale(newScale);
}

irr::core::vector3df jf::components::Particle::getRotation() const
{
    if (_particle == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::getRotation");
    return _particle->getRotation();
}

void jf::components::Particle::setRotation(const irr::core::vector3df &newRotation)
{
    if (_particle == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::setRotation");
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