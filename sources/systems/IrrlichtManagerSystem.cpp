/*
** EPITECH PROJECT, 2018
** jfecs-irrlicht
** File description:
** IrrlichtManagerSystem.cpp
*/

/* Created the 09/05/2019 at 13:55 by jfrabel */

#include "maths/Vectors.hpp"
#include "maths/Matrices.hpp"
#include "maths/Geometry3D.hpp"
#include "components/Camera.hpp"
#include "exceptions/IrrlichtManagerExceptions.hpp"
#include "ECSWrapper.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
#include "events/IrrlichtKeyInputEvent.hpp"
#include "events/IrrlichtJoystickInputEvent.hpp"
#include "events/IrrlichtMouseInputEvent.hpp"
#include "events/IrrlichtGUIEvent.hpp"
#include "components/GUI/Button.hpp"
#include "components/GUI/Text.hpp"
#include "components/GUI/Font.hpp"
#include "components/GUI/Image.hpp"
#include "components/Transform.hpp"
#include "components/SoundComponent.hpp"
#include "Entity.hpp"
#include "EntityHandler.hpp"
#include "events/IrrlichtClosingWindowEvent.hpp"
#include "exceptions/AnimatorException.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

bool indie::systems::IrrlichtManagerSystem::_drawGizmos = false;

indie::systems::IrrlichtManagerSystem::IrrlichtManagerSystem()
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
      _windowDimension(800, 600),
      _needToReload(false)
{
}

indie::systems::IrrlichtManagerSystem::~IrrlichtManagerSystem()
{
    if (isWindowOpen())
        closeWindow();
}

void indie::systems::IrrlichtManagerSystem::onAwake()
{
    ECSWrapper ecs;
    ecs.eventManager.addListener<IrrlichtManagerSystem, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_P>>(this, [](IrrlichtManagerSystem *ms, auto e) {
        ms->_device->closeDevice();
    });
}

void indie::systems::IrrlichtManagerSystem::onStart()
{
    openWindow();
}

void indie::systems::IrrlichtManagerSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    if (!_driver || !_sceneManager || !_guiEnvironment)
        return;

    if (_needToReload) {
        if (_device != nullptr)
            closeWindow();
        if (_device == nullptr)
            openWindow();
        _needToReload = false;
    }

    ECSWrapper ecs;

    _driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
    
    /* Camera */
    updateCamera(elapsedTime);
    /* Light */
    ecs.entityManager.applyToEach<components::PointLight>(&syncPointLights);
    /* Particle */
    ecs.entityManager.applyToEach<components::Transform, components::Particle>(&syncParticlePos);
    /* 3DModel */
    ecs.entityManager.applyToEach<components::Mesh>(&syncModel);

    if (_drawGizmos) {
        ecs.entityManager.applyToEach<components::BoxCollider>(&drawBoxColliderGizmos);
    }

    ecs.entityManager.applyToEach<components::Transform, components::Button>(&drawButton);
    ecs.entityManager.applyToEach<components::Transform, components::Text>(&drawText);
    ecs.entityManager.applyToEach<components::Transform, components::Image>(&drawImage);

    _sceneManager->drawAll();
    _guiEnvironment->drawAll();

    _driver->endScene();
}

void indie::systems::IrrlichtManagerSystem::onStop()
{
    closeWindow();
}

void indie::systems::IrrlichtManagerSystem::onTearDown()
{

}

bool indie::systems::IrrlichtManagerSystem::isFullScreenEnabled() const
{
    return _fullscreenEnabled;
}

void indie::systems::IrrlichtManagerSystem::setFullScreenEnabled(bool enabled)
{
    _fullscreenEnabled = enabled;
    reloadWindow();
}

bool indie::systems::IrrlichtManagerSystem::isVSyncEnabled() const
{
    return _vsyncEnabled;
}

void indie::systems::IrrlichtManagerSystem::setVSyncEnabled(bool enabled)
{
    _vsyncEnabled = enabled;
    reloadWindow();
}

const std::string &indie::systems::IrrlichtManagerSystem::getWindowCaption() const
{
    return _windowCaption;
}

void indie::systems::IrrlichtManagerSystem::setWindowCaption(const std::string &str)
{
    _windowCaption = str;
    reloadWindow();
}

