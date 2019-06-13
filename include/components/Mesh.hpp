/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** Mesh
*/

#ifndef MESH_HPP_
#define MESH_HPP_

#include "Component.hpp"
#include "systems/IrrlichtManagerSystem.hpp"

namespace indie {

    namespace components {

        class Mesh : public jf::components::Component {
        public:
            Mesh(jf::entities::Entity &entity, const std::string filename);
            ~Mesh();

            Mesh &operator>>(std::ostream &file);

            void addToScene();
            void changeVisibility(bool shouldBeSeen);
            void changeMesh(const std::string &filename);
            void setPos(irr::core::vector3df &vector);
            void setMaterialTexture(const std::string &filename);
            void setMaterialType(irr::video::E_MATERIAL_TYPE type);
            void setMaterialFlag(irr::video::E_MATERIAL_FLAG flag, bool value);
            void setScale(irr::core::vector3df &vector);
            void rotate(irr::core::vector3df &vector);
            bool linkFilenameToMesh();
            bool applyChanges();

            irr::scene::IAnimatedMeshSceneNode *getAnimatedMeshNode();

        protected:
        private:
            irr::scene::IAnimatedMesh *_mesh;
            irr::scene::IAnimatedMeshSceneNode *_node;
            std::string _meshFilename;
            bool _shouldMeshChange;
            jf::internal::ID _irrlichtClosingWindowEventID;
        };
    }
}

#else

namespace indie {

    namespace components {
        class Mesh;
    }
}

#endif /* !MESH_HPP_ */