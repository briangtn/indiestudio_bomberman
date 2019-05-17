/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** ComponentParticle
*/

#include "ComponentParticle.hpp"
#include "IrrlichtClosingWindowEvent.hpp"

jf::components::Particle::Particle(jf::entities::Entity &entity, const std::string &name)
    : Component(entity),
      _boxEmiterCreated(false),
      _affectorCreated(false),
      _isVisible(false),
      _particle(nullptr),
      _emitter(nullptr),
      _affector(nullptr),
      _layer(0),
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
    ECSWrapper ecs;
    _irrlichtClosingWindowEventID = ecs.eventManager.addListener<Particle, events::IrrlichtClosingWindowEvent>(this,
        [](Particle *particle, events::IrrlichtClosingWindowEvent e) {
            if (particle->_affector) {
                particle->_affector->drop();
                particle->_affector = nullptr;
            }
            if (particle->_emitter) {
                particle->_emitter->drop();
                particle->_emitter = nullptr;
            }
            if (particle->_particle) {
                particle->_particle->remove();
                particle->_particle = nullptr;
            }
        }
    );
    EMIT_CREATE(Particle);
}

jf::components::Particle::~Particle()
{
    EMIT_DELETE(Particle);
    ECSWrapper ecs;
    ecs.eventManager.removeListener(_irrlichtClosingWindowEventID);
    if (_affector)
        _affector->drop();
    if (_emitter)
        _emitter->drop();
    if (_particle)
        _particle->remove();
}

bool jf::components::Particle::isEmitterInit() const
{
    return _emiterSizeInitialize && _initialDirectionInitialize &&
    _emitRateInitialize && _darkBrightColorInitialize &&
    _minMaxAgeInitialize && _angleInitialize && _minMaxSizeInitialize;
}

bool jf::components::Particle::isAffectorInit() const
{
    return _fadeColorInitialize && _fadeTimeInitialize;
}

void jf::components::Particle::initParticle()
{
    if (_particle != nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::initParticle");
    ECSWrapper ecs;
    auto sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
    auto videoDriver = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getVideoDriver();
    if (sceneManager == nullptr || videoDriver == nullptr)
        throw jf::exceptions::IrrlichtParticleException("sceneManager not init.", "jf::components::Particle::initParticle");
    _particle = sceneManager->addParticleSystemSceneNode(false);
    if (_particle == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::initParticle");
    if (!isEmitterInit()) {
        throw jf::exceptions::IrrlichtParticleException("Emitter not init.", "jf::components::Particle::initParticle");
    } else {
        createBoxEmitter();
    }
    if (!isAffectorInit()) {
        throw jf::exceptions::IrrlichtParticleException("Affector not init.", "jf::components::Particle::initParticle");
    } else {
        createFadeOutAffector();
    }
    _particle->setName(_name.c_str());
    _particle->setVisible(_isVisible);
    _particle->setMaterialTexture(_layer, videoDriver->getTexture(_texturePath.c_str()));
    _particle->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _particle->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    _particle->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    activate();
}

bool jf::components::Particle::isInit() const
{
    return _particle && _affector;
}

void jf::components::Particle::createBoxEmitter()
{
    if (_particle == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::createBoxEmitter");
    _emitter = _particle->createBoxEmitter(
        _emiterSize,
        _initialDirection,
        _emitRate.first,
        _emitRate.second,
        _darkBrightColor.first,
        _darkBrightColor.second,
        _minMaxAge.first,
        _minMaxAge.second,
        _angle,
        _minMaxSize.first,
        _minMaxSize.second
    );
    if (_emitter == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Emitter not init.", "jf::components::Particle::createBoxEmitter");
    _particle->setEmitter(_emitter);
    _boxEmiterCreated = true;
}

void jf::components::Particle::createFadeOutAffector()
{
    if (_particle == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::createFadeOutParticle");
    _affector = _particle->createFadeOutParticleAffector(_fadeColor, _fadeTime);
    if (_affector == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Affector not init.", "jf::components::Particle::createFadeOutParticle");
    _particle->addAffector(_affector);
    _affectorCreated = true;
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
    _minMaxSize = newMinMaxSize;
    _minMaxSizeInitialize = true;
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
    _isVisible = true;
    if (_particle != nullptr) {
        _particle->setVisible(_isVisible);
    }
}

void jf::components::Particle::deactivate()
{
    _isVisible = false;
    if (_particle == nullptr)
        throw jf::exceptions::IrrlichtParticleException("Particle not init.", "jf::components::Particle::deactivate");
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

    _layer = layer;
    _texturePath = texturePath;
    if (_particle != nullptr) {
        auto videoDriver = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getVideoDriver();
        if (videoDriver != nullptr)
            _particle->setMaterialTexture(_layer, videoDriver->getTexture(texturePath.c_str()));
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

void jf::components::Particle::render()
{
    if (_particle != nullptr) {
        _particle->setVisible(_isVisible);
        _particle->render();
    }
}