const indie::maths::Vector2D &indie::systems::IrrlichtManagerSystem::getWindowDimension() const
{
    return _windowDimension;
}

void indie::systems::IrrlichtManagerSystem::setWindowDimension(const indie::maths::Vector2D &dimensions)
{
    _windowDimension = dimensions;
    reloadWindow();
}

irr::scene::ISceneManager *indie::systems::IrrlichtManagerSystem::getSceneManager()
{
    return _sceneManager;
}

irr::video::IVideoDriver *indie::systems::IrrlichtManagerSystem::getVideoDriver()
{
    return _driver;
}

irr::gui::IGUIEnvironment *indie::systems::IrrlichtManagerSystem::getGUIEnvironment()
{
    return _guiEnvironment;
}

irr::IrrlichtDevice* indie::systems::IrrlichtManagerSystem::getDevice()
{
    return _device;
}

bool indie::systems::IrrlichtManagerSystem::isWindowOpen() const
{
    if (_device != nullptr)
        return _device->run();
    return false;
}

void indie::systems::IrrlichtManagerSystem::openWindow()
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
        throw exceptions::IrrlichtManagerDeviceException("Failed to create device", "indie::systems::IrrlichtManagerSystem::openWindow");
    _device->setWindowCaption(std::wstring(_windowCaption.begin(), _windowCaption.end()).c_str());
    _driver = _device->getVideoDriver();
    _sceneManager = _device->getSceneManager();
    _guiEnvironment = _device->getGUIEnvironment();
    reloadJoysticks();
}

void indie::systems::IrrlichtManagerSystem::closeWindow()
{
    if (_device != nullptr) {
        ECSWrapper ecs;
        ecs.eventManager.emit(events::IrrlichtClosingWindowEvent());
        _device->closeDevice();
        _device->run();
        _device->drop();
    }
    _device = nullptr;
}

void indie::systems::IrrlichtManagerSystem::reloadWindow()
{
    if (!isWindowOpen())
        return;
    _needToReload = true;
}

void indie::systems::IrrlichtManagerSystem::activateJoysticks()
{
    _joystickEnabled = true;
}

const irr::core::array<irr::SJoystickInfo> &indie::systems::IrrlichtManagerSystem::getJoystickInfos()
{
    return _joystickInfos;
}

void indie::systems::IrrlichtManagerSystem::reloadJoysticks()
{
    if (_joystickEnabled) {
        if (_device == nullptr) {
            throw exceptions::IrrlichtManagerDeviceException("Device is not open.", "indie::systems::IrrlichtManagerSystem::reloadJoysticks");
        }
        if (!_device->activateJoysticks(_joystickInfos)) {
            throw exceptions::IrrlichtManagerDeviceException("Joystick support is not enabled.", "indie::systems::IrrlichtManagerSystem::reloadJoysticks");
        }
        std::cout << "Joystick support is enabled and " << _joystickInfos.size() << " joystick(s) are present." << std::endl;
    }
}

void indie::systems::IrrlichtManagerSystem::updateCamera(const std::chrono::nanoseconds &elapsedTime)
{
    ECSWrapper ecs;

    std::vector<jf::entities::EntityHandler> cameras;
    cameras = ecs.entityManager.getEntitiesWith<indie::components::Camera, indie::components::Transform>();

    if (!cameras.empty()) {
        cameras[0]->getComponent<indie::components::Camera>()->updateCamera();
        _sceneManager->setActiveCamera(cameras[0]->getComponent<indie::components::Camera>()->getCameraNode());
    }
}

void indie::systems::IrrlichtManagerSystem::syncModel(jf::entities::EntityHandler entity,
                                                      jf::components::ComponentHandler<indie::components::Mesh> mesh)
{
    auto tr = entity->getComponent<components::Transform>();
    auto mat = entity->getComponent<components::Material>();
    auto animator = entity->getComponent<components::Animator>();
    bool forceReload = false;

    forceReload = forceReload || mesh->linkFilenameToMesh();
    forceReload = forceReload || mesh->applyChanges();
    mesh->addToScene();
    if (tr.isValid()) {
        syncModelPos(tr, mesh, forceReload);
    }
    if (mat.isValid()) {
        syncModelMaterial(mat, mesh, forceReload);
    }
    if (animator.isValid()) {
        syncModelAnimation(animator, mesh, forceReload);
    }
}

