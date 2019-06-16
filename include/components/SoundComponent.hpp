/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** SoundComponent.hpp
*/

/* Created the 13/05/2019 at 19:00 by jbulteau */

#ifndef INDIESTUDIO_SOUNDCOMPONENT_HPP
#define INDIESTUDIO_SOUNDCOMPONENT_HPP

#include <irrKlang.h>
#include "Component.hpp"
#include "maths/Vectors.hpp"

namespace indie {

    namespace components {

        class SoundComponent : public jf::components::Component {
        public:
            enum SoundType {
                MUSIC,
                EFFECT
            };

            enum SoundComponentState {
                STARTING,
                STARTED
            };

        public:
            explicit SoundComponent(jf::entities::Entity &entity, const std::string &sourceFile, SoundType soundType);
            explicit SoundComponent(jf::entities::Entity &entity, const std::string &sourceFile, SoundType soundType, indie::maths::Vector3D position);
            ~SoundComponent() override;

            SoundComponent &operator>>(std::ostream &file);

        public:
            const SoundComponentState getState() const;
            irrklang::ISound *getSound();
            void setSound(irrklang::ISound *sound);
            const std::string &getSourceFile() const;
            SoundType getSoundType() const;
            bool getSpatialization() const;
            bool getIsLooped() const;
            void setIsLooped(bool isLooped);
            bool getIsPaused() const;
            void setIsPaused(bool isPaused);
            float getVolume() const;
            void setVolume(float volume);
            unsigned int getPlayPosition() const;
            void setPlayPosition(unsigned int position);

        public:
            virtual const indie::maths::Vector3D getPosition() const;
            virtual void setPosition(const indie::maths::Vector3D &position);
            virtual const indie::maths::Vector3D getVelocity() const;
            virtual void setVelocity(const indie::maths::Vector3D &velocity);

        private:
            SoundComponentState _state;

            irrklang::ISound *_sound;

            std::string _sourceFile;
            SoundType _soundType;
            bool _spatialization;

            bool _isLooped;
            bool _isPaused;
            float _volume;
            unsigned int _playPosition;

            indie::maths::Vector3D _position;
            indie::maths::Vector3D _velocity;
        };
    }
}

#endif //INDIESTUDIO_SOUNDCOMPONENT_HPP
