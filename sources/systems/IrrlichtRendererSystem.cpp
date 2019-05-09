/*
** EPITECH PROJECT, 2018
** jfecs-irrlicht
** File description:
** IrrlichtRendererSystem.cpp
*/

/* Created the 09/05/2019 at 13:55 by jfrabel */

#include "IrrlichtRendererSystem.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

jf::systems::IrrlichtRendererSystem::IrrlichtRendererSystem()
    : _device(nullptr),
      _driver(nullptr),
      _sceneManager(nullptr),
      _guiEnvironment(nullptr),
      _fullscreenEnabled(false),
      _vsyncEnabled(false),
      _windowCaption("Irrlicht window"),
      _windowDimension(800, 600)
{

}

jf::systems::IrrlichtRendererSystem::~IrrlichtRendererSystem()
{
    if (isWindowOpen())
        closeWindow();
}

void jf::systems::IrrlichtRendererSystem::onAwake()
{

}

void jf::systems::IrrlichtRendererSystem::onStart()
{
    openWindow();
}

void jf::systems::IrrlichtRendererSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    _driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
    _sceneManager->drawAll();
    _guiEnvironment->drawAll();
    _driver->endScene();
}

void jf::systems::IrrlichtRendererSystem::onStop()
{
    closeWindow();
}

void jf::systems::IrrlichtRendererSystem::onTearDown()
{

}

bool jf::systems::IrrlichtRendererSystem::isFullScreenEnabled() const
{
    return _fullscreenEnabled;
}

void jf::systems::IrrlichtRendererSystem::setFullScreenEnabled(bool enabled)
{
    _fullscreenEnabled = enabled;
    reloadWindow();
}

bool jf::systems::IrrlichtRendererSystem::isVSyncEnabled() const
{
    return _vsyncEnabled;
}

void jf::systems::IrrlichtRendererSystem::setVSyncEnabled(bool enabled)
{
    _vsyncEnabled = enabled;
    reloadWindow();
}

const std::string &jf::systems::IrrlichtRendererSystem::getWindowCaption() const
{
    return _windowCaption;
}

void jf::systems::IrrlichtRendererSystem::setWindowCaption(const std::string &str)
{
    _windowCaption = str;
    reloadWindow();
}

const jf::maths::Vector2D &jf::systems::IrrlichtRendererSystem::getWindowDimension() const
{
    return _windowDimension;
}

void jf::systems::IrrlichtRendererSystem::setWindowDimension(const jf::maths::Vector2D &dimensions)
{
    _windowDimension = dimensions;
    reloadWindow();
}

bool jf::systems::IrrlichtRendererSystem::isWindowOpen() const
{
    if (_device != nullptr)
        return _device->run();
    return false;
}

void jf::systems::IrrlichtRendererSystem::openWindow()
{
    _device = irr::createDevice(
        irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(_windowDimension.x, _windowDimension.y),
        32,
        _fullscreenEnabled,
        false,
        _vsyncEnabled,
        0
    );
    if (_device == nullptr)
        throw std::exception();
    _device->setWindowCaption(std::wstring(_windowCaption.begin(), _windowCaption.end()).c_str());
    _driver = _device->getVideoDriver();
    _sceneManager = _device->getSceneManager();
    _guiEnvironment = _device->getGUIEnvironment();
}

void jf::systems::IrrlichtRendererSystem::closeWindow()
{
    if (_device != nullptr)
        _device->drop();
    _device = nullptr;
}

void jf::systems::IrrlichtRendererSystem::reloadWindow()
{
    if (_device != nullptr)
        closeWindow();
    if (_device == nullptr)
        openWindow();
}
