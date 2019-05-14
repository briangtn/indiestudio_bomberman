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
                //other display settings
                void changeMesh(const std::string filename, bool shouldBeSeen);
                //
            protected:
            private:
                irr::scene::IAnimatedMesh *_mesh;
                irr::scene::IAnimatedMeshSceneNode *_node;
        };
    }
}

#endif /* !MESH_HPP_ */