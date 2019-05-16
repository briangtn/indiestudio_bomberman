/*
** EPITECH PROJECT, 2018
** jfecs-irrlicht
** File description:
** IrrlichtManagerSystem.cpp
*/

/* Created the 09/05/2019 at 13:55 by jfrabel */

#include "IrrlichtManagerExceptions.hpp"
#include "ECSWrapper.hpp"
#include "IrrlichtManagerSystem.hpp"
#include "IrrlichtKeyInputEvent.hpp"
#include "IrrlichtJoystickInputEvent.hpp"
#include "IrrlichtMouseInputEvent.hpp"
#include "IrrlichtGUIEvent.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

jf::systems::IrrlichtManagerSystem::IrrlichtManagerSystem()
    : _eventReceiver(),
      _device(nullptr),
      _driver(nullptr),
      _sceneManager(nullptr),
      _guiEnvironment(nullptr),
      _joystickEnabled(false),
      _joystickInfos(),
      _fullscreenEnabled(false),
      _vsyncEnabled(false),
      _windowCaption("Irrlicht window"),
      _windowDimension(800, 600)
{

}

jf::systems::IrrlichtManagerSystem::~IrrlichtManagerSystem()
{
    if (isWindowOpen())
        closeWindow();
}

void jf::systems::IrrlichtManagerSystem::onAwake()
{

}

void jf::systems::IrrlichtManagerSystem::onStart()
{
    openWindow();
}

void jf::systems::IrrlichtManagerSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    if (!_driver || !_sceneManager || !_guiEnvironment)
        return;
    _driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
    _sceneManager->drawAll();
    _guiEnvironment->drawAll();
    _driver->endScene();
}

void jf::systems::IrrlichtManagerSystem::onStop()
{
    closeWindow();
}

void jf::systems::IrrlichtManagerSystem::onTearDown()
{

}

bool jf::systems::IrrlichtManagerSystem::isFullScreenEnabled() const
{
    return _fullscreenEnabled;
}

void jf::systems::IrrlichtManagerSystem::setFullScreenEnabled(bool enabled)
{
    _fullscreenEnabled = enabled;
    reloadWindow();
}

bool jf::systems::IrrlichtManagerSystem::isVSyncEnabled() const
{
    return _vsyncEnabled;
}

void jf::systems::IrrlichtManagerSystem::setVSyncEnabled(bool enabled)
{
    _vsyncEnabled = enabled;
    reloadWindow();
}

const std::string &jf::systems::IrrlichtManagerSystem::getWindowCaption() const
{
    return _windowCaption;
}

void jf::systems::IrrlichtManagerSystem::setWindowCaption(const std::string &str)
{
    _windowCaption = str;
    reloadWindow();
}

const jf::maths::Vector2D &jf::systems::IrrlichtManagerSystem::getWindowDimension() const
{
    return _windowDimension;
}

void jf::systems::IrrlichtManagerSystem::setWindowDimension(const jf::maths::Vector2D &dimensions)
{
    _windowDimension = dimensions;
    reloadWindow();
}

bool jf::systems::IrrlichtManagerSystem::isWindowOpen() const
{
    if (_device != nullptr)
        return _device->run();
    return false;
}

void jf::systems::IrrlichtManagerSystem::openWindow()
{
    _device = irr::createDevice(
        irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(_windowDimension.x, _windowDimension.y),
        32,
        _fullscreenEnabled,
        false,
        _vsyncEnabled,
        &_eventReceiver
    );
    if (_device == nullptr)
        throw exceptions::IrrlichtManagerDeviceException("Failed to create device", "jf::systems::IrrlichtManagerSystem::openWindow");
    _device->setWindowCaption(std::wstring(_windowCaption.begin(), _windowCaption.end()).c_str());
    _driver = _device->getVideoDriver();
    _sceneManager = _device->getSceneManager();
    _guiEnvironment = _device->getGUIEnvironment();
    reloadJoysticks();
}

void jf::systems::IrrlichtManagerSystem::closeWindow()
{
    if (_device != nullptr)
        _device->drop();
    _device = nullptr;
}

void jf::systems::IrrlichtManagerSystem::reloadWindow()
{
    if (!isWindowOpen())
        return;
    if (_device != nullptr)
        closeWindow();
    if (_device == nullptr)
        openWindow();
}

void jf::systems::IrrlichtManagerSystem::activateJoysticks()
{
    _joystickEnabled = true;
}

