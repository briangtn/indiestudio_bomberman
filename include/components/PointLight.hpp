/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** PointLight.hpp
*/

/* Created the 19/05/2019 at 15:46 by jfrabel */

#ifndef INDIESTUDIO_POINTLIGHT_HPP
#define INDIESTUDIO_POINTLIGHT_HPP

#include <irrlicht.h>
#include "Component.hpp"
#include "Entity.hpp"

#define DEFAULT_BILLBOARD_TEXTURE "../test_assets/particle_default.png"

#define POINT_LIGHT_NO_CHANGES             0b00000000000000000000000000000000
#define POINT_LIGHT_SHOW_SHADOWS_CHANGES   0b00000000000000000000000000000001
#define POINT_LIGHT_SHOW_BILLBOARD_CHANGES 0b00000000000000000000000000000010
#define POINT_LIGHT_SHOW_LIGHT_CHANGES     0b00000000000000000000000000000100
#define POINT_LIGHT_LIGHT_COLOR_CHANGES    0b00000000000000000000000000001000
#define POINT_LIGHT_LIGHT_RADIUS_CHANGES   0b00000000000000000000000000010000
#define POINT_LIGHT_BILLBOARD_DIM_CHANGES  0b00000000000000000000000000100000
#define POINT_LIGHT_BILLBOARD_TEX_CHANGES  0b00000000000000000000000001000000

namespace indie {

    namespace components {

        class PointLight : public jf::components::Component {
        public:
            PointLight(jf::entities::Entity &entity);
            ~PointLight() override;

            bool isInit();

            void setCastShadows(bool value);
            bool getCastShadows() const;

            void setShowBillboard(bool value);
            bool getShowBillboard() const;

            void setShowLight(bool value);
            bool getShowLight() const;

            void setLightColot(const irr::video::SColorf &value);
            const irr::video::SColorf &getLightColor() const;

            void setRadius(const irr::f32 &radius);
            const irr::f32 &getRadius() const;

            void setBillboardDimensions(const irr::core::dimension2df &dimensions);
            const irr::core::dimension2df &getBillboardDimensions() const;

            void setBillboardTexture(const std::string &texture);
            const std::string &getBillboardTexture() const;

            irr::scene::IBillboardSceneNode *getBillboardNode() const;
            void setBillboardNode(irr::scene::IBillboardSceneNode *node);

            irr::scene::ILightSceneNode *getLightNode() const;
            void setLightNode(irr::scene::ILightSceneNode *node);

            unsigned int getChanges() const;
            void resetChanges();

        private:
            bool _castShadows;
            bool _showBillboard;
            bool _showLight;

            irr::video::SColorf _lightColor;

            irr::f32 _radius;

            irr::core::dimension2df _billboardDimensions;
            std::string _billboardTexture;

            irr::scene::IBillboardSceneNode *_billboardNode;
            irr::scene::ILightSceneNode *_lightNode;

            unsigned int _changes;

            jf::internal::ID _irrlichtClosingWindowEventID;
        };
    }
}

#endif //INDIESTUDIO_POINTLIGHT_HPP