void indie::systems::IrrlichtManagerSystem::syncModelMaterial(
    jf::components::ComponentHandler<indie::components::Material> mat,
    jf::components::ComponentHandler<indie::components::Mesh> mesh,
    bool force)
{
    if (mat->hasMaterialChanged() || force) {
        if (mat->hasMaterialTextureChanged() || force) {
            mesh->setMaterialTexture(mat->getMaterialTexture());
        }
        if (mat->hasMaterialTypeChanged() || force) {
            mesh->setMaterialType(mat->getMaterialType());
        }
        if (mat->hasMaterialFlagsChanged() || force) {
            for (const auto &flag : mat->getMaterialFlags()) {
                mesh->setMaterialFlag(flag.first, flag.second);
            }
        }
        mat->resetHasMaterialChanged();
    }
}

void indie::systems::IrrlichtManagerSystem::syncModelPos(
    jf::components::ComponentHandler<components::Transform> tr,
    jf::components::ComponentHandler<components::Mesh> mesh,
    bool force)
{
    auto pos = tr->getPosition();
    irr::core::vector3df vector(pos.x, pos.y, pos.z);
    mesh->setPos(vector);
    auto scale = tr->getScale();
    irr::core::vector3df vectorScale(scale.x, scale.y, scale.z);
    mesh->setScale(vectorScale);
    auto rotate = tr->getRotation();
    irr::core::vector3df vectorRotation(rotate.x, rotate.y, rotate.z);
    mesh->rotate(vectorRotation);
}

void indie::systems::IrrlichtManagerSystem::syncModelAnimation(
    jf::components::ComponentHandler<indie::components::Animator> animator,
    jf::components::ComponentHandler<indie::components::Mesh> mesh,
    bool force)
{
    if ((animator->hasAnimationChanged() || force) && !animator->getCurrentAnimation().empty()) {
        animator->resetAnimationChanged();
        components::Animator::Animation data;
        try {
            data = animator->getCurrentAnimationData();
        } catch (exceptions::AnimatorException &e) {
            std::cerr << "[WARNING][IrrlichtManagerSystem] an animation was set but not found: " << e.what() << std::endl;
            return;
        }
        auto *node = mesh->getAnimatedMeshNode();
        if (node == nullptr) {
            return;
        }
        node->setAnimationSpeed(data.speed);
        node->setFrameLoop(data.start, data.end);
        node->setLoopMode(data.loop);
        node->setAnimationEndCallback(animator.get());
    }
}

void indie::systems::IrrlichtManagerSystem::syncParticlePos(jf::entities::EntityHandler entity,
                                                            jf::components::ComponentHandler<components::Transform> tr,
                                                            jf::components::ComponentHandler<components::Particle> particle)
{
    irr::core::vector3df newPosition;
    irr::core::vector3df newScale;
    irr::core::vector3df newRotation;

    if (!particle->isInit())
        particle->initParticle();
    newPosition.X = tr->getPosition().x;
    newPosition.Y = tr->getPosition().y;
    newPosition.Z = tr->getPosition().z;
    particle->setPosition(newPosition);
    newScale.X = tr->getScale().x;
    newScale.Y = tr->getScale().y;
    newScale.Z = tr->getScale().z;
    particle->setScale(newScale);
    newRotation.X = tr->getRotation().x;
    newRotation.Y = tr->getRotation().y;
    newRotation.Z = tr->getRotation().z;
    particle->setRotation(newRotation);
    particle->render();
}

void indie::systems::IrrlichtManagerSystem::syncPointLights(
    jf::entities::EntityHandler entity,
    jf::components::ComponentHandler<indie::components::PointLight> pl)
{
    ECSWrapper ecs;
    auto tr = entity->getComponent<components::Transform>();
    IrrlichtManagerSystem &sys = ecs.systemManager.getSystem<IrrlichtManagerSystem>();
    auto sceneManager = sys.getSceneManager();
    auto driver = sys.getVideoDriver();

    if (sceneManager == nullptr || driver == nullptr)
        return;
    if (!pl->isInit()) {
        irr::scene::ILightSceneNode *light = sceneManager->addLightSceneNode(
            nullptr,
            tr.isValid() ? irr::core::vector3df(tr->getPosition().x, tr->getPosition().y, tr->getPosition().z) : irr::core::vector3df(0, 0, 0),
            pl->getLightColor(),
            pl->getRadius()
        );
        light->enableCastShadow(pl->getCastShadows());
        pl->setLightNode(light);
        irr::scene::IBillboardSceneNode *billboard = sceneManager->addBillboardSceneNode(light, pl->getBillboardDimensions());
        billboard->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        billboard->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
        billboard->setMaterialTexture(0, driver->getTexture(pl->getBillboardTexture().c_str()));
        pl->setBillboardNode(billboard);
    }

    if (tr.isValid())
        syncPointLightsTransform(tr, pl);

    if (pl->getChanges())
        syncPointChanges(pl);
}

