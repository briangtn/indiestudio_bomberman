/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** 2DSoundComponent.hpp
*/

/* Created the 13/05/2019 at 19:00 by jbulteau */

#ifndef INDIESTUDIO_SOUND2DCOMPONENT_HPP
#define INDIESTUDIO_SOUND2DCOMPONENT_HPP

#include <irrKlang.h>
#include "Component.hpp"

namespace indie {

    namespace components {

        class Sound2DComponent : public jf::components::Component {
        public:
            enum SoundType {
                MUSIC,
                EFFECT
            };

            enum Sound2DComponentState {
                STARTING,
                STARTED,
                STOPPING,
                STOPPED
            };

        public:
            explicit Sound2DComponent(jf::entities::Entity &entity, const std::string &sourceFile, SoundType soundType);
            ~Sound2DComponent() override;

        public:
            const Sound2DComponentState getState() const;
            const irrklang::ISound *getSound() const;
            void setSound(irrklang::ISound *sound);
            const std::string &getSourceFile() const;
            SoundType getSoundType() const;
            bool getIsPaused() const;
            void setIsPaused(bool isPaused);
            float getVolume() const;
            void setVolume(float volume);
            bool getShouldBePlayed() const;
            void setShouldBePlayed(bool shouldBePlayed);
            bool getIsLooped() const;
            void setIsLooped(bool loop);
            unsigned int getPlayPosition() const;
            void setPlayPosition(unsigned int position);

        private:
            Sound2DComponentState _state;

            irrklang::ISound *_sound;

            std::string _sourceFile;
            SoundType _soundType;
            bool _shouldBePlayed;
        };
    }
}

#endif //INDIESTUDIO_SOUND2DCOMPONENT_HPP