const irr::core::array<irr::SJoystickInfo> &jf::systems::IrrlichtManagerSystem::getJoystickInfos()
{
    return _joystickInfos;
}

void jf::systems::IrrlichtManagerSystem::reloadJoysticks()
{
    if (_joystickEnabled) {
        if (_device == nullptr) {
            throw exceptions::IrrlichtManagerDeviceException("Device is not open.", "jf::systems::IrrlichtManagerSystem::reloadJoysticks");
        }
        if (!_device->activateJoysticks(_joystickInfos)) {
            throw exceptions::IrrlichtManagerDeviceException("Joystick support is not enabled.", "jf::systems::IrrlichtManagerSystem::reloadJoysticks");
        }
        std::cout << "Joystick support is enabled and " << _joystickInfos.size() << " joystick(s) are present." << std::endl;
    }
}

bool jf::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::OnEvent(const irr::SEvent &event)
{
    switch (event.EventType) {
    case irr::EET_GUI_EVENT:
        sendGUIEvent(event);
        break;
    case irr::EET_MOUSE_INPUT_EVENT:
        sendMouseInputEvent(event);
        break;
    case irr::EET_KEY_INPUT_EVENT:
        sendKeyInputEvent(event);
        break;
    case irr::EET_JOYSTICK_INPUT_EVENT:
        sendJoystickInputEvent(event);
        break;
    case irr::EET_LOG_TEXT_EVENT:
        sendLogTextEvent(event);
        break;
    case irr::EET_USER_EVENT:
        sendUserEvent(event);
        break;
    default:
        break;
    }
    return false;
}

void jf::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::sendGUIEvent(const irr::SEvent &event)
{
    ECSWrapper ecs;
    ecs.eventManager.emit(events::IrrlichtGUIEvent({event.GUIEvent}));
}

void jf::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::sendMouseInputEvent(const irr::SEvent &event)
{
    ECSWrapper ecs;
    ecs.eventManager.emit(events::IrrlichtMouseInputEvent({event.MouseInput}));
    switch (event.MouseInput.Event) {
    case irr::EMIE_LMOUSE_PRESSED_DOWN:
        ecs.eventManager.emit(events::IrrlichtLeftMouseButtonInputEvent({true, false}));
        break;
    case irr::EMIE_RMOUSE_PRESSED_DOWN:
        ecs.eventManager.emit(events::IrrlichtRightMouseButtonInputEvent({true, false}));
        break;
    case irr::EMIE_MMOUSE_PRESSED_DOWN:
        ecs.eventManager.emit(events::IrrlichtMiddleMouseButtonInputEvent({true, false}));
        break;
    case irr::EMIE_LMOUSE_LEFT_UP:
        ecs.eventManager.emit(events::IrrlichtLeftMouseButtonInputEvent({false, true}));
        break;
    case irr::EMIE_RMOUSE_LEFT_UP:
        ecs.eventManager.emit(events::IrrlichtRightMouseButtonInputEvent({false, true}));
        break;
    case irr::EMIE_MMOUSE_LEFT_UP:
        ecs.eventManager.emit(events::IrrlichtMiddleMouseButtonInputEvent({false, true}));
        break;
    case irr::EMIE_MOUSE_MOVED:
        ecs.eventManager.emit(events::IrrlichtMouseMovedInputEvent({event.MouseInput.X, event.MouseInput.Y}));
        break;
    case irr::EMIE_MOUSE_WHEEL:
        ecs.eventManager.emit(events::IrrlichtMouseWheelScrolledInputEvent({event.MouseInput.Wheel}));
        break;
    default:
        break;
    }
}

