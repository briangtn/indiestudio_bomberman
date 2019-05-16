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
                void changeMesh(const std::string &filename);
                void setPos(irr::core::vector3df &vector);
                void setTexture(const std::string &filename);
                void setScale(irr::core::vector3df &vector);
                void rotate(irr::core::vector3df &vector);
                void linkFilenameToMesh();
                void applyChange();
            protected:
            private:
                irr::scene::IAnimatedMesh *_mesh;
                irr::scene::IAnimatedMeshSceneNode *_node;
                std::string _meshFilename;
                std::string _textureFilename;
                bool _shouldMeshChange;
                bool _shouldTextureChange;
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