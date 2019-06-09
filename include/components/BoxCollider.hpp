/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** BoxCollider.hpp
*/

/* Created the 28/05/2019 at 19:56 by jfrabel */

#ifndef INDIESTUDIO_BOXCOLLIDER_HPP
#define INDIESTUDIO_BOXCOLLIDER_HPP

#include "Component.hpp"
#include "maths/Vectors.hpp"

namespace indie {

    enum BombermanLayers {
        UNBREAKABLE_BLOCK_LAYER  = 0b001,
        BREAKABLE_BLOCK_LAYER    = 0b010,
        BOMB_LAYER               = 0b100,
    };

    namespace components {

        class BoxCollider : public jf::components::Component {
        public:
            explicit BoxCollider(jf::entities::Entity &entity, maths::Vector3D size = {1, 1, 1}, maths::Vector3D offset = {0, 0, 0}, uint64_t layer = 0xffffffff);
            ~BoxCollider() override;

            const maths::Vector3D &getSize() const;
            void setSize(const maths::Vector3D &size);

            const maths::Vector3D &getOffset() const;
            void setOffset(const maths::Vector3D &offset);

            uint64_t getLayer() const;
            void setLayer(uint64_t layer);

            bool hasCollisions();
            std::vector<jf::entities::EntityHandler> getCollisions();

            std::ostream &operator<<(std::ostream &file);

        private:
            maths::Vector3D _size;
            maths::Vector3D _offset;
            uint64_t _layer;
        };
    }
}
#endif //INDIESTUDIO_BOXCOLLIDER_HPP
