/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** Mesh
*/

#ifndef MESH_HPP_
#define MESH_HPP_

#include "IrrlichtManagerSystem.hpp"

namespace jf {

    namespace components {

        class Mesh {
            public:
                Mesh(const std::string filename);
                ~Mesh();

            protected:
            private:
                irr::scene::IAnimatedMesh *_mesh;
                irr::scene::IAnimatedMeshSceneNode *_node;
        };
    }
}

#endif /* !MESH_HPP_ */