void jf::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::sendKeyInputEvent(const irr::SEvent &event)
{
    ECSWrapper ecs;
    ecs.eventManager.emit(jf::events::IrrlichtKeyInputEvent({
        event.KeyInput.Key,
        event.KeyInput.PressedDown,
        !event.KeyInput.PressedDown,
        event.KeyInput.Shift,
        event.KeyInput.Control
    }));
    if (DO_NOT_SEND_SPECIFIC_KEY_EVENT)
        return;
    switch (event.KeyInput.Key) {
    case irr::KEY_LBUTTON:
        EMIT_SPECIFIC_KEY(irr::KEY_LBUTTON, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_RBUTTON:
        EMIT_SPECIFIC_KEY(irr::KEY_RBUTTON, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_CANCEL:
        EMIT_SPECIFIC_KEY(irr::KEY_CANCEL, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_MBUTTON:
        EMIT_SPECIFIC_KEY(irr::KEY_MBUTTON, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_XBUTTON1:
        EMIT_SPECIFIC_KEY(irr::KEY_XBUTTON1, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_XBUTTON2:
        EMIT_SPECIFIC_KEY(irr::KEY_XBUTTON2, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_BACK:
        EMIT_SPECIFIC_KEY(irr::KEY_BACK, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_TAB:
        EMIT_SPECIFIC_KEY(irr::KEY_TAB, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_CLEAR:
        EMIT_SPECIFIC_KEY(irr::KEY_CLEAR, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_RETURN:
        EMIT_SPECIFIC_KEY(irr::KEY_RETURN, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_SHIFT:
        EMIT_SPECIFIC_KEY(irr::KEY_SHIFT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_CONTROL:
        EMIT_SPECIFIC_KEY(irr::KEY_CONTROL, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_MENU:
        EMIT_SPECIFIC_KEY(irr::KEY_MENU, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_PAUSE:
        EMIT_SPECIFIC_KEY(irr::KEY_PAUSE, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_CAPITAL:
        EMIT_SPECIFIC_KEY(irr::KEY_CAPITAL, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KANA:
        EMIT_SPECIFIC_KEY(irr::KEY_KANA, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_JUNJA:
        EMIT_SPECIFIC_KEY(irr::KEY_JUNJA, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_FINAL:
        EMIT_SPECIFIC_KEY(irr::KEY_FINAL, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_HANJA:
        EMIT_SPECIFIC_KEY(irr::KEY_HANJA, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_ESCAPE:
        EMIT_SPECIFIC_KEY(irr::KEY_ESCAPE, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_CONVERT:
        EMIT_SPECIFIC_KEY(irr::KEY_CONVERT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_NONCONVERT:
        EMIT_SPECIFIC_KEY(irr::KEY_NONCONVERT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_ACCEPT:
        EMIT_SPECIFIC_KEY(irr::KEY_ACCEPT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_MODECHANGE:
        EMIT_SPECIFIC_KEY(irr::KEY_MODECHANGE, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_SPACE:
        EMIT_SPECIFIC_KEY(irr::KEY_SPACE, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_PRIOR:
        EMIT_SPECIFIC_KEY(irr::KEY_PRIOR, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_NEXT:
        EMIT_SPECIFIC_KEY(irr::KEY_NEXT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_END:
        EMIT_SPECIFIC_KEY(irr::KEY_END, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_HOME:
        EMIT_SPECIFIC_KEY(irr::KEY_HOME, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_LEFT:
        EMIT_SPECIFIC_KEY(irr::KEY_LEFT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_UP:
        EMIT_SPECIFIC_KEY(irr::KEY_UP, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_RIGHT:
        EMIT_SPECIFIC_KEY(irr::KEY_RIGHT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_DOWN:
        EMIT_SPECIFIC_KEY(irr::KEY_DOWN, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_SELECT:
        EMIT_SPECIFIC_KEY(irr::KEY_SELECT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_PRINT:
        EMIT_SPECIFIC_KEY(irr::KEY_PRINT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_EXECUT:
        EMIT_SPECIFIC_KEY(irr::KEY_EXECUT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_SNAPSHOT:
        EMIT_SPECIFIC_KEY(irr::KEY_SNAPSHOT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_INSERT:
        EMIT_SPECIFIC_KEY(irr::KEY_INSERT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_DELETE:
        EMIT_SPECIFIC_KEY(irr::KEY_DELETE, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_HELP:
        EMIT_SPECIFIC_KEY(irr::KEY_HELP, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_0:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_0, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_1:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_1, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_2:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_2, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_3:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_3, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_4:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_4, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_5:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_5, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_6:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_6, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_7:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_7, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_8:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_8, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_9:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_9, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_A:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_A, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_B:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_B, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_C:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_C, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_D:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_D, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_E:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_E, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_F:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_F, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_G:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_G, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_H:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_H, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_I:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_I, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_J:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_J, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_K:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_K, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_L:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_L, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_M:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_M, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_N:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_N, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_O:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_O, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_P:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_P, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_Q:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_Q, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_R:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_R, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_S:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_S, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_T:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_T, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_U:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_U, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_V:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_V, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_W:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_W, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_X:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_X, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_Y:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_Y, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_Z:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_Z, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_LWIN:
        EMIT_SPECIFIC_KEY(irr::KEY_LWIN, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_RWIN:
        EMIT_SPECIFIC_KEY(irr::KEY_RWIN, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_APPS:
        EMIT_SPECIFIC_KEY(irr::KEY_APPS, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_SLEEP:
        EMIT_SPECIFIC_KEY(irr::KEY_SLEEP, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_NUMPAD0:
        EMIT_SPECIFIC_KEY(irr::KEY_NUMPAD0, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_NUMPAD1:
        EMIT_SPECIFIC_KEY(irr::KEY_NUMPAD1, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_NUMPAD2:
        EMIT_SPECIFIC_KEY(irr::KEY_NUMPAD2, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_NUMPAD3:
        EMIT_SPECIFIC_KEY(irr::KEY_NUMPAD3, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_NUMPAD4:
        EMIT_SPECIFIC_KEY(irr::KEY_NUMPAD4, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_NUMPAD5:
        EMIT_SPECIFIC_KEY(irr::KEY_NUMPAD5, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_NUMPAD6:
        EMIT_SPECIFIC_KEY(irr::KEY_NUMPAD6, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_NUMPAD7:
        EMIT_SPECIFIC_KEY(irr::KEY_NUMPAD7, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_NUMPAD8:
        EMIT_SPECIFIC_KEY(irr::KEY_NUMPAD8, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_NUMPAD9:
        EMIT_SPECIFIC_KEY(irr::KEY_NUMPAD9, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_MULTIPLY:
        EMIT_SPECIFIC_KEY(irr::KEY_MULTIPLY, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_ADD:
        EMIT_SPECIFIC_KEY(irr::KEY_ADD, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_SEPARATOR:
        EMIT_SPECIFIC_KEY(irr::KEY_SEPARATOR, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_SUBTRACT:
        EMIT_SPECIFIC_KEY(irr::KEY_SUBTRACT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_DECIMAL:
        EMIT_SPECIFIC_KEY(irr::KEY_DECIMAL, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_DIVIDE:
        EMIT_SPECIFIC_KEY(irr::KEY_DIVIDE, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F1:
        EMIT_SPECIFIC_KEY(irr::KEY_F1, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F2:
        EMIT_SPECIFIC_KEY(irr::KEY_F2, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F3:
        EMIT_SPECIFIC_KEY(irr::KEY_F3, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F4:
        EMIT_SPECIFIC_KEY(irr::KEY_F4, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F5:
        EMIT_SPECIFIC_KEY(irr::KEY_F5, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F6:
        EMIT_SPECIFIC_KEY(irr::KEY_F6, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F7:
        EMIT_SPECIFIC_KEY(irr::KEY_F7, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F8:
        EMIT_SPECIFIC_KEY(irr::KEY_F8, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F9:
        EMIT_SPECIFIC_KEY(irr::KEY_F9, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F10:
        EMIT_SPECIFIC_KEY(irr::KEY_F10, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F11:
        EMIT_SPECIFIC_KEY(irr::KEY_F11, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F12:
        EMIT_SPECIFIC_KEY(irr::KEY_F12, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F13:
        EMIT_SPECIFIC_KEY(irr::KEY_F13, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F14:
        EMIT_SPECIFIC_KEY(irr::KEY_F14, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F15:
        EMIT_SPECIFIC_KEY(irr::KEY_F15, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F16:
        EMIT_SPECIFIC_KEY(irr::KEY_F16, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F17:
        EMIT_SPECIFIC_KEY(irr::KEY_F17, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F18:
        EMIT_SPECIFIC_KEY(irr::KEY_F18, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F19:
        EMIT_SPECIFIC_KEY(irr::KEY_F19, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F20:
        EMIT_SPECIFIC_KEY(irr::KEY_F20, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F21:
        EMIT_SPECIFIC_KEY(irr::KEY_F21, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F22:
        EMIT_SPECIFIC_KEY(irr::KEY_F22, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F23:
        EMIT_SPECIFIC_KEY(irr::KEY_F23, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_F24:
        EMIT_SPECIFIC_KEY(irr::KEY_F24, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_NUMLOCK:
        EMIT_SPECIFIC_KEY(irr::KEY_NUMLOCK, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_SCROLL:
        EMIT_SPECIFIC_KEY(irr::KEY_SCROLL, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_LSHIFT:
        EMIT_SPECIFIC_KEY(irr::KEY_LSHIFT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_RSHIFT:
        EMIT_SPECIFIC_KEY(irr::KEY_RSHIFT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_LCONTROL:
        EMIT_SPECIFIC_KEY(irr::KEY_LCONTROL, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_RCONTROL:
        EMIT_SPECIFIC_KEY(irr::KEY_RCONTROL, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_LMENU:
        EMIT_SPECIFIC_KEY(irr::KEY_LMENU, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_RMENU:
        EMIT_SPECIFIC_KEY(irr::KEY_RMENU, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_OEM_1:
        EMIT_SPECIFIC_KEY(irr::KEY_OEM_1, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_PLUS:
        EMIT_SPECIFIC_KEY(irr::KEY_PLUS, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_COMMA:
        EMIT_SPECIFIC_KEY(irr::KEY_COMMA, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_MINUS:
        EMIT_SPECIFIC_KEY(irr::KEY_MINUS, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_PERIOD:
        EMIT_SPECIFIC_KEY(irr::KEY_PERIOD, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_OEM_2:
        EMIT_SPECIFIC_KEY(irr::KEY_OEM_2, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_OEM_3:
        EMIT_SPECIFIC_KEY(irr::KEY_OEM_3, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_OEM_4:
        EMIT_SPECIFIC_KEY(irr::KEY_OEM_4, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_OEM_5:
        EMIT_SPECIFIC_KEY(irr::KEY_OEM_5, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_OEM_6:
        EMIT_SPECIFIC_KEY(irr::KEY_OEM_6, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_OEM_7:
        EMIT_SPECIFIC_KEY(irr::KEY_OEM_7, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_OEM_8:
        EMIT_SPECIFIC_KEY(irr::KEY_OEM_8, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_OEM_AX:
        EMIT_SPECIFIC_KEY(irr::KEY_OEM_AX, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_OEM_102:
        EMIT_SPECIFIC_KEY(irr::KEY_OEM_102, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_ATTN:
        EMIT_SPECIFIC_KEY(irr::KEY_ATTN, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_CRSEL:
        EMIT_SPECIFIC_KEY(irr::KEY_CRSEL, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_EXSEL:
        EMIT_SPECIFIC_KEY(irr::KEY_EXSEL, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_EREOF:
        EMIT_SPECIFIC_KEY(irr::KEY_EREOF, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_PLAY:
        EMIT_SPECIFIC_KEY(irr::KEY_PLAY, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_ZOOM:
        EMIT_SPECIFIC_KEY(irr::KEY_ZOOM, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_PA1:
        EMIT_SPECIFIC_KEY(irr::KEY_PA1, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_OEM_CLEAR:
        EMIT_SPECIFIC_KEY(irr::KEY_OEM_CLEAR, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    case irr::KEY_KEY_CODES_COUNT:
        EMIT_SPECIFIC_KEY(irr::KEY_KEY_CODES_COUNT, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
        break;
    }
}

void jf::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::sendJoystickInputEvent(const irr::SEvent &event)
{
    ECSWrapper ecs;
    ecs.eventManager.emit(events::IrrlichtJoystickEvent({event.JoystickEvent}));
}

void jf::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::sendLogTextEvent(const irr::SEvent &event)
{
    (void)event;
}

void jf::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::sendUserEvent(const irr::SEvent &event)
{
    (void)event;
}

irr::scene::ISceneManager *jf::systems::IrrlichtManagerSystem::getSceneManager() const
{
    return _sceneManager;
}

irr::video::IVideoDriver *jf::systems::IrrlichtManagerSystem::getVideoDriver() const
{
    return _driver;
}


void jf::systems::IrrlichtManagerSystem::syncParticle(__attribute__((unused))jf::entities::EntityHandler entity, components::ComponentHandler<components::Transform> transf, components::ComponentHandler<components::Particle> particle)
{
    irr::core::vector3df newPosition;
    irr::core::vector3df newScale;
    irr::core::vector3df newRotation;

    newPosition.X = transf->getPosition().x;
    newPosition.Y = transf->getPosition().y;
    newPosition.Z = transf->getPosition().z;
    particle->setPosition(newPosition);
    newScale.X = transf->getScale().x;
    newScale.Y = transf->getScale().y;
    newScale.Z = transf->getScale().z;
    particle->setScale(newScale);
    newRotation.X = transf->getRotation().x;
    newRotation.Y = transf->getRotation().y;
    newRotation.Z = transf->getRotation().z;
    particle->setRotation(newRotation);
}
