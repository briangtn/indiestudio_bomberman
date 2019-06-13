/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Controller.hpp
*/

/* Created the 11/06/2019 at 00:39 by brian */

#ifndef INDIESTUDIO_CONTROLLER_HPP
#define INDIESTUDIO_CONTROLLER_HPP

#include <string>
#include "InputManager.hpp"

namespace indie {


    class Controller {
    public:
        enum AxisTypes {
            KEY,
            JOYSTICK,
            CONTROLLERKEY
        };

        struct AxisConfig {
            AxisTypes type;
            KeyAxis keyAxis;
            ControllerKeyAxis controllerKeyAxis;
            JoystickAxis joystickAxis;
        };

        struct KeyConfig {
            AxisTypes type;
            irr::EKEY_CODE keyCode;
            irr::u8 controllerId;
            irr::u8 controllerKeyId;
        };

    public:
        explicit Controller(const std::string &imagePath,
                std::map<std::string, AxisConfig> axes = std::map<std::string, AxisConfig>(),
                std::map<std::string, KeyConfig> keys = std::map<std::string, KeyConfig>());

        const std::string &getImagePath() const;
        void setImagePath(const std::string &imagePath);

        template<typename T>
        void addAxis(const std::string &name, T axis)
        {
            addAxis(name, axis);
        }

        void addAxis(std::string, AxisConfig);
        void addAxis(const std::string &name, KeyAxis axis);
        void addAxis(const std::string &name, ControllerKeyAxis axis);
        void addAxis(const std::string &name, JoystickAxis axis);

        void addKey(std::string, KeyConfig);
        void addKey(const std::string &name, irr::EKEY_CODE keyCode);
        void addKey(const std::string &name, irr::u8 controllerId, irr::u8 keyId);

        const std::map<std::string, AxisConfig> &getAxes() const;
        const std::map<std::string, KeyConfig> &getKeys() const;

        void generateKeysAndAxes(const std::string &baseName);
        void generateKeys(const std::string &baseName);
        void generateAxes(const std::string &baseName);
        void generateKey(std::string name, KeyConfig config);
        void generateAxis(std::string name, AxisConfig config);

        void setControllerId(irr::u8 id);

    protected:
        std::string _imagePath;
        std::map<std::string, AxisConfig> _axes;
        std::map<std::string, KeyConfig> _keys;
    };
}


#endif //INDIESTUDIO_CONTROLLER_HPP