void indie::systems::IrrlichtManagerSystem::syncPointLightsTransform(
    jf::components::ComponentHandler<indie::components::Transform> tr,
    jf::components::ComponentHandler<indie::components::PointLight> pl)
{
    irr::core::vector3df newPosition;
    irr::core::vector3df newScale;
    irr::core::vector3df newRotation;

    newPosition.X = tr->getPosition().x;
    newPosition.Y = tr->getPosition().y;
    newPosition.Z = tr->getPosition().z;
    pl->getLightNode()->setPosition(newPosition);
    newScale.X = tr->getScale().x;
    newScale.Y = tr->getScale().y;
    newScale.Z = tr->getScale().z;
    pl->getLightNode()->setScale(newScale);
    newRotation.X = tr->getRotation().x;
    newRotation.Y = tr->getRotation().y;
    newRotation.Z = tr->getRotation().z;
    pl->getLightNode()->setRotation(newRotation);
}

void indie::systems::IrrlichtManagerSystem::syncPointChanges(jf::components::ComponentHandler<indie::components::PointLight> pl)
{
    ECSWrapper ecs;
    auto driver = ecs.systemManager.getSystem<IrrlichtManagerSystem>().getVideoDriver();

    auto lightData = pl->getLightNode()->getLightData();
    if (pl->getChanges() & POINT_LIGHT_SHOW_SHADOWS_CHANGES) {
        pl->getLightNode()->enableCastShadow(pl->getCastShadows());
    }
    if (pl->getChanges() & POINT_LIGHT_SHOW_BILLBOARD_CHANGES) {
        pl->getBillboardNode()->setVisible(pl->getShowBillboard());
    }
    if (pl->getChanges() & POINT_LIGHT_SHOW_LIGHT_CHANGES) {
        pl->getLightNode()->setVisible(pl->getShowLight());
    }
    if (pl->getChanges() & POINT_LIGHT_LIGHT_COLOR_CHANGES) {
        lightData.DiffuseColor = pl->getLightColor();
    }
    if (pl->getChanges() & POINT_LIGHT_LIGHT_RADIUS_CHANGES) {
        lightData.Radius = pl->getRadius();
    }
    if (pl->getChanges() & POINT_LIGHT_BILLBOARD_DIM_CHANGES) {
        pl->getBillboardNode()->setSize(pl->getBillboardDimensions());
    }
    if (pl->getChanges() & POINT_LIGHT_BILLBOARD_TEX_CHANGES) {
        pl->getBillboardNode()->setMaterialTexture(0, driver->getTexture(pl->getBillboardTexture().c_str()));
    }
    if (pl->getChanges() & (POINT_LIGHT_LIGHT_COLOR_CHANGES | POINT_LIGHT_LIGHT_RADIUS_CHANGES)) {
        pl->getLightNode()->setLightData(lightData);
    }
    pl->resetChanges();
}

