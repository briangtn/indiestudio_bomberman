/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** GuiBase.hpp
*/

/* Created the 04/06/2019 at 15:05 by brian */

#ifndef INDIESTUDIO_GUIBASE_HPP
#define INDIESTUDIO_GUIBASE_HPP

#include "Component.hpp"

namespace indie {
    namespace components {
        class GUIBase : public jf::components::Component {
        public:
            explicit GUIBase(jf::entities::Entity &entity, int id = -1);
            ~GUIBase();

            int getId() const;

            void setId(int id);

        protected:
            int _id;
        };
    }
}

#endif //INDIESTUDIO_GUIBASE_HPP
