/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** ASoundComponent.hpp
*/

/* Created the 13/05/2019 at 19:00 by jbulteau */

#ifndef INDIESTUDIO_ASOUNDCOMPONENT_HPP
#define INDIESTUDIO_ASOUNDCOMPONENT_HPP

#include <irrKlang.h>
#include "Component.hpp"
#include "Vectors.hpp"

namespace indie {

    namespace components {

        class ASoundComponent : public jf::components::Component {
        public:
            enum SoundType {
                MUSIC,
                EFFECT
            };

            enum SoundComponentState {
                STARTING,
                STARTED,
                STOPPING,
                STOPPED
            };

        public:
            explicit ASoundComponent(jf::entities::Entity &entity, const std::string &sourceFile, SoundType soundType);
            ~ASoundComponent() override;

        public:
            const SoundComponentState getState() const;
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

        public:
            virtual const jf::maths::Vector3D getPosition() const;
            virtual void setPosition(const jf::maths::Vector3D &position);
            virtual const jf::maths::Vector3D getVelocity() const;
            virtual void setVelocity(const jf::maths::Vector3D &velocity);

        protected:
            SoundComponentState _state;

            irrklang::ISound *_sound;

            std::string _sourceFile;
            SoundType _soundType;
            bool _shouldBePlayed;
        };
    }
}

#endif //INDIESTUDIO_ASOUNDCOMPONENT_HPP