void indie::systems::IrrlichtManagerSystem::drawBoxColliderGizmos(jf::entities::EntityHandler entity,
                                                                  jf::components::ComponentHandler<indie::components::BoxCollider> collider)
{
    ECSWrapper ecs;
    auto tr = entity->getComponent<components::Transform>();
    auto rot = tr.isValid() ? tr->getRotation() : maths::Vector3D();
    maths::Vector3D position = tr.isValid() ? tr->getPosition() + collider->getOffset() : collider->getOffset();
    maths::Vector3D size = collider->getSize() * tr->getScale();
    maths::Matrix3 rotation = maths::Matrix3::Rotation(rot.x, rot.y, rot.z);
    maths::Vector3D axes[] = {
        maths::Vector3D(rotation.asArray[0], rotation.asArray[1], rotation.asArray[2]),
        maths::Vector3D(rotation.asArray[3], rotation.asArray[4], rotation.asArray[5]),
        maths::Vector3D(rotation.asArray[6], rotation.asArray[7], rotation.asArray[8]),
    };
    maths::Vector3D vertices[8];
    vertices[0] = position + axes[0] * size[0] + axes[1] * size[1] + axes[2] * size[2];
    vertices[1] = position - axes[0] * size[0] + axes[1] * size[1] + axes[2] * size[2];
    vertices[2] = position + axes[0] * size[0] - axes[1] * size[1] + axes[2] * size[2];
    vertices[3] = position + axes[0] * size[0] + axes[1] * size[1] - axes[2] * size[2];
    vertices[4] = position - axes[0] * size[0] - axes[1] * size[1] - axes[2] * size[2];
    vertices[5] = position + axes[0] * size[0] - axes[1] * size[1] - axes[2] * size[2];
    vertices[6] = position - axes[0] * size[0] + axes[1] * size[1] - axes[2] * size[2];
    vertices[7] = position - axes[0] * size[0] - axes[1] * size[1] + axes[2] * size[2];

    auto driver = ecs.systemManager.getSystem<IrrlichtManagerSystem>().getVideoDriver();

    irr::video::SMaterial mat;
    mat.Lighting = false;
    driver->setMaterial(mat);

    irr::core::matrix4 identity;
    driver->setTransform(irr::video::ETS_WORLD, identity);
    for (int i = 0; i < 7; ++i) {
        for (int j = i + 1; j < 8; ++j) {
            driver->draw3DLine(
                irr::core::vector3df(vertices[i].x, vertices[i].y, vertices[i].z),
                irr::core::vector3df(vertices[j].x, vertices[j].y, vertices[j].z),
                irr::video::SColor(255, 0, 255, 0));
        }
    }
}

void indie::systems::IrrlichtManagerSystem::drawGizmos(bool value)
{
    _drawGizmos = value;
}

bool indie::systems::IrrlichtManagerSystem::getDrawGizmos()
{
    return _drawGizmos;
}

void indie::systems::IrrlichtManagerSystem::drawButton(jf::entities::EntityHandler entity,
                                                       jf::components::ComponentHandler<components::Transform> tr,
                                                       jf::components::ComponentHandler<components::Button> button)
{
    ECSWrapper ecs;
    auto env = ecs.systemManager.getSystem<IrrlichtManagerSystem>().getGUIEnvironment();
    auto driver = ecs.systemManager.getSystem<IrrlichtManagerSystem>().getVideoDriver();
    auto pos = tr->getPosition();
    auto scale = tr->getScale();
    auto font = entity->getComponent<components::Font>();
    irr::core::rect<irr::s32> rect = irr::core::rect<irr::s32>(pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);
    irr::gui::IGUIButton *buttonNode = nullptr;
    std::wstring wideString = std::wstring(button->getText().begin(), button->getText().end());
    const wchar_t *text = wideString.c_str();

    if (!button->isInit()) {
        buttonNode = env->addButton(rect, nullptr, button->getId(), text);
        button->setButtonNode(buttonNode);
    }
    if (button->isTextureNeedInit())
        button->setTextureNode(driver->getTexture(button->getTexturePath().c_str()));
    buttonNode = button->getButtonNode();
    buttonNode->setText(text);
    buttonNode->setRelativePosition(rect);
    buttonNode->setID(button->getId());
    if (button->getTextureNode() != nullptr)
        buttonNode->setImage(button->getTextureNode());
    if (font.isValid()) {
        if (!font->isInit()) {
            font->setFontNode(env->getFont(font->getPath().c_str()));
        }
        buttonNode->setOverrideFont(font->getFontNode());
    }
}

