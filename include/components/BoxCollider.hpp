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

    enum BombermanLayers : uint64_t {
        P1_UNBREAKABLE_BLOCK_LAYER  = 0b000000000001,
        P1_BREAKABLE_BLOCK_LAYER    = 0b000000000010,
        P1_BOMB_LAYER               = 0b000000000100,
        P2_UNBREAKABLE_BLOCK_LAYER  = 0b000000001000,
        P2_BREAKABLE_BLOCK_LAYER    = 0b000000010000,
        P2_BOMB_LAYER               = 0b000000100000,
        P3_UNBREAKABLE_BLOCK_LAYER  = 0b000001000000,
        P3_BREAKABLE_BLOCK_LAYER    = 0b000010000000,
        P3_BOMB_LAYER               = 0b000100000000,
        P4_UNBREAKABLE_BLOCK_LAYER  = 0b001000000000,
        P4_BREAKABLE_BLOCK_LAYER    = 0b010000000000,
        P4_BOMB_LAYER               = 0b100000000000,
        UNBREAKABLE_BLOCK_LAYER     = P1_UNBREAKABLE_BLOCK_LAYER | P2_UNBREAKABLE_BLOCK_LAYER | P3_UNBREAKABLE_BLOCK_LAYER | P4_UNBREAKABLE_BLOCK_LAYER,
        BREAKABLE_BLOCK_LAYER       = P1_BREAKABLE_BLOCK_LAYER | P2_BREAKABLE_BLOCK_LAYER | P3_BREAKABLE_BLOCK_LAYER | P4_BREAKABLE_BLOCK_LAYER,
        BOMB_LAYER                  = P1_BOMB_LAYER | P2_BOMB_LAYER | P3_BOMB_LAYER | P4_BOMB_LAYER,
        P1_LAYER                    = P1_UNBREAKABLE_BLOCK_LAYER | P1_BREAKABLE_BLOCK_LAYER | P1_BOMB_LAYER,
        P2_LAYER                    = P2_UNBREAKABLE_BLOCK_LAYER | P2_BREAKABLE_BLOCK_LAYER | P2_BOMB_LAYER,
        P3_LAYER                    = P3_UNBREAKABLE_BLOCK_LAYER | P3_BREAKABLE_BLOCK_LAYER | P3_BOMB_LAYER,
        P4_LAYER                    = P4_UNBREAKABLE_BLOCK_LAYER | P4_BREAKABLE_BLOCK_LAYER | P4_BOMB_LAYER,
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

        private:
            maths::Vector3D _size;
            maths::Vector3D _offset;
            uint64_t _layer;
        };
    }
}
#endif //INDIESTUDIO_BOXCOLLIDER_HPP
