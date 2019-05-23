/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IScene.hpp
*/

/* Created the 22/05/2019 at 14:49 by jfrabel */

#ifndef INDIESTUDIO_ISCENE_HPP
#define INDIESTUDIO_ISCENE_HPP

namespace indie {
    namespace scenes {
        class IScene {
        public:
            virtual void onStart() = 0;
            virtual void onStop() = 0;
        };
    }
}
#endif //INDIESTUDIO_ISCENE_HPP
