/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** Mesh
*/

#ifndef MESH_HPP_
#define MESH_HPP_

#include "IrrlichtManagerSystem.hpp"
#include "Component.hpp"

namespace jf {

    namespace components {

        class Mesh : public Component {
            public:
                Mesh(entities::Entity &entity, const std::string filename);
                ~Mesh();

                void addToScene();
                void changeVisibility(bool shouldBeSeen);
                //other display settings (SYNCPOSITION IN SYSTEM)
                void changeMesh(const std::string &filename, bool shouldBeSeen, bool shouldAddToScene);
                void setPos(irr::core::vector3df vector);
                void setTexture(const std::string &filename);
            protected:
            private:
                irr::scene::IAnimatedMesh *_mesh;
                irr::scene::IAnimatedMeshSceneNode *_node;
        };
    }
}

#else

namespace jf {

    namespace components {
        class Mesh;
    }
}

#endif /* !MESH_HPP_ */