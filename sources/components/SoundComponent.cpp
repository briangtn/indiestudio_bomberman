/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** SoundComponent.cpp
*/

/* Created the 13/05/2019 at 19:00 by jbulteau */

#include <iomanip>
#include "components/SoundComponent.hpp"
#include "ECSWrapper.hpp"
#include "systems/IrrklangAudioSystem.hpp"
#include "Events.hpp"
#include "components/SoundComponent.hpp"

/* ================================================================================================================ */
/* ----------------------------------------------------Ctor&Dtor--------------------------------------------------- */
/* ================================================================================================================ */

indie::components::SoundComponent::SoundComponent(jf::entities::Entity &entity, const std::string &sourceFile, SoundType soundType)
    : Component(entity)
    , _state(STARTING)
    , _sound(nullptr)
    , _sourceFile(sourceFile)
    , _soundType(soundType)
    , _spatialization(false)
    , _isLooped(false)
    , _isPaused(true)
    , _volume(1)
    , _playPosition(0)
    , _position(0, 0, 0)
    , _velocity(0, 0, 0)
{
    EMIT_CREATE(SoundComponent);
}

indie::components::SoundComponent::SoundComponent(jf::entities::Entity &entity, const std::string &sourceFile, SoundType soundType, indie::maths::Vector3D position)
        : Component(entity)
        , _state(STARTING)
        , _sound(nullptr)
        , _sourceFile(sourceFile)
        , _soundType(soundType)
        , _spatialization(true)
        , _isLooped(false)
        , _isPaused(true)
        , _volume(1)
        , _playPosition(0)
        , _position(position)
        , _velocity(0, 0, 0)
{
    EMIT_CREATE(SoundComponent);
}

indie::components::SoundComponent::~SoundComponent()
{
    ECSWrapper ecs;

    EMIT_DELETE(SoundComponent);
    if (_sound != nullptr)
        ecs.systemManager.getSystem<systems::IrrklangAudioSystem>().removeSound(jf::components::ComponentHandler<SoundComponent>(this));
}

/* ================================================================================================================ */
/* -----------------------------------------------Setters and Getters---------------------------------------------- */
/* ================================================================================================================ */

const indie::components::SoundComponent::SoundComponentState indie::components::SoundComponent::getState() const
{
    return _state;
}

irrklang::ISound *indie::components::SoundComponent::getSound()
{
    return _sound;
}

void indie::components::SoundComponent::setSound(irrklang::ISound *sound)
{
    _sound = sound;
    if (_sound) {
        _state = STARTED;
        _sound->setVolume(_volume);
        _sound->setPlayPosition(_playPosition);
        if (_spatialization) {
            _sound->setVelocity(irrklang::vec3df(_velocity.x, _velocity.y, _velocity.z));
        }
    }
}

const std::string &indie::components::SoundComponent::getSourceFile() const
{
    return _sourceFile;
}

indie::components::SoundComponent::SoundType indie::components::SoundComponent::getSoundType() const
{
    return _soundType;
}

bool indie::components::SoundComponent::getSpatialization() const
{
    return _spatialization;
}

bool indie::components::SoundComponent::getIsLooped() const
{
    if (_sound) {
        return _sound->isLooped();
    }
    return _isLooped;
}

void indie::components::SoundComponent::setIsLooped(bool isLooped)
{
    _isLooped = isLooped;
    if (_sound) {
        _sound->setIsLooped(isLooped);
    }
}

bool indie::components::SoundComponent::getIsPaused() const
{
    if (_sound) {
        return _sound->getIsPaused();
    }
    return _isPaused;
}

void indie::components::SoundComponent::setIsPaused(bool isPaused)
{
    _isPaused = isPaused;
    if (_sound) {
        _sound->setIsPaused(isPaused);
    }
}

float indie::components::SoundComponent::getVolume() const
{
    if (_sound) {
        return _sound->getVolume();
    }
    return _volume;
}

void indie::components::SoundComponent::setVolume(float volume)
{
    _volume = volume;
    if (_sound) {
        _sound->setVolume(volume);
    }
}

unsigned int indie::components::SoundComponent::getPlayPosition() const
{
    if (_sound) {
        return _sound->getPlayPosition();
    }
    return _playPosition;
}

void indie::components::SoundComponent::setPlayPosition(unsigned int position)
{
    _playPosition = position;
    if (_sound) {
        _sound->setPlayPosition(position);
    }
}

const indie::maths::Vector3D indie::components::SoundComponent::getPosition() const
{
    if (_sound && _spatialization) {
        irrklang::vec3df position = _sound->getPosition();
        return indie::maths::Vector3D(position.X, position.Y, position.Z);
    }
    return _position;
}

void indie::components::SoundComponent::setPosition(const indie::maths::Vector3D &position)
{
    if (_sound && _spatialization) {
        _sound->setPosition(irrklang::vec3df(position.x, position.y, position.z));
    }
}

const indie::maths::Vector3D indie::components::SoundComponent::getVelocity() const
{
    if (_sound && _spatialization) {
        irrklang::vec3df velocity = _sound->getVelocity();
        return indie::maths::Vector3D(velocity.X, velocity.Y, velocity.Z);
    }
    return _velocity;
}

void indie::components::SoundComponent::setVelocity(const indie::maths::Vector3D &velocity)
{
    _velocity = velocity;
    if (_sound && _spatialization) {
        _sound->setVelocity(irrklang::vec3df(velocity.x, velocity.y, velocity.z));
    }
}

indie::components::SoundComponent &indie::components::SoundComponent::operator>>(std::ostream &file)
{
    file << R"(        <component type="Sound">)" << std::endl;
    file << R"(            <argument name="fileName" value=")" << _sourceFile << R"("/>)" << std::endl;
    file << R"(            <argument name="type" value=")" << ((_soundType == MUSIC) ? "MUSIC" : "EFFECT") << R"("/>)" << std::endl;
    if (_spatialization) {
        file << R"(            <argument name="position" value=")" << _position << R"("/>)" << std::endl;
    }
    file << R"(            <argument name="playLooped" value=")" << std::boolalpha << _isLooped << R"("/>)" << std::endl;
    file << R"(            <argument name="startPaused" value=")" << std::boolalpha << _isPaused << R"("/>)" << std::endl;
    file << R"(            <argument name="volume" value=")" << _volume << R"("/>)" << std::endl;
    file << R"(            <argument name="playPosition" value=")" << _playPosition << R"("/>)" << std::endl;
    if (_spatialization) {
        file << R"(            <argument name="velocity" value=")" << _velocity << R"("/>)" << std::endl;
    }
    file << "        </component>" << std::endl;
    return *this;
}