void indie::systems::IrrlichtManagerSystem::drawText(jf::entities::EntityHandler entity,
                                                     jf::components::ComponentHandler<indie::components::Transform> tr,
                                                     jf::components::ComponentHandler<indie::components::Text> text)
{
    ECSWrapper ecs;
    auto env = ecs.systemManager.getSystem<IrrlichtManagerSystem>().getGUIEnvironment();
    auto pos = tr->getPosition();
    auto scale = tr->getScale();
    auto font = entity->getComponent<components::Font>();
    irr::core::rect<irr::s32> rect = irr::core::rect<irr::s32>(pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);
    irr::gui::IGUIStaticText *textNode = nullptr;
    std::wstring wideString = std::wstring(text->getText().begin(), text->getText().end());
    const wchar_t *textStr = wideString.c_str();

    if (!text->isInit()) {
        textNode = env->addStaticText(textStr, rect, false, true, nullptr, text->getId());
        text->setTextNode(textNode);
    }
    textNode = text->getTextNode();
    textNode->setText(textStr);
    textNode->setRelativePosition(rect);
    textNode->setID(text->getId());
    textNode->setTextAlignment(static_cast<irr::gui::EGUI_ALIGNMENT>(text->getHorizontalAlignement()), static_cast<irr::gui::EGUI_ALIGNMENT>(text->getVerticalAlignement()));
    textNode->setOverrideColor(text->getColor());
    textNode->setBackgroundColor(text->getBackgroundColor());
    textNode->setDrawBackground(true);
    if (font.isValid()) {
        if (!font->isInit()) {
            font->setFontNode(env->getFont(font->getPath().c_str()));
        }
        textNode->setOverrideFont(font->getFontNode());
    }
}

void indie::systems::IrrlichtManagerSystem::drawImage(jf::entities::EntityHandler entity,
                                                      jf::components::ComponentHandler<indie::components::Transform> tr,
                                                      jf::components::ComponentHandler<indie::components::Image> image)
{
    ECSWrapper ecs;
    auto driver = ecs.systemManager.getSystem<IrrlichtManagerSystem>().getVideoDriver();
    auto env = ecs.systemManager.getSystem<IrrlichtManagerSystem>().getGUIEnvironment();
    auto pos = tr->getPosition();
    irr::core::position2d<irr::s32> irrPos = irr::core::position2d<irr::s32>(pos.x, pos.y);
    irr::video::ITexture *textureNode = nullptr;

    if (!image->isTextureInit()) {
        textureNode = driver->getTexture(image->getPath().c_str());
        driver->makeColorKeyTexture(textureNode, irr::core::position2d<irr::s32>(0, 0));
        image->setTextureNode(textureNode);
    }
    if (image->isTextureInit() && !image->isImageInit()) {
        textureNode = image->getTextureNode();
        image->setImageNode(env->addImage(textureNode, irrPos, false));
    }
}


bool indie::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::OnEvent(const irr::SEvent &event)
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

void indie::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::sendGUIEvent(const irr::SEvent &event)
{
    ECSWrapper ecs;
    ecs.eventManager.emit(events::IrrlichtGUIEvent({event.GUIEvent}));
    if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
        ecs.entityManager.applyToEach<components::Button>([event](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Button> button){
            if (button->getId() == event.GUIEvent.Caller->getID()) {
                if (button->getOnClicked() != nullptr)
                    button->getOnClicked()(button.get());
            }
        });
    } else if (event.GUIEvent.EventType == irr::gui::EGET_ELEMENT_HOVERED) {
        ecs.entityManager.applyToEach<components::Button>([event](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Button> button){
            if (button->getId() == event.GUIEvent.Caller->getID()) {
                if (button->getOnHovered() != nullptr)
                    button->getOnHovered()(button.get(), true);
            }
        });
    } else if (event.GUIEvent.EventType == irr::gui::EGET_ELEMENT_LEFT) {
        ecs.entityManager.applyToEach<components::Button>([event](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Button> button){
            if (button->getId() == event.GUIEvent.Caller->getID()) {
                if (button->getOnHovered() != nullptr)
                    button->getOnHovered()(button.get(), false);
            }
        });
    }
}

void indie::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::sendMouseInputEvent(const irr::SEvent &event)
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

void indie::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::sendKeyInputEvent(const irr::SEvent &event)
{
    ECSWrapper ecs;
    ecs.eventManager.emit(indie::events::IrrlichtKeyInputEvent({
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

void indie::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::sendJoystickInputEvent(const irr::SEvent &event)
{
    ECSWrapper ecs;
    ecs.eventManager.emit(events::IrrlichtJoystickEvent({event.JoystickEvent}));
}

void indie::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::sendLogTextEvent(const irr::SEvent &event)
{
    (void)event;
}

void indie::systems::IrrlichtManagerSystem::IrrlichtEventReceiver::sendUserEvent(const irr::SEvent &event)
{
    (void)event;
}
