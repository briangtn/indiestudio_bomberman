/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** ComponentParticle
*/

#include <iomanip>
#include "components/ComponentParticle.hpp"
#include "events/IrrlichtClosingWindowEvent.hpp"

indie::components::Particle::Particle(jf::entities::Entity &entity, const std::string &name)
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

indie::components::Particle::~Particle()
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

bool indie::components::Particle::isEmitterInit() const
{
    return _emiterSizeInitialize && _initialDirectionInitialize &&
    _emitRateInitialize && _darkBrightColorInitialize &&
    _minMaxAgeInitialize && _angleInitialize && _minMaxSizeInitialize;
}

bool indie::components::Particle::isAffectorInit() const
{
    return _fadeColorInitialize && _fadeTimeInitialize;
}

void indie::components::Particle::initParticle()
{
    if (_particle != nullptr)
        throw indie::exceptions::IrrlichtParticleException("Particle not init.", "indie::components::Particle::initParticle");
    ECSWrapper ecs;
    auto sceneManager = ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().getSceneManager();
    auto videoDriver = ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().getVideoDriver();
    if (sceneManager == nullptr || videoDriver == nullptr)
        throw indie::exceptions::IrrlichtParticleException("sceneManager not init.", "indie::components::Particle::initParticle");
    _particle = sceneManager->addParticleSystemSceneNode(false);
    if (_particle == nullptr)
        throw indie::exceptions::IrrlichtParticleException("Particle not init.", "indie::components::Particle::initParticle");
    if (!isEmitterInit()) {
        throw indie::exceptions::IrrlichtParticleException("Emitter not init.", "indie::components::Particle::initParticle");
    } else {
        createBoxEmitter();
    }
    if (!isAffectorInit()) {
        throw indie::exceptions::IrrlichtParticleException("Affector not init.", "indie::components::Particle::initParticle");
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

bool indie::components::Particle::isInit() const
{
    return _particle && _affector;
}

void indie::components::Particle::createBoxEmitter()
{
    if (_particle == nullptr)
        throw indie::exceptions::IrrlichtParticleException("Particle not init.", "indie::components::Particle::createBoxEmitter");
    _emitter = _particle->createBoxEmitter(
        _emitterSize,
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
        throw indie::exceptions::IrrlichtParticleException("Emitter not init.", "indie::components::Particle::createBoxEmitter");
    _particle->setEmitter(_emitter);
    _boxEmiterCreated = true;
}

void indie::components::Particle::createFadeOutAffector()
{
    if (_particle == nullptr)
        throw indie::exceptions::IrrlichtParticleException("Particle not init.", "indie::components::Particle::createFadeOutParticle");
    _affector = _particle->createFadeOutParticleAffector(_fadeColor, _fadeTime);
    if (_affector == nullptr)
        throw indie::exceptions::IrrlichtParticleException("Affector not init.", "indie::components::Particle::createFadeOutParticle");
    _particle->addAffector(_affector);
    _affectorCreated = true;
}

const irr::scene::IParticleEmitter *indie::components::Particle::getEmitter() const
{
    return _emitter;
}

irr::core::aabbox3d<irr::f32> indie::components::Particle::getEmitterSize() const
{
    return _emitterSize;
}

void indie::components::Particle::setEmitterSize(const irr::core::aabbox3d<irr::f32> &newEmitterSize)
{
    _emitterSize = newEmitterSize;
    _emiterSizeInitialize = true;
}

irr::core::vector3df indie::components::Particle::getInitialDirection() const
{
    return _initialDirection;
}

void indie::components::Particle::setInitialDirection(const irr::core::vector3df &newInitialDirection)
{
    _initialDirection = newInitialDirection;
    _initialDirectionInitialize = true;
}

 std::pair<int, int> indie::components::Particle::getEmitRate() const
 {
     return _emitRate;
 }

 void indie::components::Particle::setEmitRate(const std::pair<int, int> &newEmitRate)
 {
     _emitRate = newEmitRate;
     _emitRateInitialize = true;
 }

std::pair<irr::video::SColor, irr::video::SColor> indie::components::Particle::getDarkBrightColor() const
{
    return _darkBrightColor;
}

void indie::components::Particle::setDarkBrightColor(const std::pair<irr::video::SColor, irr::video::SColor> &newDarkBrightColor)
{
    _darkBrightColor = newDarkBrightColor;
    _darkBrightColorInitialize = true;
}

std::pair<int, int> indie::components::Particle::getMinMaxAge() const
{
    return _minMaxAge;
}

void indie::components::Particle::setMinMaxAge(const std::pair<int, int> &newMinMaxAge)
{
    _minMaxAge = newMinMaxAge;
    _minMaxAgeInitialize = true;
}

 int indie::components::Particle::getAngle() const
 {
     return _angle;
 }

 void indie::components::Particle::setAngle(const int &newAngle)
 {
     _angle = newAngle;
     _angleInitialize = true;
 }

std::pair<irr::core::dimension2df, irr::core::dimension2df> indie::components::Particle::getMinMaxSize() const
{
    return _minMaxSize;
}

void indie::components::Particle::setMinMaxSize(const std::pair<irr::core::dimension2df, irr::core::dimension2df> &newMinMaxSize)
{
    _minMaxSize = newMinMaxSize;
    _minMaxSizeInitialize = true;
}

irr::video::SColor indie::components::Particle::getFadeColor() const
{
    return _fadeColor;
}

void indie::components::Particle::setFadeColor(const irr::video::SColor &newFadeColor)
{
    _fadeColor = newFadeColor;
    _fadeColorInitialize = true;
}

int indie::components::Particle::getFadeTime() const
{
    return _fadeTime;
}

void indie::components::Particle::setFadeTime(const int &newFadeTime)
{
    _fadeTime = newFadeTime;
    _fadeTimeInitialize = true;
}

void indie::components::Particle::activate()
{
    _isVisible = true;
    if (_particle != nullptr) {
        _particle->setVisible(_isVisible);
    }
}

void indie::components::Particle::deactivate()
{
    _isVisible = false;
    if (_particle == nullptr)
        throw indie::exceptions::IrrlichtParticleException("Particle not init.", "indie::components::Particle::deactivate");
    _particle->setVisible(_isVisible);
}

std::string indie::components::Particle::getTexturePath() const
{
    return _texturePath;
}

irr::core::vector3df indie::components::Particle::getPosition() const
{
    if (_particle == nullptr)
        throw indie::exceptions::IrrlichtParticleException("Particle not init.", "indie::components::Particle::getPosition");
    return _particle->getPosition();
}

void indie::components::Particle::setPosition(const irr::core::vector3df &newPos)
{
    if (_particle == nullptr)
        throw indie::exceptions::IrrlichtParticleException("Particle not init.", "indie::components::Particle::setPosition");
    _particle->setPosition(newPos);
}

irr::core::vector3df indie::components::Particle::getScale() const
{
    if (_particle == nullptr)
        throw indie::exceptions::IrrlichtParticleException("Particle not init.", "indie::components::Particle::getScale");
    return _particle->getScale();
}

void indie::components::Particle::setScale(const irr::core::vector3df &newScale)
{
    if (_particle == nullptr)
        throw indie::exceptions::IrrlichtParticleException("Particle not init.", "indie::components::Particle::setScale");
    _particle->setScale(newScale);
}

irr::core::vector3df indie::components::Particle::getRotation() const
{
    if (_particle == nullptr)
        throw indie::exceptions::IrrlichtParticleException("Particle not init.", "indie::components::Particle::getRotation");
    return _particle->getRotation();
}

void indie::components::Particle::setRotation(const irr::core::vector3df &newRotation)
{
    if (_particle == nullptr)
        throw indie::exceptions::IrrlichtParticleException("Particle not init.", "indie::components::Particle::setRotation");
    _particle->setRotation(newRotation);
}

void indie::components::Particle::setTexture(int layer, const std::string &texturePath)
{
    ECSWrapper ecs;

    _layer = layer;
    _texturePath = texturePath;
    if (_particle != nullptr) {
        auto videoDriver = ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().getVideoDriver();
        if (videoDriver != nullptr)
            _particle->setMaterialTexture(_layer, videoDriver->getTexture(texturePath.c_str()));
    }
}

bool indie::components::Particle::getIsVisible() const
{
    return _isVisible;
}

std::string indie::components::Particle::getName() const
{
    return _name;
}

void indie::components::Particle::setName(const std::string &newName)
{
    _name = newName;
    if (_particle != nullptr)
        _particle->setName(_name.c_str());
}

void indie::components::Particle::render()
{
    if (_particle != nullptr) {
        _particle->setVisible(_isVisible);
        _particle->render();
    }
}

indie::components::Particle &indie::components::Particle::operator>>(std::ostream &file)
{
    file << R"(        <component type="Particle">)" << std::endl;
    file << R"(            <argument name="name" value=")" << _name << R"("/>)" << std::endl;
    file << R"(            <argument name="fileName" value=")" << _texturePath << R"("/>)" << std::endl;
    file << R"(            <argument name="layer" value=")" << _layer << R"("/>)" << std::endl;
    file << R"(            <argument name="emitterSize" value=")"  << _emitterSize << R"("/>)" << std::endl;
    file << R"(            <argument name="direction" value=")" << _initialDirection << R"("/>)" << std::endl;
    file << R"(            <argument name="emitRate" value=")" << _emitRate << R"("/>)" << std::endl;
    file << R"(            <argument name="brightColor" value=")" << _darkBrightColor << R"("/>)" << std::endl;
    file << R"(            <argument name="age" value=")" << _minMaxAge << R"("/>)" << std::endl;
    file << R"(            <argument name="angle" value=")" << _angle << R"("/>)" << std::endl;
    file << R"(            <argument name="size" value=")" << _minMaxSize << R"("/>)" << std::endl;
    file << R"(            <argument name="fadeColor" value=")" << _fadeColor << R"("/>)" << std::endl;
    file << R"(            <argument name="fadeTime" value=")" << _fadeTime << R"("/>)" << std::endl;
    file << "        </component>" << std::endl;
    return *this;
}

std::ostream &indie::components::operator<<(std::ostream &file, const irr::core::aabbox3d<irr::f32> &box)
{
    file << box.MinEdge << ";" << box.MaxEdge;
    return file;
}

std::ostream &indie::components::operator<<(std::ostream &file, const irr::core::vector3d<float> &vector)
{
    file << vector.X << "," << vector.Y << "," << vector.Z;
    return file;
}

std::ostream &indie::components::operator<<(std::ostream &file, const std::pair<int, int> &pair)
{
    file << pair.first << "," << pair.second;
    return file;
}

std::ostream &indie::components::operator<<(std::ostream &file, const std::pair<irr::video::SColor, irr::video::SColor> &pair)
{
    file << pair.first << ";" << pair.second;
    return file;
}

std::ostream &indie::components::operator<<(std::ostream &file, const irr::video::SColor &color)
{
    file << color.getAlpha() << "," << color.getRed() << "," << color.getGreen() << "," << color.getBlue();
    return file;
}

std::ostream &indie::components::operator<<(std::ostream &file, const std::pair<irr::core::dimension2df, irr::core::dimension2df> &pair)
{
    file << pair.first << ";" << pair.second;
    return file;
}

std::ostream &indie::components::operator<<(std::ostream &file, const irr::core::dimension2df &vector)
{
    file << vector.Width << "," << vector.Height;
    return file;
}
